#ifndef PARSERTREEITEM_H
#define PARSERTREEITEM_H
#include <QVariant>

class ParserTreeItem
{
public:
    ParserTreeItem(const QList<QVariant> &data, ParserTreeItem *parent);
    ~ParserTreeItem();

    void appendChild(ParserTreeItem *child);

    ParserTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data (int column) const;
    int row() const;
    ParserTreeItem *parent();

private:
    QList<ParserTreeItem*> childItems;
    QList<QVariant> itemData;
    ParserTreeItem *parentItem;
};
#endif // PARSERTREEITEM_H
