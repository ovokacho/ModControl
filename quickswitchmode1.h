#ifndef QUICKSWITCHMODE1_H
#define QUICKSWITCHMODE1_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QThread>
#include "exampleobject.h"
#include <QStatusBar>


namespace Ui {
class quickSwitchMode1;
}
class SettingsDialog;
class quickSwitchMode1 : public QDialog
{
    Q_OBJECT

public:

    virtual void closeEvent ( QCloseEvent * event );


    explicit quickSwitchMode1(QWidget *parent = nullptr);
    ~quickSwitchMode1();
    void fillToolListMode();
    unsigned long int message2;
    unsigned long int message1;
    bool stopW;
private slots:
    void slotCalculateAtt();
    void slotCalculateAtt1();
    void slotCalculateFv();
    void slotCalculateFv1();
    void slotCalculateElse();
    void slotCalculateElse1();
    void on_pushButtonRefresh_clicked();
    void addCheckBoxAtt(QString name, QString b);
    void addCheckBoxFv(QString name, QString b);
    void addCheckBoxElse(QString name, QString b);
     void openSerialPort();
     void closeSerialPort();
    void sendCommandLine(int msg);
     void on_sendButton_clicked();
     void update (int i);

     void on_stopButton_clicked();

     void on_PortButton_clicked();

     void toolcomboselected();

signals:
     void sendGlobalVar1(int);

private:

    Ui::quickSwitchMode1 *ui;
   QString SettingsFile;
   QString SettingsOfFile;
   void loadini(QString tool);
   QSerialPort *port_serial;
   SettingsDialog *settings;
   bool started;
   bool HEXIsLoaded;

   QThread thread_1;
   ExampleObject exampleObject_1;

};

#endif // QUICKSWITCHMODE1_H
