#include <cstring>
#include <string>
#include <BitGrabber.h>
#include <StringGrabber.h>
#include <FileEntry.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

//    FILE* fp = fopen(FNAME.c_str(), "w+");
//    fwrite(fbuf, 1, i, fp);
//    fclose(fp);
    return fbuf;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    BitGrabber bg(Endianness::BigEndian);
    StringGrabber sg;
    FileData fd;
    uint32_t i = 0;
    char *buf = FillTheFile();
    auto ext = FileEntry("Extension", sg.GetString(buf, i));
    fd.Entries.push_back(ext);
    i += (strlen(buf + i) + 1) * BYTES_TO_BITS;

    auto ver = FileEntry("Version", bg.GrabU32(buf, i, 4 * BYTES_TO_BITS), EntryType::Unsigned32);
    fd.Entries.push_back(ver);
    i += 4 * BYTES_TO_BITS;

    auto cnt = FileEntry("FileCount", bg.GrabU8(buf, i, 5), EntryType::Unsigned8);
    fd.Entries.push_back(cnt);
    i += BYTES_TO_BITS;

    auto fl1 = FileEntry("File1", sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl1);
    i += (fl1.GetStringValue().length() + 1) * BYTES_TO_BITS;

    auto fl2 = FileEntry("File2", sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl2);
    i += (fl2.GetStringValue().length() + 1) * BYTES_TO_BITS;

    auto fl3 = FileEntry("File3", sg.GetString(buf, i / BYTES_TO_BITS));
    fd.Entries.push_back(fl3);
    i += (fl3.GetStringValue().length() + 1) * BYTES_TO_BITS;
    QString numStr;
    ui->lblExt->setText(QString::fromStdString(ext.GetStringValue()));
    ui->lblVers->setText(numStr.setNum(ver.GetNumericValue().U32, 16));
    ui->lblCount->setText(numStr.setNum(cnt.GetNumericValue().U8, 16));
    ui->listFiles->addItem(QString::fromStdString(fl1.GetStringValue()));
    ui->listFiles->addItem(QString::fromStdString(fl2.GetStringValue()));
    ui->listFiles->addItem(QString::fromStdString(fl3.GetStringValue()));
}
