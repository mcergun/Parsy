#include "FileEntry.h"

FileEntry::FileEntry(std::string name, DataPosition pos) :
    Name(name), Position(pos)
{
}

FileEntry::FileEntry(std::string name, DataPosition pos, EntryType type) :
    Name(name), Position(pos)
{
	Value.Type = type;
}

FileEntry::FileEntry(std::string name, DataPosition pos, std::string value) :
    Name(name), Position(pos)
{
	SetStringValue(value);
}

FileEntry::FileEntry(std::string name, DataPosition pos, uint64_t value, EntryType type) :
    Name(name), Position(pos)
{
	Value.Type = type;
	SetNumericValue(value);
}

const std::string& FileEntry::GetName() const
{
	return Name;
}

const EntryType FileEntry::GetType() const
{
	return Value.Type;
}

const NumericValue& FileEntry::GetNumericValue() const
{
	return Value.Numeric;
}

const std::string& FileEntry::GetStringValue() const
{
	return Value.String;
}

const DataPosition& FileEntry::GetPosition() const
{
    return Position;
}

void FileEntry::SetName(std::string& name)
{
	Name = name;
}

void FileEntry::SetName(const char* name)
{
	Name = name;
}

void FileEntry::SetType(EntryType type)
{
	Value.Type = type;
}

void FileEntry::SetNumericValue(NumericValue num)
{
	Value.Numeric = num;
	Value.String.clear();
}

void FileEntry::SetNumericValue(NumericValue num, EntryType type)
{
	Value.Numeric = num;
	Value.String.clear();
	Value.Type = type;
}

void FileEntry::SetStringValue(std::string& str)
{
	Value.String = str;
	Value.Numeric = 0;
	Value.Type = EntryType::String;
}

void FileEntry::SetStringValue(const char* str)
{
	Value.String = str;
}

void FileEntry::SetPosition(DataPosition pos)
{
    Position = pos;
}
