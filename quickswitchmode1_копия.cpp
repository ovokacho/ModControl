#include "quickswitchmode1.h"
#include "ui_quickswitchmode1.h"
#include <dialog.h>
#include <QSettings>
#include <QDebug>
#include "qdynamicelement.h"
#include <iostream>
#include "settingsdialog.h"
#include "mythread.h"
#include <type_traits>
#include <QMouseEvent>
#include <windows.h>
#include <QStatusBar>

quickSwitchMode1::quickSwitchMode1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quickSwitchMode1)
{
    ui->setupUi(this);
    SettingsOfFile = "settings.ini";
   SettingsFile = "settingsval.ini";
   message2 = 0;
   message1 = 0;
   fillToolListMode();
   QString currentTool = ui->comboBoxToolList->currentText();
   loadini(currentTool);
   port_serial = new QSerialPort(this);
   settings = new SettingsDialog;
   closeSerialPort();

   connect(ui->comboBoxToolList, SIGNAL(currentIndexChanged(QString)),this, SLOT(toolcomboselected()));
   connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(openSerialPort()));
   connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
  // connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendCommandLine(int)));
    connect(&thread_1, &QThread::started, &exampleObject_1, &ExampleObject::run);
    connect(&exampleObject_1, &ExampleObject::finished, &thread_1, &QThread::terminate);
    exampleObject_1.moveToThread(&thread_1);
    connect(&exampleObject_1, SIGNAL(send(int)), this, SLOT(update(int)));
    //connect(ui->PortButton, SIGNAL(triggered()), settings, SLOT(show()));
    //connect(this, SIGNAL(sendGlobalVar1(int)), &exampleObject_1, SLOT(receiveGlobalVar1(int)));
    ui->stopButton->setEnabled(false);
    //emit sendGlobalVar1(time);
   //ui-> StatusLayout ->addWidget(new QTextEdit);
    //QStatusBar* statusBar = new QStatusBar;
    //ui-> StatusLayout ->addWidget(statusBar );
}

quickSwitchMode1::~quickSwitchMode1()
{
    delete port_serial;
    delete settings;
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void quickSwitchMode1::toolcomboselected()
{
QString currentText = ui->comboBoxToolList->currentText();
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
message2 = 0;
message1 = 0;
ui->lcdNumber_11->display(0);
ui->lcdNumber_12->display(0);
ui->lcdNumber_21->display(0);
ui->lcdNumber_22->display(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void quickSwitchMode1::closeEvent( QCloseEvent *event )
{
    //! Ignore the event by default.. otherwise the window will be closed always.
    event->ignore();
    exampleObject_1.setrunning(false);

    if(thread_1.isRunning()){
         thread_1.quit();
         thread_1.terminate();
    }

    Sleep(2000);
    event->accept();
}

void quickSwitchMode1::openSerialPort()
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
            //ui->actionConfig->setEnabled(false);
            ui->sendButton->setEnabled(true);

          //  statusBar()->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
            //                           .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
           //                            .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            port_serial->close();
            QMessageBox::critical(this, tr("Ошибка"), port_serial->errorString());

          //  statusBar()->showMessage(tr("Невозможно открыть %s порт").arg(p.name));
        }
    } else {
        QMessageBox::critical(this, tr("ошибка"), port_serial->errorString());

       // statusBar()->showMessage(tr("Ошибка настройки порта"));
    }

}

void quickSwitchMode1::closeSerialPort()
{
    port_serial->close();
    started = false;
    //ui->monitor->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
    ui->disconnectButton->setEnabled(false);
    exampleObject_1.setrunning(false);
    ui->sendButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->textEdit->clear();
    //ui->actionConfig->setEnabled(true);
   // statusBar()->showMessage(tr("Порт отключен"));
}

void quickSwitchMode1::fillToolListMode()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(SettingsOfFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboBoxToolList->clear();
    ui->comboBoxToolList->addItems(groups);
    //ui->comboBoxToolList->addItem("Новое");
}

void quickSwitchMode1::on_pushButtonRefresh_clicked()
{
    fillToolListMode();
}

