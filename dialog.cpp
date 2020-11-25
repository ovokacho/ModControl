 #include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QQueue>
#include <QDate>
#include <QSettings>
#include <QTextCodec>
#include <QApplication>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

   //m_sSettingsFile = "C:/Users/agoerlov/Documents/build-qttest-Desktop_Qt_5_3_MinGW_32bit-Debug/demosettings.ini";
    m_sSettingsFile = "settings.ini"; // имя/полное расположение файла настроек
    SettingsFile = "settingsval.ini";

    //list_of_types=(QStringList()<<"Аттенюатор"<<"Фазовращатель"<<"Другое");
    loadTypes();
//    ui->comboBox->addItems(list_of_types);
//    ui->comboBox_2->addItems(list_of_types);
//    ui->comboBox_3->addItems(list_of_types);
//    ui->comboBox_4->addItems(list_of_types);
//    ui->comboBox_5->addItems(list_of_types);
//    ui->comboBox_6->addItems(list_of_types);
//    ui->comboBox_7->addItems(list_of_types);
//    ui->comboBox_8->addItems(list_of_types);
//    ui->comboBox_9->addItems(list_of_types);
//    ui->comboBox_10->addItems(list_of_types);
//    ui->comboBox_11->addItems(list_of_types);
//    ui->comboBox_12->addItems(list_of_types);
//    ui->comboBox_13->addItems(list_of_types);
//    ui->comboBox_14->addItems(list_of_types);
//    ui->comboBox_15->addItems(list_of_types);
//    ui->comboBox_16->addItems(list_of_types);
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->comboBox_5->setCurrentIndex(-1);
    ui->comboBox_6->setCurrentIndex(-1);
    ui->comboBox_7->setCurrentIndex(-1);
    ui->comboBox_8->setCurrentIndex(-1);
    ui->comboBox_9->setCurrentIndex(-1);
    ui->comboBox_10->setCurrentIndex(-1);
    ui->comboBox_11->setCurrentIndex(-1);
    ui->comboBox_12->setCurrentIndex(-1);
    ui->comboBox_13->setCurrentIndex(-1);
    ui->comboBox_14->setCurrentIndex(-1);
    ui->comboBox_15->setCurrentIndex(-1);
    ui->comboBox_16->setCurrentIndex(-1);

    ui->comboBox_34->setCurrentIndex(-1);
    ui->comboBox_35->setCurrentIndex(-1);
    ui->comboBox_36->setCurrentIndex(-1);

    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(19);
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(19);
    ui->spinBox_3->setMinimum(0);
    ui->spinBox_3->setMaximum(19);
    ui->spinBox_4->setMinimum(0);
    ui->spinBox_4->setMaximum(19);
    ui->spinBox_5->setMinimum(0);
    ui->spinBox_5->setMaximum(19);
    ui->spinBox_6->setMinimum(0);
    ui->spinBox_6->setMaximum(19);
    ui->spinBox_7->setMinimum(0);
    ui->spinBox_7->setMaximum(19);
    ui->spinBox_8->setMinimum(0);
    ui->spinBox_8->setMaximum(19);
    ui->spinBox_9->setMinimum(0);
    ui->spinBox_9->setMaximum(19);
    ui->spinBox_10->setMinimum(0);
    ui->spinBox_10->setMaximum(19);
    ui->spinBox_11->setMinimum(0);
    ui->spinBox_11->setMaximum(19);
    ui->spinBox_12->setMinimum(0);
    ui->spinBox_12->setMaximum(19);
    ui->spinBox_13->setMinimum(0);
    ui->spinBox_13->setMaximum(19);
    ui->spinBox_14->setMinimum(0);
    ui->spinBox_14->setMaximum(19);
    ui->spinBox_15->setMinimum(0);
    ui->spinBox_15->setMaximum(19);
    ui->spinBox_16->setMinimum(0);
    ui->spinBox_16->setMaximum(19);

    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(DeleteButtonClicked()));
    connect(ui->comboBox_17, SIGNAL(currentIndexChanged(QString)),this, SLOT(toolcomboselected()));

    fillToolList();
    QString ct = ui->comboBox_17->currentText();
    fillSettings(ct);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::loadTypes()
{
    //if(ui->comboBox_17->currentText() == "Новое")
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
     //settingsstart.setIniCodec( "UTF-8" );
     QStringList groups = settingsstart1.childGroups();
     list_of_types=(groups);

     ui->comboBox->addItems(list_of_types);
     ui->comboBox_2->addItems(list_of_types);
     ui->comboBox_3->addItems(list_of_types);
     ui->comboBox_4->addItems(list_of_types);
     ui->comboBox_5->addItems(list_of_types);
     ui->comboBox_6->addItems(list_of_types);
     ui->comboBox_7->addItems(list_of_types);
     ui->comboBox_8->addItems(list_of_types);
     ui->comboBox_9->addItems(list_of_types);
     ui->comboBox_10->addItems(list_of_types);
     ui->comboBox_11->addItems(list_of_types);
     ui->comboBox_12->addItems(list_of_types);
     ui->comboBox_13->addItems(list_of_types);
     ui->comboBox_14->addItems(list_of_types);
     ui->comboBox_15->addItems(list_of_types);
     ui->comboBox_16->addItems(list_of_types);

     ui->comboBox_34->addItems(list_of_types);
     ui->comboBox_35->addItems(list_of_types);
     ui->comboBox_36->addItems(list_of_types);
}

