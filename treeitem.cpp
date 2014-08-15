#include "treeitem.h"

TreeItem::TreeItem(const QString &data, TreeItem *parent)
{
        parentItem = parent;
        itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::row() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QString TreeItem::data(int column) const
{
    return itemData;
}

TreeItem* TreeItem::parent()
{
    return parentItem;
}

void TreeItem::setChild(TreeItem *child, TreeItem *parent)
{
    parent->childItems.append(child);
}
