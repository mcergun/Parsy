#include <BitGrabber.h>
#include <StringGrabber.h>
#include <QFont>
#include <QDebug>
#include "FileEntryTableModel.h"

static char *FillTheFile()
{
    const std::string EXTENSION = "MCE";
    const std::string FNAME = "testfile." + EXTENSION;
    const uint32_t VERSION = SWAP32(0x20201116ul);
    const uint8_t FILE_COUNT = 3 << 3; // I want this to take 5 bits
    const std::string FILE_LIST[FILE_COUNT] = { "Mert", "Can", "Ergun" };
    char *fbuf = new char[256];
    std::memset(fbuf, 0, 256);
    size_t i = 0;
    std::strcpy(fbuf, EXTENSION.c_str());
    i += EXTENSION.length() + 1;
    std::memcpy(fbuf + i, reinterpret_cast<const char*>(&VERSION), sizeof(VERSION));
    i += sizeof(VERSION);
    std::memcpy(fbuf + i, reinterpret_cast<const char*>(&FILE_COUNT), 1); // 5 bits
    i += 1;
    std::strcpy(fbuf + i, FILE_LIST[0].c_str());
    i += FILE_LIST[0].length() + 1;
    std::strcpy(fbuf + i, FILE_LIST[1].c_str());
    i += FILE_LIST[1].length() + 1;
    std::strcpy(fbuf + i, FILE_LIST[2].c_str());
    i += FILE_LIST[2].length() + 1;

//    FILE* fp = fopen(FNAME.c_str(), "w+");
//    fwrite(fbuf, 1, i, fp);
//    fclose(fp);
    return fbuf;
}

FileEntryTableModel::FileEntryTableModel(QObject *parent)
{
    Q_UNUSED(parent);

    // TODO: Remove this later and use actual file buffers
    SourceBuffer = FillTheFile();
    BufLen = 25;
    updateAllEntryValues();

    TypeToStringMap.insert(EntryType::Pointer,      "Pointer");
    TypeToStringMap.insert(EntryType::Signed16,     "INT16");
    TypeToStringMap.insert(EntryType::Signed32,     "INT32");
    TypeToStringMap.insert(EntryType::Signed64,     "INT64");
    TypeToStringMap.insert(EntryType::Signed8,      "INT8");
    TypeToStringMap.insert(EntryType::String,       "String");
    TypeToStringMap.insert(EntryType::Unsigned16,   "UINT16");
    TypeToStringMap.insert(EntryType::Unsigned32,   "UINT32");
    TypeToStringMap.insert(EntryType::Unsigned64,   "UINT64");
    TypeToStringMap.insert(EntryType::Unsigned8,    "UINT8");

    StringToTypeMap.insert("Pointer",   EntryType::Pointer);
    StringToTypeMap.insert("INT16",     EntryType::Signed16);
    StringToTypeMap.insert("INT32",     EntryType::Signed32);
    StringToTypeMap.insert("INT64",     EntryType::Signed64);
    StringToTypeMap.insert("INT8",      EntryType::Signed8);
    StringToTypeMap.insert("String",    EntryType::String);
    StringToTypeMap.insert("UINT16",    EntryType::Unsigned16);
    StringToTypeMap.insert("UINT32",    EntryType::Unsigned32);
    StringToTypeMap.insert("UINT64",    EntryType::Unsigned64);
    StringToTypeMap.insert("UINT8",     EntryType::Unsigned8);
}

int FileEntryTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return FileDataList.Entries.size();
}

int FileEntryTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
}

QVariant FileEntryTableModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    // Qt::DisplayRole for QTableView
    // Qt::EditRole for QDataWidgetMapper
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column()) {
        case FILE_ENTRY_LENGTH_UNIT_COLUMN:
            ret = getFileEntryLengthUnit(index.row());
            break;
        case FILE_ENTRY_OFFSET_UNIT_COLUMN:
            ret = getFileEntryOffsetUnit(index.row());
            break;
        case FILE_ENTRY_LENGTH_COLUMN:
            ret = getFileEntryLength(index.row());
            break;
        case FILE_ENTRY_OFFSET_COLUMN:
            ret = getFileEntryOffset(index.row());
            break;
        case FILE_ENTRY_VALUE_COLUMN:
            ret = getFileEntryValue(index.row());
            break;
        case FILE_ENTRY_TYPE_COLUMN:
            ret = getFileEntryType(index.row());
            break;
        case FILE_ENTRY_NAME_COLUMN:
            ret = getFileEntryName(index.row());
            break;
        default:
            ret = "INVALID";
            break;
        }
    }
    return ret;
}