void Dialog::on_m_pButton_clicked()
{
    saveSettings();
}

void Dialog::DeleteButtonClicked()
{
    QString grp = ui->comboBox_17->currentText();
    deletegroup(grp);
}

void Dialog::fillToolList()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(m_sSettingsFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboBox_17->clear();
    ui->comboBox_17->addItems(groups);
    ui->comboBox_17->addItem("Новое");
    //qDebug() << groups;
}

void Dialog::fillSettings(QString text)
{
   //if(ui->comboBox_17->currentText() == "Новое")
//qDebug() << text;
loadSettingsOfTool(text);
}

void Dialog::toolcomboselected()
{
   //if(ui->comboBox_17->currentText() == "Новое")
QString currentText = ui->comboBox_17->currentText();
fillSettings(currentText);
}

void Dialog::deletegroup(QString group)
{
QSettings settingsdelete(m_sSettingsFile, QSettings::IniFormat);
QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Удаление устройства", "Удалить устройство?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    settingsdelete.remove(group);
    ui->comboBox_17->removeItem(ui->comboBox_17->currentIndex());
    //() << "Yes was clicked";
  } else {
    qDebug() << "Yes was *not* clicked";
  }
}

void Dialog::loadSettingsOfTool(QString tool)
{
    QComboBox* column1combos[20];
    column1combos[1] = ui->comboBox;
    column1combos[2] = ui->comboBox_2;
    column1combos[3] = ui->comboBox_3;
    column1combos[4] = ui->comboBox_4;
    column1combos[5] = ui->comboBox_5;
    column1combos[6] = ui->comboBox_6;
    column1combos[7] = ui->comboBox_7;
    column1combos[8] = ui->comboBox_8;
    column1combos[9] = ui->comboBox_9;
    column1combos[10] = ui->comboBox_10;
    column1combos[11] = ui->comboBox_11;
    column1combos[12] = ui->comboBox_12;
    column1combos[13] = ui->comboBox_13;
    column1combos[14] = ui->comboBox_14;
    column1combos[15] = ui->comboBox_15;
    column1combos[16] = ui->comboBox_16;

    column1combos[17] = ui->comboBox_34;
    column1combos[18] = ui->comboBox_35;
    column1combos[19] = ui->comboBox_36;

    QComboBox* column2combos[20];
    column2combos[1] = ui->comboBox_18;
    column2combos[2] = ui->comboBox_19;
    column2combos[3] = ui->comboBox_20;
    column2combos[4] = ui->comboBox_21;
    column2combos[5] = ui->comboBox_22;
    column2combos[6] = ui->comboBox_23;
    column2combos[7] = ui->comboBox_24;
    column2combos[8] = ui->comboBox_25;
    column2combos[9] = ui->comboBox_26;
    column2combos[10] = ui->comboBox_27;
    column2combos[11] = ui->comboBox_28;
    column2combos[12] = ui->comboBox_29;
    column2combos[13] = ui->comboBox_30;
    column2combos[14] = ui->comboBox_31;
    column2combos[15] = ui->comboBox_32;
    column2combos[16] = ui->comboBox_33;

    column2combos[17] = ui->comboBox_37;
    column2combos[18] = ui->comboBox_38;
    column2combos[19] = ui->comboBox_39;

    QSpinBox *column3spins[20];
    column3spins[1] = ui->spinBox;
    column3spins[2] = ui->spinBox_2;
    column3spins[3] = ui->spinBox_3;
    column3spins[4] = ui->spinBox_4;
    column3spins[5] = ui->spinBox_5;
    column3spins[6] = ui->spinBox_6;
    column3spins[7] = ui->spinBox_7;
    column3spins[8] = ui->spinBox_8;
    column3spins[9] = ui->spinBox_9;
    column3spins[10] = ui->spinBox_10;
    column3spins[11] = ui->spinBox_11;
    column3spins[12] = ui->spinBox_12;
    column3spins[13] = ui->spinBox_13;
    column3spins[14] = ui->spinBox_14;
    column3spins[15] = ui->spinBox_15;
    column3spins[16] = ui->spinBox_16;

    column3spins[17] = ui->spinBox_17;
    column3spins[18] = ui->spinBox_18;
    column3spins[19] = ui->spinBox_19;

  //  QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);
  //  settings.setIniCodec( codec );
// settings.setIniCodec( "UTF-8" );
 settings.beginGroup(tool);
 for(int idx=1;idx<20;idx++) column1combos[idx]->setCurrentText(settings.value(column1combos[idx]->objectName(),"").toString());
 for(int idx=1;idx<20;idx++) column2combos[idx]->setCurrentText(settings.value(column2combos[idx]->objectName(), "").toString());
 for(int idx=1;idx<20;idx++) column3spins[idx]->setValue(settings.value(column3spins[idx]->objectName(), "").toInt());
 settings.endGroup();
// qDebug() << "loaded";
}

