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
    DataLengthUnit GetOffsetUnit() const;
    uint32_t GetOffset(DataLengthUnit unit) const;
    uint32_t GetOffset() const;
    DataLengthUnit GetSizeUnit() const;
    uint32_t GetSize(DataLengthUnit unit) const;
    uint32_t GetSize() const;

    void SetOffsetUnit(DataLengthUnit unit);
    void SetOffset(uint32_t offset);
    void SetSizeUnit(DataLengthUnit unit);
    void SetSize(uint32_t size);

private:
    uint32_t Offset;
    DataLengthUnit OffsetUnit;
    uint32_t Size;
    DataLengthUnit SizeUnit;
};

#endif // DATADEFS_H
