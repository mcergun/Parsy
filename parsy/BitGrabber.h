#ifndef _BIT_GRABBER_H_
#define _BIT_GRABBER_H_


#include <stdint.h>
#include "DllExports.h"
#include "EndianConverter.h"

#define BYTES_TO_BITS 8

class DLLEXPORT BitGrabber
{
public:
	BitGrabber(Endianness srcEndn);
	uint64_t GrabU64(const char* buf, uint32_t offset, uint32_t count);
	uint32_t GrabU32(const char *srcBuf, uint32_t offset, uint32_t count);
	uint16_t GrabU16(const char *srcBuf, uint32_t offset, uint32_t count);
	uint8_t GrabU8(const char *srcBuf, uint32_t offset, uint32_t count);
	void GrabBuf(char *dstBuf, const char * srcBuf, uint32_t offset, uint32_t count);

private:
	inline uint8_t MaskThenShift(uint8_t b, uint8_t m, uint8_t s, bool toLeft);
	uint8_t GenerateMask(uint8_t pos, uint8_t count, bool toLeft);

	static constexpr uint8_t BYTE_SIZE = 8;
	static constexpr uint8_t FULL_BYTE = 0xFF;

	Endianness SystemEndianness = Endianness::LittleEndian;
	Endianness SourceEndianness = Endianness::LittleEndian;
};

#endif