void Dialog::saveSettings()
{
    QComboBox* column1combos[20];
    column1combos[1] = ui->comboBox;
    column1combos[2] = ui->comboBox_2;
    column1combos[3] = ui->comboBox_3;
    column1combos[4] = ui->comboBox_4;
    column1combos[5] = ui->comboBox_5;
    column1combos[6] = ui->comboBox_6;
    column1combos[7] = ui->comboBox_7;
    column1combos[8] = ui->comboBox_8;
    column1combos[9] = ui->comboBox_9;
    column1combos[10] = ui->comboBox_10;
    column1combos[11] = ui->comboBox_11;
    column1combos[12] = ui->comboBox_12;
    column1combos[13] = ui->comboBox_13;
    column1combos[14] = ui->comboBox_14;
    column1combos[15] = ui->comboBox_15;
    column1combos[16] = ui->comboBox_16;

    column1combos[17] = ui->comboBox_34;
    column1combos[18] = ui->comboBox_35;
    column1combos[19] = ui->comboBox_36;

    QComboBox* column2combos[20];
    column2combos[1] = ui->comboBox_18;
    column2combos[2] = ui->comboBox_19;
    column2combos[3] = ui->comboBox_20;
    column2combos[4] = ui->comboBox_21;
    column2combos[5] = ui->comboBox_22;
    column2combos[6] = ui->comboBox_23;
    column2combos[7] = ui->comboBox_24;
    column2combos[8] = ui->comboBox_25;
    column2combos[9] = ui->comboBox_26;
    column2combos[10] = ui->comboBox_27;
    column2combos[11] = ui->comboBox_28;
    column2combos[12] = ui->comboBox_29;
    column2combos[13] = ui->comboBox_30;
    column2combos[14] = ui->comboBox_31;
    column2combos[15] = ui->comboBox_32;
    column2combos[16] = ui->comboBox_33;

    column2combos[17] = ui->comboBox_37;
    column2combos[18] = ui->comboBox_38;
    column2combos[19] = ui->comboBox_39;

    QSpinBox* column3spins[20];
    column3spins[1] = ui->spinBox;
    column3spins[2] = ui->spinBox_2;
    column3spins[3] = ui->spinBox_3;
    column3spins[4] = ui->spinBox_4;
    column3spins[5] = ui->spinBox_5;
    column3spins[6] = ui->spinBox_6;
    column3spins[7] = ui->spinBox_7;
    column3spins[8] = ui->spinBox_8;
    column3spins[9] = ui->spinBox_9;
    column3spins[10] = ui->spinBox_10;
    column3spins[11] = ui->spinBox_11;
    column3spins[12] = ui->spinBox_12;
    column3spins[13] = ui->spinBox_13;
    column3spins[14] = ui->spinBox_14;
    column3spins[15] = ui->spinBox_15;
    column3spins[16] = ui->spinBox_16;

    column3spins[17] = ui->spinBox_17;
    column3spins[18] = ui->spinBox_18;
    column3spins[19] = ui->spinBox_19;

 //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);
 settings.setIniCodec( "UTF-8" );
 //settings.setIniCodec( codec );
 settings.beginGroup(ui->comboBox_17->currentText());
 for(int idx=1;idx<20;idx++) settings.setValue(column1combos[idx]->objectName(), column1combos[idx]->currentText());
 for(int idx=1;idx<20;idx++) settings.setValue(column2combos[idx]->objectName(), column2combos[idx]->currentText());
 for(int idx=1;idx<20;idx++) settings.setValue(column3spins[idx]->objectName(), column3spins[idx]->value());
 settings.endGroup();
 int position = ui->comboBox_17->currentIndex();
 fillToolList();
 ui->comboBox_17->setCurrentIndex(position);
// qDebug() << "saved";
}