QVariant FileEntryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant ret;
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case FILE_ENTRY_VALUE_COLUMN:
            ret = "Value";
            break;
        case FILE_ENTRY_TYPE_COLUMN:
            ret = "Type";
            break;
        case FILE_ENTRY_NAME_COLUMN:
            ret = "Name";
            break;
        default:
            ret = "INVALID";
            break;
        }
    }
    return ret;
}

// TODO: This method is getting HUGE, do something
bool FileEntryTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = false;
    if (role == Qt::EditRole)
    {
        FileEntry &fe = FileDataList.Entries[index.row()];
        switch (index.column())
        {
        case FILE_ENTRY_LENGTH_UNIT_COLUMN:
        {
            if (value == "Bits")
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetSizeUnit(DataLengthUnit::InBits);
                fe.SetPosition(pos);
            }
            else if (value == "Bytes")
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetSizeUnit(DataLengthUnit::InBytes);
                fe.SetPosition(pos);
            }
            // Else, no data to save
            break;
        }
        case FILE_ENTRY_OFFSET_UNIT_COLUMN:
        {
            if (value == "Bits")
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetOffsetUnit(DataLengthUnit::InBits);
                fe.SetPosition(pos);
            }
            else if (value == "Bytes")
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetOffsetUnit(DataLengthUnit::InBytes);
                fe.SetPosition(pos);
            }
            // Else, no data to save
            break;
        }
        case FILE_ENTRY_LENGTH_COLUMN:
        {
            bool successful = false;
            uint32_t newLen = value.toUInt(&successful);
            if (successful)
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetSize(newLen);
                fe.SetPosition(pos);
            }
            break;
        }
        case FILE_ENTRY_OFFSET_COLUMN:
        {
            bool successful = false;
            uint32_t newOffset = value.toUInt(&successful);
            if (successful)
            {
                ret = true;
                DataPosition pos = fe.GetPosition();
                pos.SetOffset(newOffset);
                fe.SetPosition(pos);
            }
            break;
        }
        case FILE_ENTRY_TYPE_COLUMN:
        {
            EntryType newType = StringToTypeMap.value(value.toString());
            fe.SetType(newType);
            ret = true;
            break;
        }
        case FILE_ENTRY_NAME_COLUMN:
        {
            std::string newName = value.toString().toStdString();
            fe.SetName(newName);
            ret = true;
            break;
        }
        case FILE_ENTRY_VALUE_COLUMN:
        default:
            break;
        }
    }
    if (ret)
    {
        emit dataChanged(index, index);
    }
    return ret;
}

//Qt::ItemFlags FileEntryTableModel::flags(const QModelIndex &index) const
//{
//    return Qt::NoItemFlags;
//}

void FileEntryTableModel::addNewItem(QString &name, QString &type, uint32_t offset, uint32_t length, int offsUnit, int lenUnit)
{
    DataLengthUnit offsetUnit = static_cast<DataLengthUnit>(offsUnit);
    DataLengthUnit lengthUnit = static_cast<DataLengthUnit>(lenUnit);
    DataPosition pos(offset, offsetUnit, length, lengthUnit);
    EntryType typ = StringToTypeMap.value(type);
    if (pos.GetOffset() == 0)
    {
        countIndex();
        if (typ == EntryType::String)
        {
            // Need to align strings to a byte start
            uint32_t bs = (CurrentBitIdx + BYTES_TO_BITS - 1) / BYTES_TO_BITS;
            pos.SetOffset(bs);
            pos.SetOffsetUnit(DataLengthUnit::InBytes);
        }
        else
        {
            pos.SetOffset(CurrentBitIdx);
            pos.SetOffsetUnit(DataLengthUnit::InBits);
        }
    }
    FileEntry fe(name.toStdString(), pos, typ);
    emit layoutAboutToBeChanged();
    FileDataList.Entries.push_back(fe);
    updateAllEntryValues();
    emit layoutChanged();
}

void FileEntryTableModel::setSourceBuffer(char *buf)
{
    SourceBuffer = buf;
}

void FileEntryTableModel::updateAllEntryValues()
{
    BitGrabber bg(Endianness::BigEndian);
    StringGrabber sg;
    uint32_t i = 0;
    for (FileEntry &fe : FileDataList.Entries)
    {
        DataPosition pos = fe.GetPosition();
        updateEntryValue(fe);
        switch (fe.GetType())
        {
        case EntryType::String:
            i += fe.GetStringValue().length() * BYTES_TO_BITS;
            break;
        default:
            i += fe.GetPosition().GetSize(DataLengthUnit::InBits);
            break;
        }
    }
}

void FileEntryTableModel::updateEntryValue(uint32_t idx)
{
    if (idx < FileDataList.Entries.size())
    {
        FileEntry &fe = FileDataList.Entries[idx];
        updateEntryValue(fe);
    }
}

