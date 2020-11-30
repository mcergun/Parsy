#include "mainwindow.h"
#include "grammarwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GrammarWindow gw;
    w.show();
    gw.show();
    return a.exec();
}