void Dialog::on_comboBox_currentIndexChanged(){
    ui->comboBox_18->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value") != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_18->addItems(que);
}

void Dialog::on_comboBox_2_currentIndexChanged(){
    ui->comboBox_19->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_2->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_19->addItems(que);
}

void Dialog::on_comboBox_3_currentIndexChanged(){
    ui->comboBox_20->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_3->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_20->addItems(que);
}

void Dialog::on_comboBox_4_currentIndexChanged(){
    ui->comboBox_21->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_4->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_21->addItems(que);
}

void Dialog::on_comboBox_5_currentIndexChanged(){
    ui->comboBox_22->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_5->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_22->addItems(que);
}

void Dialog::on_comboBox_6_currentIndexChanged(){
    ui->comboBox_23->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_6->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_23->addItems(que);
}

void Dialog::on_comboBox_7_currentIndexChanged(){
    ui->comboBox_24->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_7->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_24->addItems(que);
}

void Dialog::on_comboBox_8_currentIndexChanged(){
    ui->comboBox_25->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_8->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_25->addItems(que);
}

void Dialog::on_comboBox_9_currentIndexChanged(){
    ui->comboBox_26->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_9->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_26->addItems(que);
}

void Dialog::on_comboBox_10_currentIndexChanged(){
    ui->comboBox_27->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_10->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_27->addItems(que);
}

void Dialog::on_comboBox_11_currentIndexChanged(){
    ui->comboBox_28->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_11->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_28->addItems(que);
}

void Dialog::on_comboBox_12_currentIndexChanged(){
    ui->comboBox_29->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_12->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_29->addItems(que);
}

void Dialog::on_comboBox_13_currentIndexChanged(){
    ui->comboBox_30->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_13->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_30->addItems(que);
}

void Dialog::on_comboBox_14_currentIndexChanged(){
    ui->comboBox_31->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_14->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_31->addItems(que);
}

void Dialog::on_comboBox_15_currentIndexChanged(){
    ui->comboBox_32->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_15->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_32->addItems(que);
}

void Dialog::on_comboBox_16_currentIndexChanged(){
    ui->comboBox_33->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_16->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_33->addItems(que);
}

void Dialog::on_comboBox_34_currentIndexChanged(){
    ui->comboBox_37->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_34->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_37->addItems(que);
}

void Dialog::on_comboBox_35_currentIndexChanged(){
    ui->comboBox_38->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_35->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_38->addItems(que);
}