void quickSwitchMode1::slotCalculateAtt()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num1 = cbox->text().toDouble();
       double lcdtxt;
           if (cbox->isChecked()) {
                 lcdtxt = ui->lcdNumber_21->value();
                   ui->lcdNumber_21->display(lcdtxt + num1);
           }
           else {
               lcdtxt = ui->lcdNumber_21->value() - num1;
                double lcdtxt1 = (QString("%1").arg(lcdtxt, 0, 'f', 3)).toDouble();
                   ui->lcdNumber_21->display(lcdtxt1);
           }

       if (cbox->isChecked()) {

               message2 |= (1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
       else {

               message2 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
}

void quickSwitchMode1::slotCalculateAtt1()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num1 = cbox->text().toDouble();
       double lcdtxt;
           if (cbox->isChecked()) {
                 lcdtxt = ui->lcdNumber_11->value();
                   ui->lcdNumber_11->display(lcdtxt + num1);
           }
           else {
               lcdtxt = ui->lcdNumber_11->value() - num1;
                double lcdtxt1 = (QString("%1").arg(lcdtxt, 0, 'f', 3)).toDouble();
                   ui->lcdNumber_11->display(lcdtxt1);
           }

       if (cbox->isChecked()) {

               message1 |= (1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
       else {

               message1 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
}

void quickSwitchMode1::slotCalculateFv()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num2 = cbox->text().toDouble();
       double lcdtxt2;
           if (cbox->isChecked()) {
                   ui->lcdNumber_22->display(ui->lcdNumber_22->value() + num2);
                   //message |= (1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }
           else {
               lcdtxt2 = ui->lcdNumber_22->value() - num2;
                double lcdtxt3 = (QString("%1").arg(lcdtxt2, 0, 'f', 3)).toDouble();
                   ui->lcdNumber_22->display(lcdtxt3);
                   //message &= ~(1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }

       if (cbox->isChecked()) {

               message2 |= (1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
       else {

               message2 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
}

void quickSwitchMode1::slotCalculateFv1()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());
       double num2 = cbox->text().toDouble();
       double lcdtxt2;
           if (cbox->isChecked()) {
                   ui->lcdNumber_12->display(ui->lcdNumber_12->value() + num2);
                   //message |= (1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }
           else {
               lcdtxt2 = ui->lcdNumber_12->value() - num2;
                double lcdtxt3 = (QString("%1").arg(lcdtxt2, 0, 'f', 3)).toDouble();
                   ui->lcdNumber_12->display(lcdtxt3);
                   //message &= ~(1 << cbox->toolTip().toInt());
                   //qDebug() << message;
           }

       if (cbox->isChecked()) {

               message1 |= (1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
       else {

               message1 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
}

void quickSwitchMode1::slotCalculateElse()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());

       if (cbox->isChecked()) {

               message2 |= (1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
       else {

               message2 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message2;
       }
}

void quickSwitchMode1::slotCalculateElse1()
{
    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());

       if (cbox->isChecked()) {

               message1 |= (1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
       else {

               message1 &= ~(1 << cbox->toolTip().toInt());
               qDebug() << message1;
       }
}

//////////////////////////
/// 1 - это левая колонка, 2 или без номера - правая
////////////////////////

void quickSwitchMode1::addCheckBoxAtt(QString name, QString b)
{
    QDynamicElement *checkbox2 = new QDynamicElement(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    checkbox2->setText(name);
    checkbox2->setToolTip(b);
    /* Добавляем кнопку в слой с вертикальной компоновкой
     * */
    ui->verticalLayoutAtt_2->addWidget(checkbox2);
    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
     * */
   connect(checkbox2, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateAtt()));
   QDynamicElement *checkbox1 = new QDynamicElement(this);  // Создаем объект динамической кнопки
   /* Устанавливаем текст с номером этой кнопки
    * */
   checkbox1->setText(name);
   checkbox1->setToolTip(b);
   /* Добавляем кнопку в слой с вертикальной компоновкой
    * */
   ui->verticalLayoutAtt_1->addWidget(checkbox1);
   /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
    * */
  connect(checkbox1, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateAtt1()));
}

void quickSwitchMode1::addCheckBoxFv(QString name,QString b)
{
    QDynamicElement *checkbox2 = new QDynamicElement(this);
    checkbox2->setText(name);
    checkbox2->setToolTip(b);
    ui->verticalLayoutFv_2->addWidget(checkbox2);
    connect(checkbox2, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateFv()));

    QDynamicElement *checkbox1 = new QDynamicElement(this);
    checkbox1->setText(name);
    checkbox1->setToolTip(b);
    ui->verticalLayoutFv_1->addWidget(checkbox1);
    connect(checkbox1, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateFv1()));
}

void quickSwitchMode1::addCheckBoxElse(QString name,QString b)
{
    QDynamicElement *checkbox2 = new QDynamicElement(this);
    checkbox2->setText(name);
    checkbox2->setToolTip(b);
    ui->verticalLayoutOther_2->addWidget(checkbox2);
    connect(checkbox2, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateElse()));

    QDynamicElement *checkbox1 = new QDynamicElement(this);
    checkbox1->setText(name);
    checkbox1->setToolTip(b);
    ui->verticalLayoutOther_1->addWidget(checkbox1);
    connect(checkbox1, SIGNAL(stateChanged(int)), this, SLOT(slotCalculateElse1()));
}

void quickSwitchMode1::loadini(QString tool)
{

    QSettings settings(SettingsOfFile, QSettings::IniFormat);
    settings.beginGroup(tool);
    QString dialogValues[3][16];
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
        QSettings settingstype(SettingsFile, QSettings::IniFormat);
         //  settings.setIniCodec( codec );
        //settingstype.setIniCodec( "UTF-8" );

        for(int id=0;id<16;id++){

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

void quickSwitchMode1::sendCommandLine(int msg)
{
    if(msg==1) {
     QString s = QString::number(message1);
     QByteArray ba = s.toLatin1();
     const char *c_str1 = ba.data();
    port_serial->write(c_str1);
    }
    if(msg==2) {
     QString s = QString::number(message2);
     QByteArray ba = s.toLatin1();
     const char *c_str2 = ba.data();
    port_serial->write(c_str2);
    }
}

void quickSwitchMode1::on_sendButton_clicked()
{
//    QThread *thread= new QThread;
//    MyClass *my = new MyClass("B");
//    stopW = true;
//    my->moveToThread(thread);

//    connect(my, SIGNAL(send(int)), this, SLOT(update(int)));
//    connect(thread, SIGNAL(started()), my, SLOT(doWork()));
//    connect(thread, SIGNAL(finished()), my, SLOT(stopWork()));

//    connect(ui->stopButton, SIGNAL(clicked()), my, SLOT(stopWork()));
//    connect(this, SIGNAL(sendGlobalVar1(unsigned long int)), my, SLOT(receiveGlobalVar1(unsigned long int)), Qt::DirectConnection);
//    connect(this, SIGNAL(sendGlobalVar2(unsigned long int)), my, SLOT(receiveGlobalVar2(unsigned long int)), Qt::DirectConnection);
//    connect(this, SIGNAL(sendGlobalVar3(bool)), my, SLOT(receiveGlobalVar3(bool)), Qt::DirectConnection);

//    emit sendGlobalVar2(message2);
//    emit sendGlobalVar3(stopW);
//    thread->start();
//   // my->stopWork();
//    ui->sendButton->setEnabled(false);
    int time;
    unsigned long timetest;
    time = ui->spinBox->value();
    timetest = static_cast<unsigned long>(time);
    qDebug()<< "test: " << timetest;
    exampleObject_1.setMsg(timetest);
    exampleObject_1.setrunning(true);
    thread_1.start();
//    int time;
//    time = ui->spinBox->value();
//    emit sendGlobalVar1(time);
    ui->sendButton->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void quickSwitchMode1::update (int i)
{
    if(i%2==0){
        QString s = QString::number(message1);
        QByteArray ba = s.toLatin1();
        const char *c_str1 = ba.data();
       port_serial->write(c_str1);
       ui->textEdit->insertPlainText(QString::number(message1));
       ui->textEdit->insertPlainText(";");
    }
    else
    {
        QString s = QString::number(message2);
        QByteArray ba = s.toLatin1();
        const char *c_str2 = ba.data();
       port_serial->write(c_str2);
        ui->textEdit->insertPlainText(QString::number(message2));
        ui->textEdit->insertPlainText(";");
    }

}

void quickSwitchMode1::on_stopButton_clicked()
{
       exampleObject_1.setrunning(false);
       ui->sendButton->setEnabled(true);
       ui->spinBox->setEnabled(true);
       ui->stopButton->setEnabled(false);
       //ui->textEdit->clear();
}

void quickSwitchMode1::on_PortButton_clicked()
{
    settings->exec();
}
