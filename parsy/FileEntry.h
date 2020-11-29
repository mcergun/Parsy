#ifndef _FILE_ENTRY_H_
#define _FILE_ENTRY_H_

#include <cstdint>
#include <string>
#include <vector>
#include "DllExports.h"

union NumericValue
{
	NumericValue(uint64_t val)
	{
		U64 = val;
	}

	NumericValue()
	{
		U64 = 0;
	}

	int64_t I64;
	int32_t I32;
	int16_t I16;
	int8_t I8;
	uint64_t U64;
	uint32_t U32;
	uint16_t U16;
	uint8_t U8;
};

enum class EntryType
{
	Signed8,
	Signed16,
	Signed32,
	Signed64,
	Unsigned8,
	Unsigned16,
	Unsigned32,
	Unsigned64,
	Pointer,
	String
};

struct EntryValue
{
	EntryType Type;
	NumericValue Numeric;
	std::string String;
};

class DLLEXPORT FileEntry
{
public:
	FileEntry(std::string name);
	// Generates a generic file entry of "type"
	FileEntry(std::string name, EntryType type);
	// Generates a string file entry with "name" and "value"
	FileEntry(std::string name, std::string value);
	// Generates a numeric file entry with "name" and "value" and "type"
	FileEntry(std::string name, uint64_t value, EntryType type);

	const std::string& GetName() const;
	const EntryType GetType() const;
	const NumericValue& GetNumericValue() const;
	const std::string& GetStringValue() const;
	void SetName(std::string& name);
	void SetName(const char* name);
	void SetType(EntryType type);
	void SetNumericValue(NumericValue num);
	void SetNumericValue(NumericValue num, EntryType type);
	void SetStringValue(std::string& str);
	void SetStringValue(const char* str);

private:
	std::string Name;
	EntryValue Value;
};

class FileData
{
public:
	std::vector<FileEntry> Entries;
};

#endif