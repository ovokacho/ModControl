#include "values_win.h"
#include "ui_values_win.h"
#include <QSettings>

values_win::values_win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::values_win)
{
    ui->setupUi(this);
    SettingsFile = "settingsval.ini"; // имя/полное расположение файла настроек
}

values_win::~values_win()
{
    delete ui;
}
void values_win::saveSettings()
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
 settings.beginWriteArray("values");
 //settings.beginGroup(ui->comboBox_17->currentText());
 for (int i = 0; i < 9; ++i) {
     settings.setArrayIndex(i+1);
     settings.setValue("value", column1combos[i]->text());
 }
 //for(int idx=1;idx<17;idx++) settings.setValue(column1combos[idx]->objectName(), column1combos[idx]->currentText());
 settings.endArray();

// int position = ui->comboBox_17->currentIndex();
// fillToolList();
// ui->comboBox_17->setCurrentIndex(position);
// qDebug() << "saved";
}
void values_win::on_pushButton_clicked()
{
    saveSettings();
}
