#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QDir>
#include <QTreeWidget>
#include <QTextStream>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QTableWidgetItem *newItem;

    QTreeWidgetItem *cStateItem;
    QTreeWidgetItem *cEventItem;
    QTreeWidgetItem *cGuardItem;

    QComboBox *newComboBox;

    QString cState;
    QString cEvent;
    QString cGuard;

    QString eState;
    QString eEvent;
    QString eGuard;

private slots:
    void on_addButton_clicked();
    void on_stateButton_clicked();
    //void on_sComboBoxactivated(QString);

    void on_sigButton_clicked();
    void on_actButton_clicked();
    void on_grdButton_clicked();
    void on_expButton_clicked();
};

/*class ItemBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ItemBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                     const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};*/

#endif // MAINWINDOW_H
