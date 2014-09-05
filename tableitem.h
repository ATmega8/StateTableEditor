#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QVariant>
#include <QList>
#include <QString>

/*
 * TODO: TableItem
 */

class TableItem
{
public:
    TableItem(QString data, TableItem *parent = 0);
    ~TableItem();

    int childCount() const;
    int row() const;

    QVariant data() const;

    TableItem *parent();
    TableItem *child(int row) const;

    void append(TableItem* child);
    void setData(QString string);

private:
    TableItem *parentItem;
    QList<TableItem*> childItems;
    QVariant itemData;
};

#endif // TABLEITEM_H
