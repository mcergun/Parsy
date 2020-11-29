#ifndef _STRING_GRABBER_H_
#define _STRING_GRABBER_H_

#include <string>
#include "DllExports.h"

class DLLEXPORT StringGrabber
{
public:
	StringGrabber();
	~StringGrabber();
	const char* GetString(const char* srcBuf, uint32_t offset, uint32_t maxLen = 0);

	static constexpr uint32_t DEF_BUFFER_SIZE = 256;

private:
	void ResizeBuffer(uint32_t sz);

	uint32_t BufferSize = DEF_BUFFER_SIZE;
	char* InternalBuffer = new char[DEF_BUFFER_SIZE];
};

#endif
