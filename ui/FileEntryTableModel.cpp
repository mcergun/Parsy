#include <BitGrabber.h>
#include <StringGrabber.h>
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

    BitGrabber bg(Endianness::BigEndian);
    StringGrabber sg;
    uint32_t i = 0;
    char *buf = FillTheFile();
    auto ext = FileEntry("Extension", sg.GetString(buf, i));
    FileDataList.Entries.push_back(ext);
    i += (strlen(buf + i) + 1) * BYTES_TO_BITS;

    auto ver = FileEntry("Version", bg.GrabU32(buf, i, 4 * BYTES_TO_BITS), EntryType::Unsigned32);
    FileDataList.Entries.push_back(ver);
    i += 4 * BYTES_TO_BITS;

    auto cnt = FileEntry("FileCount", bg.GrabU8(buf, i, 5), EntryType::Unsigned8);
    FileDataList.Entries.push_back(cnt);
    i += BYTES_TO_BITS;

    auto fl1 = FileEntry("File1", sg.GetString(buf, i / BYTES_TO_BITS));
    FileDataList.Entries.push_back(fl1);
    i += (fl1.GetStringValue().length() + 1) * BYTES_TO_BITS;

    auto fl2 = FileEntry("File2", sg.GetString(buf, i / BYTES_TO_BITS));
    FileDataList.Entries.push_back(fl2);
    i += (fl2.GetStringValue().length() + 1) * BYTES_TO_BITS;

    auto fl3 = FileEntry("File3", sg.GetString(buf, i / BYTES_TO_BITS));
    FileDataList.Entries.push_back(fl3);
    i += (fl3.GetStringValue().length() + 1) * BYTES_TO_BITS;
}

int FileEntryTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return FileDataList.Entries.size();
}

int FileEntryTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant FileEntryTableModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 2:
            ret = getFileEntryValue(index.row());
            break;
        case 1:
            ret = getFileEntryType(index.row());
            break;
        case 0:
            ret = getFileEntryName(index.row());
            break;
        default:
            ret = "Invalid";
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
        case 2:
            ret = "Value";
            break;
        case 1:
            ret = "Type";
            break;
        case 0:
            ret = "Name";
            break;
        default:
            ret = "INVALID";
            break;
        }
    }
    return ret;
}

void FileEntryTableModel::addNewItem(QString &name)
{
    FileEntry fe(name.toStdString());
    emit layoutAboutToBeChanged();
    FileDataList.Entries.push_back(fe);
    emit layoutChanged();
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
        const FileEntry &fe = FileDataList.Entries[idx];
        switch (fe.GetType())
        {
        case EntryType::Signed8:
            ret = "8 Bit Signed Number";
            break;
        case EntryType::Signed16:
            ret = "16 Bit Signed Number";
            break;
        case EntryType::Signed32:
            ret = "32 Bit Signed Number";
            break;
        case EntryType::Signed64:
            ret = "64 Bit Signed Number";
            break;
        case EntryType::Unsigned8:
            ret = "8 Bit Unsigned Number";
            break;
        case EntryType::Unsigned16:
            ret = "16 Bit Unsigned Number";
            break;
        case EntryType::Unsigned32:
            ret = "32 Bit Unsigned Number";
            break;
        case EntryType::Unsigned64:
            ret = "64 Bit Unsigned Number";
            break;
        case EntryType::Pointer:
            ret = "Pointer";
            break;
        case EntryType::String:
            ret = "String";
            break;
        default:
            break;
        }
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
