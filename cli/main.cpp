#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <BitGrabber.h>
#include <StringGrabber.h>
#include <FileEntry.h>

char *FillTheFile()
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

    FILE* fp = fopen(FNAME.c_str(), "w+");
    fwrite(fbuf, 1, i, fp);
    fclose(fp);
    return fbuf;
}

void TestAndPrintResults()
{
    // 1000 1001 1010 1011 1100 1101 1110 1111
    char buf[4] = { 0 };
    *(reinterpret_cast<uint32_t*>(buf)) = 0xefcdab89;
    // 2, 4		= 0x02
    // 2, 7		= 0x13
    // 2, 5		= 0x04
    // 3, 18	= 0x013579
    // 3, 7		= 0x26
    // 9, 11	= 0x02bc
    // 7, 10	= 0x357

    BitGrabber bg(Endianness::LittleEndian);

    auto out = bg.GrabU32(buf, 2, 4);
    std::cout << std::hex;
    std::cout << out << std::endl;
    out = bg.GrabU8(buf, 2, 7);
    std::cout << out << std::endl;
    out = bg.GrabU8(buf, 2, 5);
    std::cout << out << std::endl;
    out = bg.GrabU32(buf, 3, 18);
    std::cout << out << std::endl;
    out = bg.GrabU8(buf, 3, 7);
    std::cout << out << std::endl;
    out = bg.GrabU16(buf, 16, 16);
    std::cout << out << std::endl;
    out = bg.GrabU16(buf, 7, 10);
    std::cout << out << std::endl;

    char dstBuf[4] = { 0 };
    bg.GrabBuf(dstBuf, buf, 3, 18);
    std::cout << (unsigned int)dstBuf[0] << ", "
        << (unsigned int)dstBuf[1] << ", "
        << (unsigned int)dstBuf[2] << std::endl;
}

void PrintValue(FileEntry &fe)
{
    std::cout << fe.GetName() << ": ";
    switch (fe.GetType()) {
    case EntryType::String:
        std::cout << fe.GetStringValue() << std::endl;
        break;
    case EntryType::Pointer:
    case EntryType::Signed64:
    case EntryType::Unsigned64:
        std::cout << std::hex << std::setfill('0') << std::setw(16);
        std::cout << fe.GetNumericValue().U64 << std::endl;
        break;
    case EntryType::Signed32:
    case EntryType::Unsigned32:
        std::cout << std::hex << std::setfill('0') << std::setw(8);
        std::cout << fe.GetNumericValue().U32 << std::endl;
        break;
    case EntryType::Signed16:
    case EntryType::Unsigned16:
        std::cout << std::hex << std::setfill('0') << std::setw(4);
        std::cout << fe.GetNumericValue().U16 << std::endl;
        break;
    default:
        std::cout << std::hex << std::setfill('0') << std::setw(2);
        std::cout << static_cast<uint32_t>(fe.GetNumericValue().U8) << std::endl;
        break;
    }
}

int main(int argc, char** argv)
{
    //TestAndPrintResults();

    char* buf = FillTheFile();
    BitGrabber bg(Endianness::BigEndian);
    StringGrabber sg;
    FileData fd;
    uint32_t i = 0;
    DataPosition pos = {4, DataLengthUnit::InBytes, 0, DataLengthUnit::InBytes};
    auto ext = FileEntry("Extension", pos, sg.GetString(buf, i));
    fd.Entries.push_back(ext);

    i += (strlen(buf + i) + 1) * BYTES_TO_BITS;
    pos = {i, DataLengthUnit::InBits, 4, DataLengthUnit::InBytes};
    auto ver = FileEntry("Version", pos, bg.GrabU32(buf, pos), EntryType::Unsigned32);
    fd.Entries.push_back(ver);
    i += 4 * BYTES_TO_BITS;

    pos = {i, DataLengthUnit::InBits, 5, DataLengthUnit::InBits};
    auto cnt = FileEntry("FileCount", pos, bg.GrabU8(buf, pos), EntryType::Unsigned8);
    fd.Entries.push_back(cnt);
    i += BYTES_TO_BITS;

    pos = {i / BYTES_TO_BITS, DataLengthUnit::InBytes, 0, DataLengthUnit::InBytes};
    auto fl1 = FileEntry("File1", pos, sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl1);
    i += (fl1.GetStringValue().length() + 1) * BYTES_TO_BITS;

    pos = {i / BYTES_TO_BITS, DataLengthUnit::InBytes, 0, DataLengthUnit::InBytes};
    auto fl2 = FileEntry("File2", pos, sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl2);
    i += (fl2.GetStringValue().length() + 1) * BYTES_TO_BITS;

    pos = {i / BYTES_TO_BITS, DataLengthUnit::InBytes, 0, DataLengthUnit::InBytes};
    auto fl3 = FileEntry("File3", pos, sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl3);
    i += (fl3.GetStringValue().length() + 1) * BYTES_TO_BITS;

    PrintValue(ext);
    PrintValue(ver);
    PrintValue(cnt);
    PrintValue(fl1);
    PrintValue(fl2);
    PrintValue(fl3);
    return 0;
}
