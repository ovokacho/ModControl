#ifndef MAINW_H
#define MAINW_H

#include <QMainWindow>
//#include <QSignalMapper>
#include <QtSerialPort/QSerialPort>
#include <QSettings>

namespace Ui {
class MainW;
}
class SettingsDialog;

class MainW : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainW(QWidget *parent = 0);
    ~MainW();
    Ui::MainW *ui;
    void fillToolListMain();
    unsigned long int message;
private:
    QSerialPort *port_serial;
    SettingsDialog *settings;
    //QSignalMapper *mapper;
    QString SettingsOfFile;
    void loadini(QString tool);
    ////////////////
    void initActionsConnections();
    inline int read_string_hex(char *str, int len);
    bool started;
    bool HEXIsLoaded;
    QString SettingsFile;
    QString SettingsPss;
private slots:
    //void on_addButton_clicked();    // СЛОТ-обработчик нажатия кнопки добавления
    //void on_deleteButton_clicked(); // СЛОТ-обработчик нажатия кнопки удаления
    void slotCalculateAtt();
    void slotCalculateFv();
    void slotCalculateElse();  // СЛОТ для получения номера нажатой динамической кнопки
    void addCheckBoxAtt(QString name, QString b);
    void addCheckBoxFv(QString name, QString b);
    void addCheckBoxElse(QString name, QString b);
    void toolcomboselected();
    void openTools();
    void openMode();
    void openSets();
    void on_pushButtonRefresh_2_clicked();

    //////////////
    //void resizeEvent(QResizeEvent *);

    void openSerialPort();
    void closeSerialPort();
    //void readData();
    //void writeData(unsigned long int &data);
    //void putData(unsigned long int &data);
    //void handleError(QSerialPort::SerialPortError error);

    void sendCommandLine();

   // void initActionsDisplay();
};

#endif // MAINW_H
