#pragma once
#include "CoreMinimal.h"
#include "RHI.h"

#include <mutex>
#include <condition_variable>
#include <thread>

#include "zmq.hpp"
#include "NvFBCLibrary.h"
#include "NvFBC/nvFBCToSys.h"

#include "CineXPrivatePCH.h"

namespace std {
    class mutex;
    class condition_variable;
    class thread;
};

constexpr int CACHE_CAPACITY = 16;
struct BoundedBuffer {
    // Member
    TArray<FColor>*             buffer_;
    int                         capacity_;

    int                         front_;
    int                         rear_;
    int                         count_;

    std::mutex                  lock_;

    std::condition_variable     not_full_;
    std::condition_variable     not_empty_;

    // Function
    BoundedBuffer(int capacity) : capacity_(capacity), front_(0), rear_(0), count_(0) {
        buffer_ = new TArray<FColor>[capacity_];
    }

    ~BoundedBuffer() {
        delete[] buffer_;
    }

    void Deposit(TArray<FColor> data) {
        std::unique_lock<std::mutex> l(lock_);

        not_full_.wait(l, [this]() {return count_ != capacity_; });

        buffer_[rear_] = data;
        rear_ = (rear_ + 1) % capacity_;
        ++count_;

        l.unlock();
        not_empty_.notify_one();
    }

    TArray<FColor> Fetch() {
        std::unique_lock<std::mutex> l(lock_);

        not_empty_.wait(l, [this]() {return count_ != 0; });

        TArray<FColor> result = buffer_[front_];
        front_ = (front_ + 1) % capacity_;
        --count_;

        l.unlock();
        not_full_.notify_one();

        return result;
    }
};


//========================================================================

class VideoManager
{
public:

    static VideoManager* GetInstance();
    static void ReleaseInstance();

    void ReadPixels();
    void SendPixels();
    
    void Connect(const FString& IP_, const int32 Port_);
    void Disconnect();
    bool IsConnected();

    void    SetWorld(UWorld* world) { world_ = world; };
    UWorld* GetWorld() { return world_; };

protected:
    VideoManager();
    ~VideoManager();

private:
    unsigned long JpegCompress(void* lpBmpBuffer, int nWidth, int nHeight, int quality, unsigned char*& ppJpegBuffer);

private:

    UWorld* world_              = nullptr;

    BoundedBuffer*  cache_      = nullptr;
    std::thread*    thread_     = nullptr;
    bool            cancel_     = false;

    // ZMQ
    zmq::context_t* context_    = nullptr;
    zmq::socket_t*  socket_     = nullptr;
    FString         address_;

    // Pixel info
    TArray<uint8> image_data_;
};
