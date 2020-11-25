#ifndef VALUES_WIN_H
#define VALUES_WIN_H

#include <QWidget>
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
class values_win;
}

class values_win : public QWidget
{
    Q_OBJECT

public:
    explicit values_win(QWidget *parent = nullptr);
    ~values_win();

private slots:
    void on_pushButton_clicked();

private:
    Ui::values_win *ui;
     void saveSettings();

     QString SettingsFile;
};

#endif // VALUES_WIN_H
