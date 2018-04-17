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



    