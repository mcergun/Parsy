#ifndef _FIELD_H_
#define _FIELD_H_

#include <cstdint>

union UIntField
{
    uint64_t U64;
    uint32_t U32;
    uint16_t U16;
    uint8_t U8;
};

union IntField
{
    int64_t U64;
    int32_t U32;
    int16_t U16;
    int8_t U8;
};

#endif