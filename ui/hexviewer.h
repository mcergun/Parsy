#ifndef HEXVIEWER_H
#define HEXVIEWER_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class HexViewer;
}

class HexViewer : public QTextEdit
{
    Q_OBJECT

public:
    explicit HexViewer(QWidget *parent = nullptr);
    ~HexViewer();

    void setText(QString text);
    void setText(const char *buf, uint32_t len);

private:
    char replaceBrokenChar(unsigned char in);

    Ui::HexViewer *ui;
};

#endif // HEXVIEWER_H
