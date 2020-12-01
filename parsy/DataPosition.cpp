#include "DataPosition.h"

DataPosition::DataPosition(uint32_t pos, DataLengthUnit posUnit, uint32_t size, DataLengthUnit sizeUnit) :
    Position(pos), PositionUnit(posUnit), Size(size), SizeUnit(sizeUnit)
{
}

DataPosition::DataPosition(uint32_t pos, uint32_t size, DataLengthUnit commonUnit) :
    Position(pos), PositionUnit(commonUnit), Size(size), SizeUnit(commonUnit)
{
}

DataPosition::DataPosition() :
    Position(0), PositionUnit(DataLengthUnit::InBytes), Size(0), SizeUnit(DataLengthUnit::InBytes)
{
}

uint32_t DataPosition::GetPosition(DataLengthUnit unit) const
{
    uint32_t ret = 0;
    if (unit == PositionUnit)
    {
        ret = Position;
    }
    else
    {
        if (unit == DataLengthUnit::InBits)
        {
            ret = Position * BYTES_TO_BITS;
        }
        else
        {
            ret = Position / BYTES_TO_BITS;
        }
    }
    return ret;
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


uint32_t DataPosition::GetPosition() const
{
    return Position;
}

uint32_t DataPosition::GetSize() const
{
    return Size;
}

DataLengthUnit DataPosition::GetPositionUnit() const
{
    return PositionUnit;
}

DataLengthUnit DataPosition::GetSizeUnit() const
{
    return SizeUnit;
}
