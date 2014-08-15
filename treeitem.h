#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem
{
public:
    TreeItem(const QString &data, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data(int column) const;
    int row() const;
    TreeItem *parent();
    void setChild(TreeItem *child, TreeItem *parent);

private:
    QList<TreeItem*> childItems;
    QString itemData;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
