#include <cstring>
#include "StringGrabber.h"

StringGrabber::StringGrabber()
{
}

StringGrabber::~StringGrabber()
{
    if (InternalBuffer != nullptr)
    {
        delete[] InternalBuffer;
    }
}

const char* StringGrabber::GetString(const char* srcBuf, uint32_t offset, uint32_t maxLen)
{
    uint32_t len = std::strlen(srcBuf + offset);
    if (maxLen != 0 && len > maxLen)
    {
        if (len >= BufferSize)
        {
            ResizeBuffer(len);
        }
        std::strncpy(InternalBuffer, srcBuf + offset, maxLen);
        InternalBuffer[maxLen] = 0;
    }
    else
    {
        std::strcpy(InternalBuffer, srcBuf + offset);
    }
    return InternalBuffer;
}

void StringGrabber::ResizeBuffer(uint32_t sz)
{
    delete[] InternalBuffer;
    BufferSize = sz + 1;
    InternalBuffer = new char[sz + 1];
}
