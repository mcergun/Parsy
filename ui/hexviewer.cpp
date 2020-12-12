#include "hexviewer.h"
#include "ui_hexviewer.h"

HexViewer::HexViewer(QWidget *prnt) :
    ui(new Ui::HexViewer)
{
    setParent(prnt);
    ui->setupUi(this);
}

HexViewer::~HexViewer()
{
    delete ui;
}

void HexViewer::setText(QString text)
{
    ui->tbAscii->setText(text);
    auto byteArr = text.toUtf8();
    QString hex;
    for (auto b : byteArr)
    {
        QString hexB = QStringLiteral("0x%1").arg(b, 2, 16, QLatin1Char('0'));
        hex.append(b);
    }
    ui->tbHex->setText(hex);
}

void HexViewer::setText(const char *buf, uint32_t len)
{
    uint32_t bufLen = len / 8 + len + 3;
    char *str = new char[bufLen];
    std::memset(str, 0, bufLen);
    str[0] = '\r';
    str[1] = '\n';
    str[2] = replaceBrokenChar(buf[0]);
    for (uint32_t i = 1, j = 3; i < len; i++, j++)
    {
        str[j] = replaceBrokenChar(buf[i]);
        if (i % 16 == 0)
        {
            str[++j] = '\r';
            str[++j] = '\n';
        }
    }
    QString hexB(3);
    QString hexStr = "        0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  \r\n0x0000: ";
    for (uint32_t i = 1; i < len; i++)
    {
        hexB = QStringLiteral("%1 ").arg(buf[i], 2, 16, QLatin1Char('0'));
        hexStr.append(hexB);
        if (i % 16 == 0)
        {
            hexStr.append("\r\n").append(QStringLiteral("0x%1: ").arg(i, 4, 16, QLatin1Char('0')));
        }
    }
    ui->tbAscii->setText(str);
    ui->tbHex->setText(hexStr);
}

char HexViewer::replaceBrokenChar(unsigned char in)
{
    if (in < 0x20 || in > 0x7E)
    {
        return '.';
    }
    return in;
}
