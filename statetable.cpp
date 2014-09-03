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
    setRow(3);

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

    /*if(!parent.isValid())
        return 0;

    TableItem *parentItem = static_cast<TableItem*>(parent.internalPointer());

    return parentItem->childCount();*/
}

int StateTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return tableColumn;
    /*if(!parent.isValid())
        return 0;

    TableItem *parentItem = static_cast<TableItem*>(parent.internalPointer());
    TableItem *item = parentItem->parent();

    if(item != rootItem)
        return 0;
    else
        return rootItem->childCount();*/
}

QModelIndex StateTable::index(int row, int column, const QModelIndex &parent) const
{
    /*如果索引不存在，返回一个空的索引*/
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TableItem *parentItem;

    /*如果父项目的模型索引是无效的
     * parentItem为根项目
     * 否则为parent索引所指向的父项目*/
    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TableItem*>(parent.internalPointer());

    /*创建一个子项目*/
    TableItem *childItem = parentItem->child(row);

    /*如果子项目存在，创建模型索引 否则返回空的索引*/

    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex StateTable::parent(const QModelIndex &child) const
{
    /*如果索引无效，返回空的索引*/
    if(!child.isValid())
        return QModelIndex();

    /*找到索引所指向的子项目，再通过子项目找到父项目*/
    TableItem *childItem = static_cast<TableItem*>(child.internalPointer());
    TableItem*parentItem = childItem->parent();

    /*如果父项目为根项目，返回空的索引*/
    if(parentItem == rootItem)
        return QModelIndex();

    /*创建一个新索引*/
    return createIndex(0, parentItem->row(), parentItem);

}

void StateTable::setColumn(int column)
{
    tableColumn = column;
}

void StateTable::setRow(int row)
{
    tableRow = row;
}
