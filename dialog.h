#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDate>
#include <QSettings>
#include <QTextCodec>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Ui::Dialog *ui;
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
//    QString *value();


private slots:

    void on_comboBox_currentIndexChanged();
    void on_comboBox_2_currentIndexChanged();
    void on_comboBox_3_currentIndexChanged();
    void on_comboBox_4_currentIndexChanged();
    void on_comboBox_5_currentIndexChanged();
    void on_comboBox_6_currentIndexChanged();
    void on_comboBox_7_currentIndexChanged();
    void on_comboBox_8_currentIndexChanged();
    void on_comboBox_9_currentIndexChanged();
    void on_comboBox_10_currentIndexChanged();
    void on_comboBox_11_currentIndexChanged();
    void on_comboBox_12_currentIndexChanged();
    void on_comboBox_13_currentIndexChanged();
    void on_comboBox_14_currentIndexChanged();
    void on_comboBox_15_currentIndexChanged();
    void on_comboBox_16_currentIndexChanged();

    void on_comboBox_34_currentIndexChanged();
    void on_comboBox_35_currentIndexChanged();
    void on_comboBox_36_currentIndexChanged();

    void on_m_pButton_clicked();
    void toolcomboselected();
    void DeleteButtonClicked();





private:

    QString SettingsFile;
    QString m_sSettingsFile;
    QStringList list_of_values_att;
    QStringList list_of_values_fase;
    QStringList list_of_types;

//    QComboBox* column1combos[17];
//    QComboBox* column2combos[17];
//    QSpinBox *column3spins[17];

   //  QLabel* m_pLabel;
    // QLineEdit* m_pEdit;
    // QPushButton* m_pButton;

    void loadTypes();
    void loadSettings();
    void loadSettingsOfTool(QString tool);
    void saveSettings();
    void fillSettings(QString text);
    void deletegroup(QString group);
    void fillToolList();
};

#endif // DIALOG_H