void FileEntryTableModel::getBufferAndLen(char **buf, uint32_t *len)
{
    *buf = SourceBuffer;
    *len = BufLen;
}

QString FileEntryTableModel::getFileEntryValue(uint32_t idx) const
{
    QString str;
    if (idx < FileDataList.Entries.size())
    {
        const FileEntry &fe = FileDataList.Entries[idx];
        switch (fe.GetType())
        {
        case EntryType::String:
            str = QString::fromStdString(fe.GetStringValue());
            break;
        case EntryType::Pointer:
        case EntryType::Unsigned64:
        case EntryType::Signed64:
            str = QStringLiteral("0x%1").arg(fe.GetNumericValue().U64, 16, 16, QLatin1Char('0'));
            break;
        case EntryType::Unsigned32:
        case EntryType::Signed32:
            str = QStringLiteral("0x%1").arg(fe.GetNumericValue().U32, 8, 16, QLatin1Char('0'));
            break;
        case EntryType::Unsigned16:
        case EntryType::Signed16:
            str = QStringLiteral("0x%1").arg(fe.GetNumericValue().U16, 4, 16, QLatin1Char('0'));
            break;
        case EntryType::Unsigned8:
        case EntryType::Signed8:
            str = QStringLiteral("0x%1").arg(fe.GetNumericValue().U8, 2, 16, QLatin1Char('0'));
            break;
        }
    }
    return str;
}

QString FileEntryTableModel::getFileEntryType(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        ret = TypeToStringMap.value(FileDataList.Entries[idx].GetType());
    }
    return ret;
}

QString FileEntryTableModel::getFileEntryName(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        ret = QString::fromStdString(FileDataList.Entries[idx].GetName());
    }
    return ret;
}


QString FileEntryTableModel::getFileEntryOffset(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        ret = QStringLiteral("%1").arg(FileDataList.Entries[idx].GetPosition().GetOffset());
    }
    return ret;
}

QString FileEntryTableModel::getFileEntryLength(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        ret = QStringLiteral("%1").arg(FileDataList.Entries[idx].GetPosition().GetSize());
    }
    return ret;
}

QString FileEntryTableModel::getFileEntryOffsetUnit(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        DataPosition pos = FileDataList.Entries[idx].GetPosition();
        ret += pos.GetOffsetUnit() == DataLengthUnit::InBits ? "Bits" : "Bytes";
    }
    return ret;
}

QString FileEntryTableModel::getFileEntryLengthUnit(uint32_t idx) const
{
    QString ret;
    if (idx < FileDataList.Entries.size())
    {
        DataPosition pos = FileDataList.Entries[idx].GetPosition();
        ret += pos.GetSizeUnit() == DataLengthUnit::InBits ? "Bits" : "Bytes";
    }
    return ret;
}

void FileEntryTableModel::updateEntryValue(FileEntry &fe)
{
    StringGrabber sg;
    BitGrabber bg(Endianness::BigEndian);
    DataPosition pos = fe.GetPosition();
    switch (fe.GetType())
    {
    case EntryType::String:
        fe.SetStringValue(sg.GetString(SourceBuffer, pos.GetOffset(DataLengthUnit::InBytes)));
        break;
    case EntryType::Unsigned8:
    case EntryType::Signed8:
        fe.SetNumericValue(bg.GrabU8(SourceBuffer, pos), fe.GetType());
        break;
    case EntryType::Unsigned16:
    case EntryType::Signed16:
        fe.SetNumericValue(bg.GrabU16(SourceBuffer, pos), fe.GetType());
        break;
    case EntryType::Unsigned32:
    case EntryType::Signed32:
        fe.SetNumericValue(bg.GrabU32(SourceBuffer, pos), fe.GetType());
        break;
    case EntryType::Unsigned64:
    case EntryType::Signed64:
    case EntryType::Pointer:
    default:
        fe.SetNumericValue(bg.GrabU64(SourceBuffer, pos), fe.GetType());
        break;
    }
}

void FileEntryTableModel::countIndex()
{
    CurrentBitIdx = 0;
    for (FileEntry &fe : FileDataList.Entries)
    {
        if (fe.GetType() == EntryType::String)
        {
            if (fe.GetPosition().GetSize() == 0)
            {
                CurrentBitIdx += (fe.GetStringValue().length() + 1) * BYTES_TO_BITS;
            }
            else
            {
                CurrentBitIdx += fe.GetPosition().GetSize(DataLengthUnit::InBits);
            }
        }
        else
        {
            CurrentBitIdx += fe.GetPosition().GetSize(DataLengthUnit::InBits);
        }
    }
}