void Dialog::on_comboBox_36_currentIndexChanged(){
    ui->comboBox_39->clear();
     QSettings settingsstart1(SettingsFile, QSettings::IniFormat);
    // list_of_values_att
     QQueue<QString> que;
     QString typeval1 = ui->comboBox_36->currentText();
     int size = settingsstart1.beginReadArray(typeval1);
     for (int i = 0; i < size; ++i) {
           settingsstart1.setArrayIndex(i);
           if (settingsstart1.value("value").toString() != "") {
           que.enqueue(settingsstart1.value("value").toString());
           }
     }
     settingsstart1.endArray();
     ui->comboBox_39->addItems(que);
}
//QString* Dialog::value()
//{
//    //ui->comboBox->currentText();
//    static QString dialogValues[3][17];
//    dialogValues[0][0]=ui->comboBox_17->currentText();

//    dialogValues[0][1]=ui->comboBox->currentText();
//    dialogValues[0][2]=ui->comboBox_2->currentText();
//    dialogValues[0][3]=ui->comboBox_3->currentText();
//    dialogValues[0][4]=ui->comboBox_4->currentText();
//    dialogValues[0][5]=ui->comboBox_5->currentText();
//    dialogValues[0][6]=ui->comboBox_6->currentText();
//    dialogValues[0][7]=ui->comboBox_7->currentText();
//    dialogValues[0][8]=ui->comboBox_8->currentText();
//    dialogValues[0][9]=ui->comboBox_9->currentText();
//    dialogValues[0][10]=ui->comboBox_10->currentText();
//    dialogValues[0][11]=ui->comboBox_11->currentText();
//    dialogValues[0][12]=ui->comboBox_12->currentText();
//    dialogValues[0][13]=ui->comboBox_13->currentText();
//    dialogValues[0][14]=ui->comboBox_14->currentText();
//    dialogValues[0][15]=ui->comboBox_15->currentText();
//    dialogValues[0][16]=ui->comboBox_16->currentText();

//    dialogValues[1][1]=ui->comboBox_18->currentText();
//    dialogValues[1][2]=ui->comboBox_19->currentText();
//    dialogValues[1][3]=ui->comboBox_20->currentText();
//    dialogValues[1][4]=ui->comboBox_21->currentText();
//    dialogValues[1][5]=ui->comboBox_22->currentText();
//    dialogValues[1][6]=ui->comboBox_23->currentText();
//    dialogValues[1][7]=ui->comboBox_24->currentText();
//    dialogValues[1][8]=ui->comboBox_25->currentText();
//    dialogValues[1][9]=ui->comboBox_26->currentText();
//    dialogValues[1][10]=ui->comboBox_27->currentText();
//    dialogValues[1][11]=ui->comboBox_28->currentText();
//    dialogValues[1][12]=ui->comboBox_29->currentText();
//    dialogValues[1][13]=ui->comboBox_30->currentText();
//    dialogValues[1][14]=ui->comboBox_31->currentText();
//    dialogValues[1][15]=ui->comboBox_32->currentText();
//    dialogValues[1][16]=ui->comboBox_33->currentText();

//    dialogValues[2][1]=ui->spinBox->value();
//    dialogValues[2][2]=ui->spinBox_2->value();
//    dialogValues[2][3]=ui->spinBox_3->value();
//    dialogValues[2][4]=ui->spinBox_4->value();
//    dialogValues[2][5]=ui->spinBox_5->value();
//    dialogValues[2][6]=ui->spinBox_6->value();
//    dialogValues[2][7]=ui->spinBox_7->value();
//    dialogValues[2][8]=ui->spinBox_8->value();
//    dialogValues[2][9]=ui->spinBox_9->value();
//    dialogValues[2][10]=ui->spinBox_10->value();
//    dialogValues[2][11]=ui->spinBox_11->value();
//    dialogValues[2][12]=ui->spinBox_12->value();
//    dialogValues[2][13]=ui->spinBox_13->value();
//    dialogValues[2][14]=ui->spinBox_14->value();
//    dialogValues[2][15]=ui->spinBox_15->value();
//    dialogValues[2][16]=ui->spinBox_16->value();

//    return dialogValues;
//}
