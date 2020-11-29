#ifndef _ENDIAN_CONVERTER_H_
#define _ENDIAN_CONVERTER_H_

#define SWAP16(data) \
( (((data) >> 8) & 0x00FF) | (((data) << 8) & 0xFF00) )

#define SWAP32(data)   \
( (((data) >> 24) & 0x000000FF) | (((data) >>  8) & 0x0000FF00) | \
  (((data) <<  8) & 0x00FF0000) | (((data) << 24) & 0xFF000000) )

#define SWAP64(data)   \
( (((data) >> 56) & 0x00000000000000FF) | (((data) >> 40) & 0x000000000000FF00) | \
  (((data) >> 24) & 0x0000000000FF0000) | (((data) >>  8) & 0x00000000FF000000) | \
  (((data) <<  8) & 0x000000FF00000000) | (((data) << 24) & 0x0000FF0000000000) | \
  (((data) << 40) & 0x00FF000000000000) | (((data) << 56) & 0xFF00000000000000) )

enum class Endianness
{
	BigEndian,
	LittleEndian
};

inline bool IsLittleEndian()
{
	int i = 1;
	char b = *(reinterpret_cast<char*>(&i));
	return b == 0x1;
}

inline bool IsBigEndian()
{
	return !IsLittleEndian();
}

inline Endianness GetEndianness()
{
	return IsLittleEndian() ? Endianness::LittleEndian : Endianness::BigEndian;
}

#endif