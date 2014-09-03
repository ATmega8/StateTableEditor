#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "mainwindow.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem("FSM");
    ui->comboBox->addItem("HSM");
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_saddButton_clicked()
{
   bool ok;
   QString value;

   value = QInputDialog::getText(this, tr("Please input value define"),
                                tr("value:"), QLineEdit::Normal,
                                "", &ok);

   QListWidgetItem *newItem = new QListWidgetItem();
   newItem->setText(value);

   ui->listWidget->addItem(newItem);
}

void SettingDialog::on_seditButton_clicked()
{
   bool ok;
   QString value;

   value = QInputDialog::getText(this, tr("Please input value define"),
                                tr("value:"), QLineEdit::Normal,
                                "", &ok);

   QListWidgetItem *newItem = ui->listWidget->currentItem();
   newItem->setText(value);
}

void SettingDialog::on_sdelButton_clicked()
{
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void SettingDialog::on_eaddButton_clicked()
{
   bool ok;
   QString value;

   value = QInputDialog::getText(this, tr("Please input value define"),
                                tr("value:"), QLineEdit::Normal,
                                "", &ok);

   QListWidgetItem *newItem = new QListWidgetItem();
   newItem->setText(value);

   ui->elistWidget->addItem(newItem);
}

void SettingDialog::on_eeditButton_clicked()
{
    bool ok;
   QString value;

   value = QInputDialog::getText(this, tr("Please input value define"),
                                tr("value:"), QLineEdit::Normal,
                                "", &ok);

   QListWidgetItem *newItem = ui->elistWidget->currentItem();
   newItem->setText(value);
}

void SettingDialog::on_edelButton_clicked()
{
     ui->elistWidget->takeItem(ui->elistWidget->currentRow());
}

QString SettingDialog::getSateName()
{
    return ui->lineEdit->text();
}

QString SettingDialog::getEventName()
{
    return ui->lineEdit_2->text();
}

QString SettingDialog::getStateType()
{
    return ui->comboBox->currentText();
}

QList<QString> SettingDialog::getStateValue()
{
    QList<QString> value;
    int i;

    for(i = 0; i < ui->listWidget->count(); i++)
       value[i] = ui->listWidget->item(i)->text();

   return value;
}

QList<QString> SettingDialog::getEventValue()
{
    QList<QString> value;
    int i;

    for(i = 0; i < ui->elistWidget->count(); i++)
       value[i] = ui->elistWidget->item(i)->text();

   return value;
}

void SettingDialog::closeEvent(QCloseEvent *event)
{
    emit closedSignal();
    event->accept();
}
