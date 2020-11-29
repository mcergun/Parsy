#ifndef _RANDOM_FILE_H_
#define _RANDOM_FILE_H_

#include <cstdint>

struct RandomFile
{
    uint32_t Version;
    uint16_t FileHeaderSize;
    uint16_t RecordHeaderSize;
    uint16_t NumberOfRecords;
};

#endif