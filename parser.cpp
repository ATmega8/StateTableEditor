#include "parser.h"

/*
 * ParserTree类实现
 */

/*构造函数*/
ParserTree::ParserTree(QObject *parent) :
    QAbstractItemModel(parent)
{

}

/*析构函数*/
ParserTree::~ParserTree()
{

}

/*指定索引的数据*/
QVariant ParserTree::data(const QModelIndex &index, int role) const
{
    /*如果索引无效，返回空的数据*/
    if(!index.isValid())
        return QVariant();

    /*如果角色不是显示角色，返回空的数据*/
    if(role != Qt::DisplayRole)
        return QVariant();

    /*internalPointer返回一个指向索引指向的数据结构的void类型指针，
     * 然后再转换成ParserTreeItem * 类型的指针赋给 item*/
    ParserTreeItem *item = static_cast<ParserTreeItem*>(index.internalPointer());

    /*取出 item 中的数据*/
    return item->data(index.column());
}

/*指定索引的标志*/
Qt::ItemFlags ParserTree::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    /*Qt::ItemIsEnabled是指项目是可交互的
     *Qt::ItemIsSelectable是指项目是可以被选中的
     */
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*数据头, Qt::Qrientation 是用来确定表头是横向排列的还是纵向排列的*/
QVariant ParserTree::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

/*生成索引*/
QModelIndex ParserTree::index(int row, int column, const QModelIndex &parent) const
{
    /*如果索引不存在，返回一个空的索引*/
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    ParserTreeItem *parentItem;

    /*如果父项目的模型索引是无效的
     * parentItem为根项目
     * 否则为parent索引所指向的父项目*/
    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ParserTreeItem*>(parent.internalPointer());

    /*创建一个子项目*/
    ParserTreeItem *childItem = parentItem->child(row);

    /*如果子项目存在，创建模型索引 否则返回空的索引*/

    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

/*指定索引的父项目*/
QModelIndex ParserTree::parent(const QModelIndex &index) const
{
    /*如果索引无效，返回空的索引*/
    if(!index.isValid())
        return QModelIndex();

    /*找到索引所指向的子项目，再通过子项目找到父项目*/
    ParserTreeItem *childItem = static_cast<ParserTreeItem*>(index.internalPointer());
    ParserTreeItem *parentItem = childItem->parent();

    /*如果父项目为根项目，返回空的索引*/
    if(parentItem == rootItem)
        return QModelIndex();

    /*创建一个新索引*/
    return createIndex(parentItem->row(), 0, parentItem);
}

/*行计数器*/
int ParserTree::rowCount(const QModelIndex &parent) const
{
    ParserTreeItem *parentItem;

    if(parent.column() > 0)
        return 0;

    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ParserTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

/*列计数器*/
int ParserTree::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return static_cast<ParserTreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

