#ifndef VALUES_WINDOW_H
#define VALUES_WINDOW_H

#include <QDialog>
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
class values_window;
}

class values_window : public QDialog
{
    Q_OBJECT

public:
    explicit values_window(QWidget *parent = nullptr);
    ~values_window();

private slots:

    void on_saveButton_clicked();
    void setcomboselected();

    void on_deleteButton_clicked();

private:

    Ui::values_window *ui;
    void saveSettings();
    void fillSetList();
    void loadSettingsOfSet(QString set);
    void deletegroup(QString group);
    QString SettingsFile;
    QStringList list_of_types;
};

#endif // VALUES_WINDOW_H
