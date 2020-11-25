#include "form.h"
#include "ui_Form.h"
#include <iostream>
#include <QWidget>
#include <dialog.h>
#include <QSettings>
#include <QGroupBox>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    SettingsOfFile = "settings.ini"; // имя/полное расположение файла настроек

    fillToolListMain();
    QString currentTool = ui->comboBoxToolList->currentText();
    loadini(currentTool);
connect(ui->comboBoxToolList, SIGNAL(currentIndexChanged(QString)),this, SLOT(toolcomboselected()));
}

Form::~Form()
{
    delete ui;
}
void Form::addCheckBoxAtt(QString name)
{
    QDynamicElement *checkbox = new QDynamicElement(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    checkbox->setText(name);
    /* Добавляем кнопку в слой с вертикальной компоновкой
     * */
    ui->verticalLayoutAtt->addWidget(checkbox);
    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
     * */
    //connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
}

void Form::addCheckBoxFv(QString name){
    QDynamicElement *checkbox = new QDynamicElement(this);
    checkbox->setText(name);
    ui->verticalLayoutFv->addWidget(checkbox);
}

void Form::addCheckBoxElse(QString name){
    QDynamicElement *checkbox = new QDynamicElement(this);
    checkbox->setText(name);
    ui->verticalLayoutOther->addWidget(checkbox);
}

//void Form::on_addButton_clicked()
//{
//    QDynamicElement *button = new QDynamicElement(this);  // Создаем объект динамической кнопки
//    /* Устанавливаем текст с номером этой кнопки
//     * */
//    button->setText("CheckBox " + QString::number(button->getID()));
//    /* Добавляем кнопку в слой с вертикальной компоновкой
//     * */
//    ui->verticalLayoutOther->addWidget(button);
//    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
//     * */
//    connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
//}
void Form::toolcomboselected()
{
QString currentText = ui->comboBoxToolList->currentText();
while ( QLayoutItem* item = ui->verticalLayoutFv->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
while ( QLayoutItem* item = ui->verticalLayoutAtt->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
while ( QLayoutItem* item = ui->verticalLayoutOther->takeAt(0) )
   {
       Q_ASSERT( ! item->layout() ); // otherwise the layout will leak
       delete item->widget();
       delete item;
   }
loadini(currentText);
}

void Form::on_pushButton_clicked()
{
    Dialog dialog;
    if (dialog.exec())
    {

        dialog.open();
    }
//      QString *x = dialog.value();

}

void Form::fillToolListMain()
{
   //if(ui->comboBox_17->currentText() == "Новое")
    QSettings settingsstart(SettingsOfFile, QSettings::IniFormat);
    //settingsstart.setIniCodec( "UTF-8" );
    QStringList groups = settingsstart.childGroups();
    ui->comboBoxToolList->clear();
    ui->comboBoxToolList->addItems(groups);
    //ui->comboBoxToolList->addItem("Новое");
}

void Form::on_pushButtonRefresh_clicked()
{
    fillToolListMain();
}

void Form::loadini(QString tool)
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

        for(int id=0;id<16;id++){
            if((dialogValues[0][id]=="Аттенюатор")&&(dialogValues[0][id]!="")) addCheckBoxAtt(dialogValues[1][id]);
            if((dialogValues[0][id]=="Фазовращатель")&&(dialogValues[0][id]!="")) addCheckBoxFv(dialogValues[1][id]);
            if((dialogValues[0][id]!="Фазовращатель") && (dialogValues[0][id]!="Аттенюатор")&&(dialogValues[0][id]!="")) addCheckBoxElse(dialogValues[1][id]);


}

}
