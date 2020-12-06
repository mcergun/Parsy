#include "DataPosition.h"

DataPosition::DataPosition(uint32_t pos, DataLengthUnit posUnit, uint32_t size, DataLengthUnit sizeUnit) :
    Offset(pos), OffsetUnit(posUnit), Size(size), SizeUnit(sizeUnit)
{
}

DataPosition::DataPosition(uint32_t pos, uint32_t size, DataLengthUnit commonUnit) :
    Offset(pos), OffsetUnit(commonUnit), Size(size), SizeUnit(commonUnit)
{
}

DataPosition::DataPosition() :
    Offset(0), OffsetUnit(DataLengthUnit::InBytes), Size(0), SizeUnit(DataLengthUnit::InBytes)
{
}

DataLengthUnit DataPosition::GetOffsetUnit() const
{
    return OffsetUnit;
}

uint32_t DataPosition::GetOffset(DataLengthUnit unit) const
{
    uint32_t ret = 0;
    if (unit == OffsetUnit)
    {
        ret = Offset;
    }
    else
    {
        if (unit == DataLengthUnit::InBits)
        {
            ret = Offset * BYTES_TO_BITS;
        }
        else
        {
            ret = Offset / BYTES_TO_BITS;
        }
    }
    return ret;
}

uint32_t DataPosition::GetOffset() const
{
    return Offset;
}

DataLengthUnit DataPosition::GetSizeUnit() const
{
    return SizeUnit;
}

uint32_t DataPosition::GetSize(DataLengthUnit unit) const
{
    uint32_t ret = 0;
    if (unit == SizeUnit)
    {
        ret = Size;
    }
    else
    {
        if (unit == DataLengthUnit::InBits)
        {
            ret = Size * BYTES_TO_BITS;
        }
        else
        {
            ret = Size / BYTES_TO_BITS;
        }
    }
    return ret;
}

uint32_t DataPosition::GetSize() const
{
    return Size;
}

void DataPosition::SetOffsetUnit(DataLengthUnit unit)
{
    OffsetUnit = unit;
}

void DataPosition::SetOffset(uint32_t offset)
{
    Offset = offset;
}

void DataPosition::SetSizeUnit(DataLengthUnit unit)
{
    SizeUnit = unit;
}

void DataPosition::SetSize(uint32_t size)
{
    Size = size;
}
