#ifndef FILEENTRYTABLEMODEL_H
#define FILEENTRYTABLEMODEL_H

#include <QMap>
#include <QAbstractTableModel>
#include <FileEntry.h>

#define FILE_ENTRY_NAME_COLUMN          0
#define FILE_ENTRY_TYPE_COLUMN          1
#define FILE_ENTRY_VALUE_COLUMN         2
#define FILE_ENTRY_OFFSET_COLUMN        3
#define FILE_ENTRY_LENGTH_COLUMN        4
#define FILE_ENTRY_OFFSET_UNIT_COLUMN   5
#define FILE_ENTRY_LENGTH_UNIT_COLUMN   6
#define FILE_ENTRY_COLUMN_COUNT         7

class FileEntryTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileEntryTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addNewItem(QString &name);
    void addNewItem(QString &name, QString &type, uint32_t offset, uint32_t length, int offsUnit, int lenUnit);
    void removeItem(int row);
    void setSourceBuffer(char *buf);
    void updateAllEntryValues();
    void updateEntryValue(uint32_t idx);

private:
    QString getFileEntryValue(uint32_t idx) const;
    QString getFileEntryType(uint32_t idx) const;
    QString getFileEntryName(uint32_t idx) const;
    QString getFileEntryOffset(uint32_t idx) const;
    QString getFileEntryLength(uint32_t idx) const;
    QString getFileEntryOffsetUnit(uint32_t idx) const;
    QString getFileEntryLengthUnit(uint32_t idx) const;

    void updateEntryValue(FileEntry &fe);
    void countIndex();

    FileData FileDataList;
    QMap<EntryType, QString> TypeToStringMap;
    QMap<QString, EntryType> StringToTypeMap;
    char *SourceBuffer;
    uint32_t CurrentBitIdx = 0;
};

#endif // FILEENTRYTABLEMODEL_H
