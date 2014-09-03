#ifndef STATETABLE_H
#define STATETABLE_H

#include <QAbstractTableModel>

class StateTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StateTable(QObject *parent = 0);

signals:

public slots:

};

#endif // STATETABLE_H
