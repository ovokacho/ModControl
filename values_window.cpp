#include "values_window.h"
#include "ui_values_window.h"

values_window::values_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::values_window)
{
    ui->setupUi(this);
     SettingsFile = "settingsval.ini";
     list_of_types = (QStringList()<<"Аттенюатор"<<"Фазовращатель"<<"Другое");
     ui->comboType->addItems(list_of_types);
     fillSetList();
     loadSettingsOfSet(ui->comboSet->currentText());
     connect(ui->comboSet, SIGNAL(currentIndexChanged(QString)),this, SLOT(setcomboselected()));
}

values_window::~values_window()
{
    delete ui;
}
void values_window::setcomboselected()
{
   //if(ui->comboBox_17->currentText() == "Новое")
QString currentText = ui->comboSet->currentText();
loadSettingsOfSet(ui->comboSet->currentText());
//fillSettings(currentText);
}
void values_window::deletegroup(QString group)
{
QSettings settingsdelete(SettingsFile, QSettings::IniFormat);
QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Удаление набора", "Удалить набор?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    settingsdelete.remove(group);
    ui->comboSet->removeItem(ui->comboSet->currentIndex());
    //() << "Yes was clicked";
  } else {
    qDebug() << "Yes was *not* clicked";
  }
}
void values_window::saveSettings()
{
    QLineEdit* column1combos[10];
    column1combos[0] = ui->val1;
    column1combos[1] = ui->val2;
    column1combos[2] = ui->val3;
    column1combos[3] = ui->val4;
    column1combos[4] = ui->val5;
    column1combos[5] = ui->val6;
    column1combos[6] = ui->val7;
    column1combos[7] = ui->val8;
    column1combos[8] = ui->val9;
    column1combos[9] = ui->val10;


 //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
 QSettings settings(SettingsFile, QSettings::IniFormat);
 settings.setIniCodec( "UTF-8" );
 //settings.setIniCodec( codec );
 settings.beginWriteArray(ui->comboSet->currentText());
 //settings.beginGroup(ui->comboBox_17->currentText());
 for (int i = 0; i < 10; ++i) {
     settings.setArrayIndex(i);
     settings.setValue("value", column1combos[i]->text());
 }
 settings.setArrayIndex(10);
 settings.setValue("type", ui->comboType->currentIndex());
 //for(int idx=1;idx<17;idx++) settings.setValue(column1combos[idx]->objectName(), column1combos[idx]->currentText());
 settings.endArray();

// int position = ui->comboBox_17->currentIndex();
// fillToolList();
// ui->comboBox_17->setCurrentIndex(position);
// qDebug() << "saved";
}
void values_window::fillSetList()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(SettingsFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboSet->clear();
    ui->comboSet->addItems(groups);
    ui->comboSet->addItem("Новое");
    //qDebug() << groups;
}
void values_window::loadSettingsOfSet(QString set)
{
    QLineEdit* column1combos[10];
    column1combos[0] = ui->val1;
    column1combos[1] = ui->val2;
    column1combos[2] = ui->val3;
    column1combos[3] = ui->val4;
    column1combos[4] = ui->val5;
    column1combos[5] = ui->val6;
    column1combos[6] = ui->val7;
    column1combos[7] = ui->val8;
    column1combos[8] = ui->val9;
    column1combos[9] = ui->val10;

  //  QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
 QSettings settings(SettingsFile, QSettings::IniFormat);
  //  settings.setIniCodec( codec );
 settings.setIniCodec( "UTF-8" );
 settings.beginReadArray(set);
// settings.beginGroup(set);
 for(int idx=0;idx<10;idx++) {
     settings.setArrayIndex(idx);
     column1combos[idx]->setText(settings.value("value").toString());
 }
 settings.setArrayIndex(10);
 ui->comboType->setCurrentIndex(settings.value("type").toInt());
 settings.endArray();
// qDebug() << "loaded";
}
void values_window::on_saveButton_clicked()
{
    saveSettings();
   // QMessageBox::question(this, "t", "Сохранено");
    fillSetList();
}

void values_window::on_deleteButton_clicked()
{
    QString grp = ui->comboSet->currentText();
    deletegroup(grp);
}
