#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include <QInputDialog>
#include <QString>
#include <QList>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

QString getSateName();
QString getEventName();
QString getStateType();
QList<QString> getStateValue();
QList<QString> getEventValue();

private slots:
    void on_saddButton_clicked();
    void on_seditButton_clicked();
    void on_sdelButton_clicked();
    void on_eaddButton_clicked();
    void on_eeditButton_clicked();
    void on_edelButton_clicked();

private:
    Ui::SettingDialog *ui;


};

#endif // SETTINGDIALOG_H
