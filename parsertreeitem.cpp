#include "parsertreeitem.h"

/*
 * ParserTreeItem类实现
 *
 * parentItem
 *     |
 *     ThisItem---itemData  
 *          |----------childItem1
 *          |----------childItem2
 *                  ...
 *          |----------childItemn
 */

/*构造函数*/

ParserTreeItem::ParserTreeItem(const QList<QVariant> &data, ParserTreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}

/*析构函数*/
ParserTreeItem::~ParserTreeItem()
{
    qDeleteAll(childItems);
}

/*增加一个子项目，子项目会被增加到 childItems列表中*/
void ParserTreeItem::appendChild(ParserTreeItem *child)
{
    childItems.append(child);
}

/*查询指定行号的子项目*/
ParserTreeItem *ParserTreeItem::child(int row)
{
    return childItems.value(row);
}

/*子项目个数*/
int ParserTreeItem::childCount() const
{
    return childItems.count();
}

/*当前行数*/
int ParserTreeItem::row() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<ParserTreeItem*>(this));

    return 0;
}
/*列数*/
int ParserTreeItem::columnCount() const
{
    return itemData.count();
}

/*当前列的数据*/
QVariant ParserTreeItem::data(int column) const
{
    return itemData.value(column);
}

/*父项目*/
ParserTreeItem *ParserTreeItem::parent()
{
    return parentItem;
}
