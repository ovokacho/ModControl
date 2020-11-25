#include "mainw.h"
#include "ui_mainw.h"
#include <iostream>
#include <QWidget>
#include <dialog.h>
#include <values_window.h>
#include <QSettings>
//#include <QSignalMapper>
#include "settingsdialog.h"
#include "qdynamicelement.h"

#include <QInputDialog>
#include "quickswitchmode1.h"

MainW::MainW(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainW)
{
    ui->setupUi(this);
    SettingsOfFile = "settings.ini"; // имя/полное расположение файла настроек
    SettingsFile = "settingsval.ini";
    SettingsPss = "settingspss.ini";
    message = 0;
    fillToolListMain();
    QString currentTool = ui->comboBoxToolList_2->currentText();
    loadini(currentTool);

    port_serial = new QSerialPort(this);
    settings = new SettingsDialog;
    closeSerialPort();
    connect(ui->comboBoxToolList_2, SIGNAL(currentIndexChanged(QString)),this, SLOT(toolcomboselected()));
    //mapper = new QSignalMapper(this);
    //////////////////
    //connect(port_serial, SIGNAL(error(QSerialPort::SerialPortError)),
   //         this, SLOT(handleError(QSerialPort::SerialPortError)));
    //connect(port_serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(openSerialPort()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendCommandLine()));
    connect(ui->actionConfig, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionTools, SIGNAL(triggered()), this, SLOT(openTools()));
    connect(ui->actionMode, SIGNAL(triggered()), this, SLOT(openMode()));
    connect(ui->actionSets, SIGNAL(triggered()), this, SLOT(openSets()));
}
MainW::~MainW()
{
    delete port_serial;
    delete settings;
    delete ui;
}

void MainW::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    port_serial->setPortName(p.name);
    if (port_serial->open(QIODevice::ReadWrite)) {
        if (port_serial->setBaudRate(p.baudRate)
                && port_serial->setDataBits(p.dataBits)
                && port_serial->setParity(p.parity)
                && port_serial->setStopBits(p.stopBits)
                && port_serial->setFlowControl(p.flowControl)) {

            started = false;
            ui->connectButton->setEnabled(false);
            ui->disconnectButton->setEnabled(true);
            ui->actionConfig->setEnabled(false);
            ui->sendButton->setEnabled(true);

            statusBar()->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            port_serial->close();
            QMessageBox::critical(this, tr("Ошибка"), port_serial->errorString());

            statusBar()->showMessage(tr("Невозможно открыть %s порт").arg(p.name));
        }
    } else {
        QMessageBox::critical(this, tr("ошибка"), port_serial->errorString());

        statusBar()->showMessage(tr("Ошибка настройки порта"));
    }

}

void MainW::closeSerialPort()
{
    port_serial->close();
    started = false;
    //ui->monitor->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
    ui->disconnectButton->setEnabled(false);
    ui->actionConfig->setEnabled(true);
    statusBar()->showMessage(tr("Порт отключен"));
}

void MainW::sendCommandLine()
{
     QString s = QString::number(message);
     QByteArray ba = s.toLatin1();
     const char *c_str2 = ba.data();
    port_serial->write(c_str2);
}

void MainW::addCheckBoxAtt(QString name, QString b)
{
    QDynamicElement *checkbox = new QDynamicElement(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    checkbox->setText(name);
    checkbox->setToolTip(b);
    /* Добавляем кнопку в слой с вертикальной компоновкой
     * */
    ui->verticalLayoutAtt_2->addWidget(checkbox);
    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
     * */
   connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateAtt()));
}

void MainW::addCheckBoxFv(QString name,QString b){
    QDynamicElement *checkbox = new QDynamicElement(this);
    checkbox->setText(name);
    checkbox->setToolTip(b);
    ui->verticalLayoutFv_2->addWidget(checkbox);
    connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateFv()));
}

void MainW::addCheckBoxElse(QString name,QString b){
    QDynamicElement *checkbox = new QDynamicElement(this);
    checkbox->setText(name);
    checkbox->setToolTip(b);
    ui->verticalLayoutOther_2->addWidget(checkbox);
    connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateElse()));
}

