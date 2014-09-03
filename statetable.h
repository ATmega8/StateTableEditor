#ifndef STATETABLE_H
#define STATETABLE_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>

#include "tableitem.h"

/*
 *rootItem----+------------------------+
 *            |                        |
 *            +---parentItem1---+      +---parentItem2---+
 *                              |                        |
 *                              |---childItem1           +---childItem1
 *                              |                        |
 *                              +---childItem2           +---childItem2
 */

class StateTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StateTable(QObject *parent = 0);
    ~StateTable();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    void setRow(int row);
    void setColumn(int column);

signals:

public slots:

private:
    TableItem* rootItem;
    int tableRow;
    int tableColumn;

};

#endif // STATETABLE_H
