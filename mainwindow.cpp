#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = new StateTable;
    table->setTableSize(2, 5);

    QStringList headString;
    headString << "当前状态" << "信号" << "条件" << "下个状态" << "动作" ;

    table->setHeaderData(headString);

    ui->tableView_2->setModel(table);

    ui->treeWidget->setHeaderLabel(QString("State Tree"));

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

    cState = " ";
    cEvent = " ";

    setting = new SettingDialog;
    setting->setWindowTitle("State Machine and Event Setting");
    this->setWindowTitle("状态表编辑器");

    connect(setting, SIGNAL(closedSignal()), this, SLOT(on_setting_closed()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete setting;
}

void MainWindow::on_addButton_clicked()
{
    int i, row;
    QString str, event, guard;

    for(i = 0; i < 5; i++)
    {
        QComboBox *newComboBox = (QComboBox*)ui->tableWidget->cellWidget(0, i);
        str = newComboBox->currentText();

        if( !str.isEmpty() )
        {
            QTableWidgetItem *newItem  = new QTableWidgetItem(str);
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
        cStateItem = new QTreeWidgetItem(stateItem);
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
        eComboBox->addItem(text, eComboBox->count());
}

void MainWindow::on_actButton_clicked()
{
     bool ok;
     QComboBox *aComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 4);

     QString text = QInputDialog::getText(this, tr("Please Input action"),
                                         tr("Action:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
        aComboBox->addItem(text, aComboBox->count());
}

void MainWindow::on_grdButton_clicked()
{
     bool ok;
     QComboBox *gComboBox =  (QComboBox*)ui->tableWidget->cellWidget(0, 2);

     QString text = QInputDialog::getText(this, tr("Please Input gruad"),
                                         tr("Gruad:"), QLineEdit::Normal,
                                         "", &ok);
     if (ok && !text.isEmpty())
        gComboBox->addItem(text, gComboBox->count());
}

void MainWindow::on_expButton_clicked()
{
    int i;
    QString str ,event, guard, nstate, action, cPath, hPath;
    QUrl files = QFileDialog::getExistingDirectoryUrl(
                            this,
                            "Select one or more files to open",
                            QDir().currentPath());

    cPath = files.path().append("/");
    cPath.append(setting->getSateName().append(".c"));

    hPath = files.path().append("/");
    hPath.append(setting->getSateName().append(".h"));

    QFile cfile(cPath);
    if (!cfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QFile hfile(hPath);
    if (!hfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    /*Buid C Source File*/
    QTextStream out(&cfile);
    out << "/*This File Create By StateTableEdit Alpha*/\n";

//    for(i = 0; i < ui->tableWidget_2->rowCount()-1; i++)
//    {
//        str= ui->tableWidget_2->item(i, 0)->text();
//        event= ui->tableWidget_2->item(i, 1)->text();
//        guard= ui->tableWidget_2->item(i, 2)->text();
//        nstate= ui->tableWidget_2->item(i, 3)->text();
//        action= ui->tableWidget_2->item(i, 4)->text();

//        out << "\n";

//    if(eState != str)
//    {
//        eState = str;
//        eEvent = event;

//        /*function head*/
//        out << "stateTypeDef " << eState << "(userStateTypeDef *me, userSignalTypeDef *evt)\n";
//        out << "{\n";
//        out << "    switch(evt)\n";
//        out << "    {\n";
//        out << "        case " << event << ":\n";

//        if(guard != "None")
//        {
//            eGuard = guard;
//            out<< "             if(" << guard << ")\n";
//            out<< "             {\n";

//            if(action != "None")
//                out<< "                    " << action << "\n";

//            if(eState == "enter" || eState == "exit" || eState == nstate)
//            {
//                out<< "                     return HANDLE;\n";
//                out<< "                     break;\n";
//            }
//            else
//            {
//                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//                out<< "                     return TRAN;\n";
//                out<< "                     break;\n";
//            }
//            out<< "             }\n";

//        }
//        else
//        {
//            if(action != "None")
//                out<< "                    " << action << "\n";

//            if(eState == "enter" || eState == "exit" || eState == nstate)
//            {
//                out<< "                     return HANDLE;\n";
//                out<< "                     break;";
//            }
//            else
//            {
//                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//                out<< "                     return TRAN;\n";
//                out<< "                     break;\n";
//            }

//        }
//    }
//    else if(eEvent != event)
//    {
//        eEvent = event;
//        out << "        case " << event << ":\n";

//        if(guard != "None")
//        {
//            eGuard = guard;
//            out<< "             if(" << guard << ")\n";
//            out<< "             {\n";

//            if(action != "None")
//                out<< "                    " << action << "\n";

//            if(eState == "enter" || eState == "exit" || eState == nstate)
//            {
//                out<< "                     return HANDLE;\n";
//                out<< "                     break;\n";
//            }
//            else
//            {
//                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//                out<< "                     return TRAN;\n";
//                out<< "                     break;\n";
//            }
//            out<< "             }\n";

//        }
//        else
//        {
//            if(action != "None")
//                out<< "                    " << action << "\n";

//            if(eState == "enter" || eState == "exit" || eState == nstate)
//            {
//                out<< "                     return HANDLE;\n";
//                out<< "                     break;\n";
//            }
//            else
//            {
//                out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//                out<< "                     return TRAN;\n";
//                out<< "                     break;\n";
//            }

//        }
//    }
//    else if( guard != "None")
//    {
//        out<< "             else if(" << guard << ")\n";
//        out<< "             {\n";

//        if(action != "None")
//            out<< "                    " << action << "\n";

//        if(eState == "enter" || eState == "exit" || eState == nstate)
//        {
//            out<< "                     return HANDLE;\n";
//            out<< "                     break;\n";
//        }
//        else
//        {
//            out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//            out<< "                     return TRAN;\n";
//            out<< "                     break;\n";
//        }
//        out<< "             }\n";
//    }
//    else if(guard == "None")
//    {
//        out<< "                    " << action << "\n";
//        if(eState == "enter" || eState == "exit" || eState == nstate)
//        {
//            out<< "                     return HANDLE;\n";
//            out<< "                     break;\n";
//        }
//        else
//        {
//            out<< "                     me->super.currentState = STATE(" << nstate <<");\n";
//            out<< "                     return TRAN;";
//            out<< "                     break;";
//        }

//    }

//    if(i == ui->tableWidget_2->rowCount()-2)
//    {
//        out << "    }\n";
//        out << "}\n";
//    }
//    else
//    {
//        if(eState != ui->tableWidget_2->item(i+1, 0)->text())
//        {
//            out << "    }\n";
//            out << "}\n";
//        }
//    }

//    }
}

void MainWindow::on_setButton_clicked()
{
   setting->show();
}

void MainWindow::on_setting_closed()
{
    stateItem = new QTreeWidgetItem(ui->treeWidget);
    eventItem= new QTreeWidgetItem(ui->treeWidget);
    stateItem->setText(0, setting->getSateName());
    eventItem->setText(0, setting->getEventName());

}
