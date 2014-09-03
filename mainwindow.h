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

#include "settingdialog.h"
#include "statetable.h"

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

    QTreeWidgetItem *eventItem;
    QTreeWidgetItem *stateItem;

    QComboBox *newComboBox;

    QString cState;
    QString cEvent;
    QString cGuard;

    QString eState;
    QString eEvent;
    QString eGuard;

    SettingDialog *setting;

    StateTable *table;

private slots:
    void on_addButton_clicked();
    void on_stateButton_clicked();
    void on_sigButton_clicked();
    void on_actButton_clicked();
    void on_grdButton_clicked();
    void on_expButton_clicked();
    void on_setButton_clicked();

public slots:
    void on_setting_closed();

};



#endif // MAINWINDOW_H
