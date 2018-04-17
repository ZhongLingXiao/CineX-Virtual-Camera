#pragma once

    struct CameraData {
        float X 				= 0; // forward
        float Y 				= 0; // right
        float Z 				= 0; // up
        float Pitch 			= 0; // Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down)
        float Roll 				= 0; // Rotation around the forward axis (around X axis), Tilting your head, 0=Straight, +Clockwise, -CCW.
        float Yaw 				= 0; // Rotation around the up axis (around Z axis), Running in circles 0=East, +North, -South.
        float Focus 			= 0;
        float Zoom 				= 0;
        //uint32 PacketNumber      = 0;
    };


    struct PixelData {
        int32   Width       = 1920;
        int32   Height      = 1080;
        int32   ElementNum  = 4; // RGBA
        uint8*  RawData     = nullptr;

        PixelData() { RawData = new uint8[Width*Height*ElementNum]; };
        ~PixelData() { delete RawData; RawData = nullptr; };

        void operator = (const PixelData& data) {
            if (this->RawData != nullptr) {
                delete[] RawData;
                RawData = nullptr;
            }
        
            this->Width = data.Width;
            this->Height = data.Height;
            this->RawData = new uint8[Width*Height*ElementNum];
            memcpy(RawData, data.RawData, Width*Height*ElementNum);
        };
    };


    