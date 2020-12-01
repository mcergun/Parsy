#ifndef DATADEFS_H
#define DATADEFS_H

#include <cstdint>
#include "DllExports.h"

#define BYTES_TO_BITS 8

enum class DataLengthUnit
{
    InBits,
    InBytes,
};

struct DLLEXPORT DataPosition
{
public:
    DataPosition(uint32_t pos, DataLengthUnit posUnit, uint32_t size, DataLengthUnit sizeUnit);
    DataPosition(uint32_t pos, uint32_t size, DataLengthUnit commonUnit);
    DataPosition();
    uint32_t GetPosition(DataLengthUnit unit) const;
    uint32_t GetSize(DataLengthUnit unit) const;
    uint32_t GetPosition() const;
    uint32_t GetSize() const;
    DataLengthUnit GetPositionUnit() const;
    DataLengthUnit GetSizeUnit() const;

private:
    uint32_t Position;
    DataLengthUnit PositionUnit;
    uint32_t Size;
    DataLengthUnit SizeUnit;
};

#endif // DATADEFS_H
