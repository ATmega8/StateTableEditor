#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject *parent);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setupModelData(const QStringList &lines, TreeItem *parent);
    void addItem(TreeItem *curItem, TreeItem *parent);
    void setRootItem(TreeItem *root);

signals:

public slots:

private:
    TreeItem *rootItem;

};

#endif // TREEMODEL_H