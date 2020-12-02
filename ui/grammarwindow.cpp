#include "grammarwindow.h"
#include "ui_grammarwindow.h"
#include <QDataWidgetMapper>
#include "FileEntryTableModel.h"

static FileEntryTableModel *FileEntriesModel = nullptr;
static QDataWidgetMapper *Mapper = nullptr;

GrammarWindow::GrammarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GrammarWindow)
{
    ui->setupUi(this);
    // needed to reset stacked widget in case it is left on other pages
    // in edit mode
    ui->stackedWidget->setCurrentIndex(0);
    Mapper = new QDataWidgetMapper(this);
    FileEntriesModel = new FileEntryTableModel(this);
    Mapper->setOrientation(Qt::Horizontal);
    Mapper->setModel(FileEntriesModel);
    Mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    Mapper->addMapping(ui->tbSelectedFieldName, FILE_ENTRY_NAME_COLUMN);
    Mapper->addMapping(ui->cbEntryType, FILE_ENTRY_TYPE_COLUMN);
    Mapper->addMapping(ui->tbNumericOffset, FILE_ENTRY_OFFSET_COLUMN);
    Mapper->addMapping(ui->tbStringOffset, FILE_ENTRY_OFFSET_COLUMN);
    Mapper->addMapping(ui->tbNumericLength, FILE_ENTRY_LENGTH_COLUMN);
    Mapper->addMapping(ui->tbStringLength, FILE_ENTRY_LENGTH_COLUMN);
    Mapper->addMapping(ui->cbNumericOffsetType, FILE_ENTRY_OFFSET_UNIT_COLUMN);
    Mapper->addMapping(ui->cbNumericLengthType, FILE_ENTRY_LENGTH_UNIT_COLUMN);
    Mapper->toFirst();
    ui->tvEntries->setModel(FileEntriesModel);
    // Hide unneeded columns
    ui->tvEntries->setColumnHidden(FILE_ENTRY_OFFSET_COLUMN, true);
    ui->tvEntries->setColumnHidden(FILE_ENTRY_LENGTH_COLUMN, true);
    ui->tvEntries->setColumnHidden(FILE_ENTRY_OFFSET_UNIT_COLUMN, true);
    ui->tvEntries->setColumnHidden(FILE_ENTRY_LENGTH_UNIT_COLUMN, true);
    ui->tvEntries->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvEntries->setSelectionBehavior(QAbstractItemView::SelectRows);
}

GrammarWindow::~GrammarWindow()
{
    delete ui;
}

void GrammarWindow::on_cbEntryType_currentIndexChanged(int index)
{
    int pgIdx = index == 0 ? 0 : 1;
    ui->stackedWidget->setCurrentIndex(pgIdx);
}

void GrammarWindow::on_btnNewField_clicked()
{
    QString fname = ui->tbNewFieldName->text();
    FileEntriesModel->addNewItem(fname);
    Mapper->toLast();
}

void GrammarWindow::on_tvEntries_clicked(const QModelIndex &index)
{
    emit Mapper->setCurrentIndex(index.row());
}

void GrammarWindow::on_btnUpdateField_clicked()
{
    Mapper->submit();
}
