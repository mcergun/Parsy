#include "FileEntry.h"

FileEntry::FileEntry(std::string name) :
	Name(name)
{
}

FileEntry::FileEntry(std::string name, EntryType type) :
	Name(name)
{
	Value.Type = type;
}

FileEntry::FileEntry(std::string name, std::string value) :
	Name(name)
{
	SetStringValue(value);
}

FileEntry::FileEntry(std::string name, uint64_t value, EntryType type) :
	Name(name)
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
