#include "settingdialog.h"
#include "ui_settingdialog.h"

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
