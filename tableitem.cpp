#include "tableitem.h"

TableItem::TableItem(QString data, TableItem *parent)
{
    parentItem = parent;
    itemData = data;
}

TableItem::~TableItem()
{

}

TableItem* TableItem::child(int row) const
{
    return childItems.value(row);
}

TableItem* TableItem::parent()
{
    return parentItem;
}

int TableItem::childCount() const
{
    return childItems.count();
}

QVariant TableItem::data() const
{
    return itemData;
}

void TableItem::append(TableItem *child)
{
    childItems.append(child);
}

int TableItem::row() const
{
    return parentItem->childCount();
}
