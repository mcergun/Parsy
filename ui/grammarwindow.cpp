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
    Mapper = new QDataWidgetMapper(this);
    FileEntriesModel = new FileEntryTableModel(this);
    Mapper->setOrientation(Qt::Horizontal);
    Mapper->setModel(FileEntriesModel);
    Mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    Mapper->addMapping(ui->tbEntryName, FILE_ENTRY_NAME_COLUMN);
    Mapper->addMapping(ui->cbEntryType, FILE_ENTRY_TYPE_COLUMN);
    Mapper->addMapping(ui->tbEntryOffset, FILE_ENTRY_OFFSET_COLUMN);
    Mapper->addMapping(ui->tbEntryLength, FILE_ENTRY_LENGTH_COLUMN);
    Mapper->addMapping(ui->cbEntryOffsetUnit, FILE_ENTRY_OFFSET_UNIT_COLUMN);
    Mapper->addMapping(ui->cbEntryLengthUnit, FILE_ENTRY_LENGTH_UNIT_COLUMN);
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
    static int oldOffset = 0;
    static int oldLength = 0;
    static int lastIdx = 0;
    if (index == 0)
    {
        // String type
        oldOffset = ui->cbEntryOffsetUnit->currentIndex();
        oldLength = ui->cbEntryLengthUnit->currentIndex();
        ui->cbEntryOffsetUnit->setCurrentIndex(1);
        ui->cbEntryLengthUnit->setCurrentIndex(1);
        ui->cbEntryOffsetUnit->setEnabled(false);
        ui->cbEntryLengthUnit->setEnabled(false);
        ui->lblDispType->setText("String Type:");
    }
    else
    {
        // Numeric types
        if (lastIdx == 0)
        {
            ui->cbEntryOffsetUnit->setCurrentIndex(oldOffset);
            ui->cbEntryLengthUnit->setCurrentIndex(oldLength);
            ui->lblDispType->setText("Display Style:");
        }
        ui->cbEntryOffsetUnit->setEnabled(true);
        ui->cbEntryLengthUnit->setEnabled(true);
    }
    lastIdx = index;
}

void GrammarWindow::on_btnNewField_clicked()
{
    QString fname = ui->tbEntryName->text();
    QString ftype = ui->cbEntryType->currentText();
    uint32_t offset = ui->tbEntryOffset->text().toUInt();
    uint32_t length = ui->tbEntryLength->text().toUInt();
    int offsetIdx = ui->cbEntryOffsetUnit->currentIndex();
    int lenIdx = ui->cbEntryLengthUnit->currentIndex();
    FileEntriesModel->addNewItem(fname, ftype, offset, length, offsetIdx, lenIdx);
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
