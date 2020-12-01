#include "grammarwindow.h"
#include "ui_grammarwindow.h"
#include <QDataWidgetMapper>
#include "FileEntryTableModel.h"

static FileEntryTableModel FileEntriesModel;
static QDataWidgetMapper *Mapper;

GrammarWindow::GrammarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GrammarWindow)
{
    ui->setupUi(this);
    ui->tvEntries->setModel(&FileEntriesModel);
    // needed to reset stacked widget in case it is left on other pages
    // in edit mode
    ui->stackedWidget->setCurrentIndex(0);
    Mapper = new QDataWidgetMapper(this);
    Mapper->setOrientation(Qt::Horizontal);
    Mapper->setModel(&FileEntriesModel);
    Mapper->addMapping(ui->tbSelectedFieldName, 0);
    Mapper->toFirst();
}

GrammarWindow::~GrammarWindow()
{
    delete ui;
}

void GrammarWindow::on_cbEntryType_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void GrammarWindow::on_btnNewField_clicked()
{
    QString fname = ui->tbNewFieldName->text();
    FileEntriesModel.addNewItem(fname);
}

void GrammarWindow::on_tvEntries_clicked(const QModelIndex &index)
{
    switch (index.row())
    {
    case 5:
    case 4:
    case 3:
        ui->cbEntryType->setCurrentIndex(0);
        break;
    case 2:
    case 1:
        ui->cbEntryType->setCurrentIndex(1);
        break;
    case 0:
    default:
        ui->cbEntryType->setCurrentIndex(0);
        break;
    }
}
