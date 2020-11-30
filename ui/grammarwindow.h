#ifndef GRAMMARWINDOW_H
#define GRAMMARWINDOW_H

#include <QMainWindow>

namespace Ui {
class GrammarWindow;
}

class GrammarWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GrammarWindow(QWidget *parent = nullptr);
    ~GrammarWindow();

private slots:
    void on_cbEntryType_currentIndexChanged(int index);

    void on_btnNewField_clicked();

    void on_tvEntries_clicked(const QModelIndex &index);

private:
    Ui::GrammarWindow *ui;
};

#endif // GRAMMARWINDOW_H
