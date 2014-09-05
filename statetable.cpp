#include "statetable.h"

StateTable::StateTable(QObject *parent) :
    QAbstractTableModel(parent)
{
    rootItem = new TableItem("root");
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

QVariant StateTable::data(const QModelIndex &index, int role) const {
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

bool StateTable::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

bool StateTable::setHeaderData(QStringList string)
{
   int i;

   if(string.length() != tableColumn)
       return false;

   for(i = 0; i < tableColumn; i++)
   {
       TableItem *parentItem = rootItem->child(i);
       parentItem->setData(string.at(i));
   }
}

Qt::ItemFlags StateTable::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled;
}

void StateTable::setTableSize(int row, int column)
{
    int i, j;

    tableColumn = column;
    tableRow = row;

    for(i = 0; i < tableColumn; i++)
    {
        TableItem *parentItem = new TableItem("", rootItem);
        rootItem->append(parentItem);

        for(j = 0; j < tableRow; j++)
        {
            TableItem *childItem = new TableItem("", rootItem);
            parentItem->append(childItem);
        }
    }
}
