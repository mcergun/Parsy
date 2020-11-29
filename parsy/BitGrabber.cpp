#include "BitGrabber.h"

BitGrabber::BitGrabber(Endianness srcEndn) :
    SystemEndianness(GetEndianness()), SourceEndianness(srcEndn)
{
}

uint64_t BitGrabber::GrabU64(const char* buf, uint32_t offset, uint32_t count)
{
    uint64_t out = 0;
    GrabBuf(reinterpret_cast<char*>(&out), buf, offset, count);
    if (SystemEndianness != SourceEndianness)
    {
        out = SWAP64(out);
    }
    return out;
}

uint32_t BitGrabber::GrabU32(const char *buf, uint32_t offset, uint32_t count)
{
    uint32_t out = 0;
    GrabBuf(reinterpret_cast<char *>(&out), buf, offset, count);
    if (SystemEndianness != SourceEndianness)
    {
        out = SWAP32(out);
    }
    return out;
}

uint16_t BitGrabber::GrabU16(const char *buf, uint32_t offset, uint32_t count)
{
    uint16_t out = 0;
    GrabBuf(reinterpret_cast<char*>(&out), buf, offset, count);
    if (SystemEndianness != SourceEndianness)
    {
        out = SWAP16(out);
    }
    return out;
}

uint8_t BitGrabber::GrabU8(const char *buf, uint32_t offset, uint32_t count)
{
    uint8_t out = 0;
    GrabBuf(reinterpret_cast<char*>(&out), buf, offset, count);
    return out;
}

void BitGrabber::GrabBuf(char *dstBuf, const char *srcBuf, uint32_t offset, uint32_t count)
{
    const uint32_t ls = (offset + count) % BYTE_SIZE;
    const uint32_t rs = BYTE_SIZE - ls;
    const uint32_t ti = (offset + count) / 8;
    uint8_t rm = FULL_BYTE << rs;
    uint8_t lm = FULL_BYTE >> ls;
    uint32_t rmn = count;
    while (rmn > 0)
    {
        uint32_t i = (offset + rmn) / BYTE_SIZE;
        uint8_t b = 0;
        if (rmn > BYTE_SIZE)
        {
            b = MaskThenShift(srcBuf[i], rm, rs, false);
            b |= MaskThenShift(srcBuf[i - 1], lm, ls, true);
            rmn -= BYTE_SIZE;
        }
        else
        {
            rm = GenerateMask(rs, rmn, true);
            b = MaskThenShift(srcBuf[i], rm, rs, false);
            rmn = rmn > ls ? (rmn - ls) : 0;
            if (rmn > 0)
            {
                lm = GenerateMask(0, rmn, true);
                b |= MaskThenShift(srcBuf[i - 1], lm, ls, true);
                rmn = 0;
            }
        }
        dstBuf[ti - i] = b;
    }
}

inline uint8_t BitGrabber::MaskThenShift(uint8_t b, uint8_t m, uint8_t s, bool toLeft)
{
    b = (b & m);
    b = toLeft ? b << s : b >> s;
    return b;
}

uint8_t BitGrabber::GenerateMask(uint8_t pos, uint8_t count, bool toLeft)
{
    uint8_t mask = FULL_BYTE >> (BYTE_SIZE - count);
    mask = toLeft ? mask << pos : mask << (pos - count + 1);
    return mask;
}