void MainW::slotCalculateAtt()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num1 = cbox->text().toDouble();
       double lcdtxt;
           if (cbox->isChecked()) {
                 lcdtxt = ui->lcdNumber->value();
                   ui->lcdNumber->display(lcdtxt + num1);
           }
           else {
               lcdtxt = ui->lcdNumber->value() - num1;
                double lcdtxt1 = (QString("%1").arg(lcdtxt, 0, 'f', 3)).toDouble();
                   ui->lcdNumber->display(lcdtxt1);
           }

       if (cbox->isChecked()) {

               message |= (1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
       else {

               message &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
}

void MainW::slotCalculateFv()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num2 = cbox->text().toDouble();
       double lcdtxt2;
           if (cbox->isChecked()) {
                   ui->lcdNumber_2->display(ui->lcdNumber_2->value() + num2);
                   //message |= (1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }
           else {
               lcdtxt2 = ui->lcdNumber_2->value() - num2;
                double lcdtxt3 = (QString("%1").arg(lcdtxt2, 0, 'f', 3)).toDouble();
                   ui->lcdNumber_2->display(lcdtxt3);
                   //message &= ~(1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }

       if (cbox->isChecked()) {

               message |= (1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
       else {

               message &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
}

void MainW::slotCalculateElse()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());

       if (cbox->isChecked()) {

               message |= (1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
       else {

               message &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message;
       }
}

void MainW::toolcomboselected()
{
QString currentText = ui->comboBoxToolList_2->currentText();
while ( QLayoutItem* item = ui->verticalLayoutFv_2->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
while ( QLayoutItem* item = ui->verticalLayoutAtt_2->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
while ( QLayoutItem* item = ui->verticalLayoutOther_2->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
loadini(currentText);
 message = 0;
ui->lcdNumber->display(0);
ui->lcdNumber_2->display(0);
}

void MainW::openTools()
{
    Dialog dialog;
    if (dialog.exec())
    {

        dialog.open();
    }
//      QString *x = dialog.value();

}
/////////////
void MainW::openMode()
{
    quickSwitchMode1 quickswitchmode1;
    if (quickswitchmode1.exec())
    {

        quickswitchmode1.open();
    }
//      QString *x = dialog.value();

}
//////////////
void MainW::openSets()
{
    QSettings settingspss(SettingsPss, QSettings::IniFormat);
    //settingspss.setValue("KEY", "4815162342");
        QString password = settingspss.value("KEY","").toString();


    bool bOk;
    QString pss = QInputDialog::getText( this,
                                         "Закрыто",
                                         "Пароль:",
                                         QLineEdit::Password,
                                         "",
                                         &bOk
                                        );
    if (bOk && pss == password) {
        values_window values_window;
        if (values_window.exec())
        {
            values_window.open();
        }
    }


}

void MainW::fillToolListMain()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(SettingsOfFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboBoxToolList_2->clear();
    ui->comboBoxToolList_2->addItems(groups);
    //ui->comboBoxToolList->addItem("Новое");
}

void MainW::on_pushButtonRefresh_2_clicked()
{
    fillToolListMain();
}

void MainW::loadini(QString tool)
{

    QSettings settings(SettingsOfFile, QSettings::IniFormat);
    settings.beginGroup(tool);
    QString dialogValues[3][19];
        dialogValues[0][0] = settings.value("combobox","").toString();
        dialogValues[0][1] = settings.value("combobox_2","").toString();
        dialogValues[0][2] = settings.value("combobox_3","").toString();
        dialogValues[0][3] = settings.value("combobox_4","").toString();
        dialogValues[0][4] = settings.value("combobox_5","").toString();
        dialogValues[0][5] = settings.value("combobox_6","").toString();
        dialogValues[0][6] = settings.value("combobox_7","").toString();
        dialogValues[0][7] = settings.value("combobox_8","").toString();
        dialogValues[0][8] = settings.value("combobox_9","").toString();
        dialogValues[0][9] = settings.value("combobox_10","").toString();
        dialogValues[0][10] = settings.value("combobox_11","").toString();
        dialogValues[0][11] = settings.value("combobox_12","").toString();
        dialogValues[0][12] = settings.value("combobox_13","").toString();
        dialogValues[0][13] = settings.value("combobox_14","").toString();
        dialogValues[0][14] = settings.value("combobox_15","").toString();
        dialogValues[0][15] = settings.value("combobox_16","").toString();

        dialogValues[0][16] = settings.value("combobox_34","").toString();
        dialogValues[0][17] = settings.value("combobox_35","").toString();
        dialogValues[0][18] = settings.value("combobox_36","").toString();

        dialogValues[1][0] = settings.value("combobox_18","").toString();
        dialogValues[1][1] = settings.value("combobox_19","").toString();
        dialogValues[1][2] = settings.value("combobox_20","").toString();
        dialogValues[1][3] = settings.value("combobox_21","").toString();
        dialogValues[1][4] = settings.value("combobox_22","").toString();
        dialogValues[1][5] = settings.value("combobox_23","").toString();
        dialogValues[1][6] = settings.value("combobox_24","").toString();
        dialogValues[1][7] = settings.value("combobox_25","").toString();
        dialogValues[1][8] = settings.value("combobox_26","").toString();
        dialogValues[1][9] = settings.value("combobox_27","").toString();
        dialogValues[1][10] = settings.value("combobox_28","").toString();
        dialogValues[1][11] = settings.value("combobox_29","").toString();
        dialogValues[1][12] = settings.value("combobox_30","").toString();
        dialogValues[1][13] = settings.value("combobox_31","").toString();
        dialogValues[1][14] = settings.value("combobox_32","").toString();
        dialogValues[1][15] = settings.value("combobox_33","").toString();

        dialogValues[1][16] = settings.value("combobox_37","").toString();
        dialogValues[1][17] = settings.value("combobox_38","").toString();
        dialogValues[1][18] = settings.value("combobox_39","").toString();

        dialogValues[2][0] = settings.value("spinBox","").toString();
        dialogValues[2][1] = settings.value("spinBox_2","").toString();
        dialogValues[2][2] = settings.value("spinBox_3","").toString();
        dialogValues[2][3] = settings.value("spinBox_4","").toString();
        dialogValues[2][4] = settings.value("spinBox_5","").toString();
        dialogValues[2][5] = settings.value("spinBox_6","").toString();
        dialogValues[2][6] = settings.value("spinBox_7","").toString();
        dialogValues[2][7] = settings.value("spinBox_8","").toString();
        dialogValues[2][8] = settings.value("spinBox_9","").toString();
        dialogValues[2][9] = settings.value("spinBox_10","").toString();
        dialogValues[2][10] = settings.value("spinBox_11","").toString();
        dialogValues[2][11] = settings.value("spinBox_12","").toString();
        dialogValues[2][12] = settings.value("spinBox_13","").toString();
        dialogValues[2][13] = settings.value("spinBox_14","").toString();
        dialogValues[2][14] = settings.value("spinBox_15","").toString();
        dialogValues[2][15] = settings.value("spinBox_16","").toString();

        dialogValues[2][16] = settings.value("spinBox_17","").toString();
        dialogValues[2][17] = settings.value("spinBox_18","").toString();
        dialogValues[2][18] = settings.value("spinBox_19","").toString();

        QSettings settingstype(SettingsFile, QSettings::IniFormat);
         //  settings.setIniCodec( codec );
        //settingstype.setIniCodec( "UTF-8" );

        for(int id=0;id<19;id++){

            if(dialogValues[0][id]!="") {
                settingstype.beginReadArray(dialogValues[0][id]);
                settingstype.setArrayIndex(10);
            if(settingstype.value("type").toInt()==0) {
                addCheckBoxAtt(dialogValues[1][id],dialogValues[2][id]);
            }
            if(settingstype.value("type").toInt()==1){
                addCheckBoxFv(dialogValues[1][id],dialogValues[2][id]);
            }
            if(settingstype.value("type").toInt()==2){
                addCheckBoxElse(dialogValues[1][id],dialogValues[2][id]);
            }
            settingstype.endArray();
            }
        }
}
//QSettings settings(SettingsFile, QSettings::IniFormat);
// //  settings.setIniCodec( codec );
//settings.setIniCodec( "UTF-8" );
//settings.beginReadArray(set);
//// settings.beginGroup(set);
//for(int idx=0;idx<10;idx++) {
//    settings.setArrayIndex(idx);
//    column1combos[idx]->setText(settings.value("value").toString());
//}
//settings.setArrayIndex(10);
//ui->comboType->setCurrentIndex(settings.value("type").toInt());
//settings.endArray();
