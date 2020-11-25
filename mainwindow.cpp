#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <dialog.h>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SettingsOfFile = "settings.ini"; // имя/полное расположение файла настроек

    fillToolListMain();
    QString currentTool = ui->comboBoxToolList->currentText();
    loadini(currentTool);
connect(ui->comboBoxToolList, SIGNAL(currentIndexChanged(QString)),this, SLOT(toolcomboselected()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toolcomboselected()
{
QString currentText = ui->comboBoxToolList->currentText();
loadini(currentText);
}

void MainWindow::on_pushButton_clicked()
{
//    Dialog dialog;
//      QString *x = dialog.value();

}

void MainWindow::fillToolListMain()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(SettingsOfFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboBoxToolList->clear();
    ui->comboBoxToolList->addItems(groups);
    //ui->comboBoxToolList->addItem("Новое");
}

void MainWindow::on_pushButtonRefresh_clicked()
{
    fillToolListMain();
}

void MainWindow::loadini(QString tool)
{

//    QSettings settings(SettingsOfFile, QSettings::IniFormat);
//    settings.beginGroup(tool);
//    QString dialogValues[3][16];
//        dialogValues[0][0] = settings.value("combobox","").toString();
//        dialogValues[0][1] = settings.value("combobox_2","").toString();
//        dialogValues[0][2] = settings.value("combobox_3","").toString();
//        dialogValues[0][3] = settings.value("combobox_4","").toString();
//        dialogValues[0][4] = settings.value("combobox_5","").toString();
//        dialogValues[0][5] = settings.value("combobox_6","").toString();
//        dialogValues[0][6] = settings.value("combobox_7","").toString();
//        dialogValues[0][7] = settings.value("combobox_8","").toString();
//        dialogValues[0][8] = settings.value("combobox_9","").toString();
//        dialogValues[0][9] = settings.value("combobox_10","").toString();
//        dialogValues[0][10] = settings.value("combobox_11","").toString();
//        dialogValues[0][11] = settings.value("combobox_12","").toString();
//        dialogValues[0][12] = settings.value("combobox_13","").toString();
//        dialogValues[0][13] = settings.value("combobox_14","").toString();
//        dialogValues[0][14] = settings.value("combobox_15","").toString();
//        dialogValues[0][15] = settings.value("combobox_16","").toString();

//        dialogValues[1][0] = settings.value("combobox_18","").toString();
//        dialogValues[1][1] = settings.value("combobox_19","").toString();
//        dialogValues[1][2] = settings.value("combobox_20","").toString();
//        dialogValues[1][3] = settings.value("combobox_21","").toString();
//        dialogValues[1][4] = settings.value("combobox_22","").toString();
//        dialogValues[1][5] = settings.value("combobox_23","").toString();
//        dialogValues[1][6] = settings.value("combobox_24","").toString();
//        dialogValues[1][7] = settings.value("combobox_25","").toString();
//        dialogValues[1][8] = settings.value("combobox_26","").toString();
//        dialogValues[1][9] = settings.value("combobox_27","").toString();
//        dialogValues[1][10] = settings.value("combobox_28","").toString();
//        dialogValues[1][11] = settings.value("combobox_29","").toString();
//        dialogValues[1][12] = settings.value("combobox_30","").toString();
//        dialogValues[1][13] = settings.value("combobox_31","").toString();
//        dialogValues[1][14] = settings.value("combobox_32","").toString();
//        dialogValues[1][15] = settings.value("combobox_33","").toString();

//        dialogValues[2][0] = settings.value("spinBox","").toString();
//        dialogValues[2][1] = settings.value("spinBox_2","").toString();
//        dialogValues[2][2] = settings.value("spinBox_3","").toString();
//        dialogValues[2][3] = settings.value("spinBox_4","").toString();
//        dialogValues[2][4] = settings.value("spinBox_5","").toString();
//        dialogValues[2][5] = settings.value("spinBox_6","").toString();
//        dialogValues[2][6] = settings.value("spinBox_7","").toString();
//        dialogValues[2][7] = settings.value("spinBox_8","").toString();
//        dialogValues[2][8] = settings.value("spinBox_9","").toString();
//        dialogValues[2][9] = settings.value("spinBox_10","").toString();
//        dialogValues[2][10] = settings.value("spinBox_11","").toString();
//        dialogValues[2][11] = settings.value("spinBox_12","").toString();
//        dialogValues[2][12] = settings.value("spinBox_13","").toString();
//        dialogValues[2][13] = settings.value("spinBox_14","").toString();
//        dialogValues[2][14] = settings.value("spinBox_15","").toString();
//        dialogValues[2][15] = settings.value("spinBox_16","").toString();

//        ui->checkBoxFv1->setChecked(false);
//        ui->checkBoxFv2->setChecked(false);
//        ui->checkBoxFv3->setChecked(false);
//        ui->checkBoxFv4->setChecked(false);
//        ui->checkBoxFv5->setChecked(false);
//        ui->checkBoxFv6->setChecked(false);
//        ui->checkBoxAtt1->setChecked(false);
//        ui->checkBoxAtt2->setChecked(false);
//        ui->checkBoxAtt3->setChecked(false);
//        ui->checkBoxAtt4->setChecked(false);
//        ui->checkBoxAtt5->setChecked(false);

//        for(int id=0;id<16;id++){
//            if(dialogValues[1][id]=="5.625*") ui->checkBoxFv1->setChecked(true);
//            if(dialogValues[1][id]=="11.25*") ui->checkBoxFv2->setChecked(true);
//            if(dialogValues[1][id]=="22.5*")  ui->checkBoxFv3->setChecked(true);
//            if(dialogValues[1][id]=="45*") ui->checkBoxFv4->setChecked(true);
//            if(dialogValues[1][id]=="90*") ui->checkBoxFv5->setChecked(true);
//            if(dialogValues[1][id]=="180*") ui->checkBoxFv6->setChecked(true);
//            if(dialogValues[1][id]=="0.9 dB") ui->checkBoxAtt1->setChecked(true);
//            if(dialogValues[1][id]=="1.8 dB")  ui->checkBoxAtt2->setChecked(true);
//            if(dialogValues[1][id]=="3.6 dB") ui->checkBoxAtt3->setChecked(true);
//            if(dialogValues[1][id]=="7.2 dB") ui->checkBoxAtt4->setChecked(true);
//            if(dialogValues[1][id]=="14.4 dB") ui->checkBoxAtt5->setChecked(true);
//        }

//    for(int idx=1;idx<17;idx++) column1combos[idx]->setCurrentText(settings.value(column1combos[idx]->objectName(),"").toString());
//    for(int idx=1;idx<17;idx++) column2combos[idx]->setCurrentText(settings.value(column2combos[idx]->objectName(), "").toString());
//    for(int idx=1;idx<17;idx++) column3spins[idx]->setValue(settings.value(column3spins[idx]->objectName(), "").toInt());
//    settings.endGroup();


       //ui->childwidget->ui->comboBox_33->setCurrentText("DKJ:TYJ");
}




