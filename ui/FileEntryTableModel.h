#ifndef FILEENTRYTABLEMODEL_H
#define FILEENTRYTABLEMODEL_H

#include <FileEntry.h>
#include <QAbstractTableModel>

class FileEntryTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileEntryTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addNewItem(QString &name);
    void removeItem(int row);

private:
    QString getFileEntryValue(uint32_t idx) const;
    QString getFileEntryType(uint32_t idx) const;
    QString getFileEntryName(uint32_t idx) const;

    FileData FileDataList;
};

#endif // FILEENTRYTABLEMODEL_H
