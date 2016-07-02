/*
Copyright (c) 2016,
Dan Bethell, Johannes Saam, Vahan Sosoyan, Brian Scherbinski.
All rights reserved. See COPYING.txt for more details.
*/

#ifndef ATON_DATA_H_
#define ATON_DATA_H_

#include <vector>

namespace aton
{
    // Represents image information passed from Client to Server
    // This class wraps up the data sent from Client to Server. When calling
    // Client::openImage() a Data object should first be constructed that
    // specifies the full image dimensions.
    // E.g. Data( 0, 0, 320, 240, 3 );
    // When sending actually pixel information it should be constructed using
    // values that represent the chunk of pixels being sent.
    // E.g. Data( 15, 15, 16, 16, 3, myPixelPointer );
    class Data
    {
    friend class Client;
    friend class Server;
    public:
        Data(const int& x = 0,
             const int& y = 0,
             const int& width = 0,
             const int& height = 0,
             const long long& rArea = 0,
             const int& version = 0,
             const float& currentFrame = 0.0f,
             const int& spp = 0,
             const long long& ram = 0,
             const int& time = 0,
             const char* aovName = NULL,
             const float* data = NULL);
        
        ~Data();
        
        // The 'type' of message this Data represents
        // 0: image open
        // 1: pixels
        // 2: image close
        const int type() const { return mType; }

        // Get x position
        const int& x() const { return mX; }
        
        // Get y position
        const int& y() const { return mY; }
        
        // Get width
        const int& width() const { return mWidth; }
        
        // Get height
        const int& height() const { return mHeight; }
        
        // Get area of the render region
        const long long& rArea() const { return mRArea; }
        
        // Version number
        const int& version() const { return mVersion; }
        
        // Current frame
        const float& currentFrame() const { return mCurrentFrame; }
        
        // Samples-per-pixel, aka channel depth
        const int& spp() const { return mSpp; }
        
        // Taken memory while rendering
        const long long& ram() const { return mRam; }
        
        // Taken time while rendering
        const unsigned int& time() const { return mTime; }
        
        // Get Aov name
        const char* aovName() const { return mAovName; }
        
        // Deallocate Aov name
        void deAllocAovName();
        
        // Pointer to pixel data owned by the display driver (client-side)
        const float* data() const { return mpData; }
        
        // Reference to pixel data owned by this object (server-side)
        const std::vector<float>& pixels() { return mPixelStore; }
        
    private:
        // What type of data is this?
        int mType;

        // X & Y position
        int mX, mY, mWidth, mHeight, mSpp;

        // Version number
        int mVersion;

        // Current frame
        float mCurrentFrame;

        // Width, height, num channels (samples)
        unsigned int mTime;

        long long mRArea, mRam;

        const char *mAovName;

        // Our pixel data pointer (for driver-owned pixels)
        float *mpData;

        // Our persistent pixel storage (for Data-owned pixels)
        std::vector<float> mPixelStore;
    };
}

#endif // ATON_DATA_H_
