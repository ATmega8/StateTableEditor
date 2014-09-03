#include "statetable.h"

StateTable::StateTable(QObject *parent) :
    QAbstractTableModel(parent)
{
    rootItem = new TableItem("root");

    TableItem *parentItem1 = new TableItem("state", rootItem);
    TableItem *parentItem2 = new TableItem("event", rootItem);
    rootItem->append(parentItem1);
    rootItem->append(parentItem2);

    TableItem *childItem11 = new TableItem("state1", parentItem1);
    TableItem *childItem12 = new TableItem("state2", parentItem1);
    parentItem1->append(childItem11);
    parentItem1->append(childItem12);

    TableItem *childItem21 = new TableItem("event1", parentItem2);
    TableItem *childItem22 = new TableItem("event2", parentItem2);
    parentItem2->append(childItem21);
    parentItem2->append(childItem22);

    setColumn(2);
    setRow(2);

}

StateTable::~StateTable()
{

}

QVariant StateTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    TableItem *parentItem = rootItem->child(section);

    return parentItem->data();
}

QVariant StateTable::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    TableItem* item = static_cast<TableItem*>(index.internalPointer());

    return item->data();
}

int StateTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return tableRow;
}

int StateTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return tableColumn;
}

QModelIndex StateTable::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    TableItem *parentItem = rootItem->child(column);
    TableItem *childItem = parentItem->child(row);

    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

void StateTable::setColumn(int column)
{
    tableColumn = column;
}

void StateTable::setRow(int row)
{
    tableRow = row;
}

bool StateTable::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

bool StateTable::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{

}
