#ifndef PARSER_H
#define PARSER_H

#include <QAbstractItemModel>
#include <QVariant>

#include "parsertreeitem.h"


class ParserTree : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ParserTree(QObject *parent = 0);
    ~ParserTree();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;


signals:

public slots:

private:
    void buildParserTree();

    ParserTreeItem *rootItem;

};

class Parser
{

public:

private:

};


#endif // PARSER_H
