#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList HeaderLabels;
    HeaderLabels << "Current State" << "Event" << "Guard Conditions" << "Next State" << "Action";

    ui->treeWidget->setHeaderLabel(QString("State Tree"));
    ui->tableWidget_2->setHorizontalHeaderLabels(HeaderLabels);

    ui->tableWidget->setCellWidget(0,0, new QComboBox);
    ui->tableWidget->setCellWidget(0,1, new QComboBox);
    ui->tableWidget->setCellWidget(0,2, new QComboBox);
    ui->tableWidget->setCellWidget(0,3, new QComboBox);
    ui->tableWidget->setCellWidget(0,4, new QComboBox);

    QComboBox *eComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 1);
    eComboBox->addItem(tr("enter"), eComboBox->count());
    eComboBox->addItem(tr("exit"), eComboBox->count());

    QComboBox *gComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 2);
    gComboBox->addItem(tr("None"), gComboBox->count());

    QComboBox *aComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 4);
    aComboBox->addItem(tr("None"), aComboBox->count());

    QTreeWidgetItem *enterTreeItem = new QTreeWidgetItem(ui->eTree);
    enterTreeItem->setText(0, tr("enter"));

    QTreeWidgetItem *exitTreeItem = new QTreeWidgetItem(ui->eTree);
    exitTreeItem->setText(0, tr("exit"));

    cState = " ";
    cEvent = " ";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    int i, row;
    QString str, event, guard;
    row = ui->tableWidget_2->rowCount();

    for(i = 0; i < 5; i++)
    {
        QComboBox *newComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, i);
        str = newComboBox->currentText();

        if( !str.isEmpty() )
        {
            QTableWidgetItem *newItem  = new QTableWidgetItem(str);
            ui->tableWidget_2->setItem(row -1, i, newItem);
        }
    }

    QComboBox *newComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 0);
    str = newComboBox->currentText();

    newComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 1);
    event = newComboBox->currentText();

    newComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, 2);
    guard = newComboBox->currentText();

    if(cState != str)
    {
        cState = str;
        cEvent = event;
        cStateItem = new QTreeWidgetItem(ui->treeWidget);
        cEventItem = new QTreeWidgetItem(cStateItem);
        cStateItem->setText(0, str);
        cEventItem->setText(0, event);

        if(guard != "None")
        {
            cGuardItem = new QTreeWidgetItem(cEventItem);
            cGuardItem->setText(0, guard);
            cGuard = guard;
        }
    }
    else if(cEvent != event)
    {
        cEvent = event;
        cEventItem = new QTreeWidgetItem(cStateItem);
        cEventItem->setText(0, event);

        if(guard != "None")
        {
            cGuardItem = new QTreeWidgetItem(cEventItem);
            cGuardItem->setText(0, guard);
            cGuard = guard;
        }
    }
    else if(cGuard != guard && guard != "None")
    {
        cGuardItem = new QTreeWidgetItem(cEventItem);
        cGuardItem->setText(0, guard);
    }

    ui->tableWidget_2->setRowCount(row + 1);
}

