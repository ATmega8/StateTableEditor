#ifndef PARSER_H
#define PARSER_H

#include <QAbstractItemModel>

class Parser : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:

public slots:

};

#endif // PARSER_H