void MainWindow::on_stateButton_clicked()
{
    bool ok;

    QComboBox *sComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 0);
    QComboBox *nComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 3);

    QString text = QInputDialog::getText(this, tr("Please Input State"),
                                         tr("State:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
     {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem(ui->sTree);
        newTreeItem->setText(0, text);

        sComboBox->addItem(text, sComboBox->count());
        nComboBox->addItem(text, nComboBox->count());
     }
}

void MainWindow::on_sigButton_clicked()
{
     bool ok;
     QComboBox *eComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 1);

     QString text = QInputDialog::getText(this, tr("Please Input event"),
                                         tr("Event:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
     {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem(ui->eTree);
        newTreeItem->setText(0, text);

        eComboBox->addItem(text, eComboBox->count());
     }
}

void MainWindow::on_actButton_clicked()
{
     bool ok;
     QComboBox *aComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 4);

     QString text = QInputDialog::getText(this, tr("Please Input action"),
                                         tr("Action:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
     {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem(ui->aTree);
        newTreeItem->setText(0, text);

        aComboBox->addItem(text, aComboBox->count());
     }
}

void MainWindow::on_grdButton_clicked()
{
     bool ok;
     QComboBox *gComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 2);

     QString text = QInputDialog::getText(this, tr("Please Input gruad"),
                                         tr("Gruad:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
     {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem(ui->gTree);
        newTreeItem->setText(0, text);

        gComboBox->addItem(text, gComboBox->count());
     }
}

void MainWindow::on_expButton_clicked()
{
    int i;
    QString str ,event, guard, nstate, action;
    /*QUrl files = QFileDialog::getSaveFileName(
                            this,
                            "Select one or more files to open",
                            QDir().currentPath(),
                            "C Source File (*.c)");*/

    QFile file("/home/life/Code/C/QtTest.c");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);
    out << "/*This File Create By StateTableEdit Alpha*/\n";

    for(i = 0; i < ui->tableWidget_2->rowCount()-1; i++)
    {
        str= ui->tableWidget_2->item(i, 0)->text();
        event= ui->tableWidget_2->item(i, 1)->text();
        guard= ui->tableWidget_2->item(i, 2)->text();
        nstate= ui->tableWidget_2->item(i, 3)->text();
        action= ui->tableWidget_2->item(i, 4)->text();

        out << "\n";

    if(eState != str)
    {
        eState = str;
        eEvent = event;

        /*function head*/
        out << "stateTypeDef " << eState << "(userStateTypeDef *me, userSignalTypeDef *evt)\n";
        out << "{\n";
        out << "    switch(evt)\n";
        out << "    {\n";
        out << "        case " << event << ":\n";

        if(guard != "None")
        {
            eGuard = guard;
            out<< "             if(" << guard << ")\n";
            out<< "             {\n";
            out<< "                    " << action << "\n";
            if(eState == "enter" || eState == "exit" || eState == nstate)
            {
                out<< "                     return HANDLE;\n";
                out<< "                     break;\n";
            }
            else
            {
                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
                out<< "                     return TRAN;\n";
                out<< "                     break;\n";
            }
            out<< "             }\n";

        }
        else
        {
            out<< "                    " << action << "\n";
            if(eState == "enter" || eState == "exit" || eState == nstate)
            {
                out<< "                     return HANDLE;\n";
                out<< "                     break;";
            }
            else
            {
                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
                out<< "                     return TRAN;\n";
                out<< "                     break;\n";
            }

        }
    }
    else if(eEvent != event)
    {
        eEvent = event;
        out << "        case " << event << ":\n";

        if(guard != "None")
        {
            eGuard = guard;
            out<< "             if(" << guard << ")\n";
            out<< "             {\n";
            out<< "                    " << action << "\n";
            if(eState == "enter" || eState == "exit" || eState == nstate)
            {
                out<< "                     return HANDLE;\n";
                out<< "                     break;\n";
            }
            else
            {
                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
                out<< "                     return TRAN;\n";
                out<< "                     break;\n";
            }
            out<< "             }\n";

        }
        else
        {
            out<< "                    " << action << "\n";
            if(eState == "enter" || eState == "exit" || eState == nstate)
            {
                out<< "                     return HANDLE;\n";
                out<< "                     break;\n";
            }
            else
            {
                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
                out<< "                     return TRAN;\n";
                out<< "                     break;\n";
            }

        }
    }
    else if(eGuard != guard && guard != "None")
    {
        out<< "             else if(" << guard << ")\n";
        out<< "             {\n";
        out<< "                    " << action << "\n";
        if(eState == "enter" || eState == "exit" || eState == nstate)
        {
            out<< "                     return HANDLE;\n";
            out<< "                     break;";
        }
        else
        {
            out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
            out<< "                     return TRAN;";
            out<< "                     break;";
        }
        out<< "             }\n";
    }
    else if(eGuard == "None")
    {
        out<< "                    " << action << "\n";
        if(eState == "enter" || eState == "exit" || eState == nstate)
        {
            out<< "                     return HANDLE;\n";
            out<< "                     break;";
        }
        else
        {
            out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
            out<< "                     return TRAN;";
            out<< "                     break;";
        }

    }

    if(i == ui->tableWidget_2->rowCount()-2)
    {
        out << "    }\n";
        out << "}\n";
    }
    else
    {
        if(eState != ui->tableWidget_2->item(i+1, 0)->text())
        {
            out << "    }\n";
            out << "}\n";
        }
    }

    }
}
