#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QString>
#include <QtSerialPort/QSerialPort>

class MyClass:public QObject
{
Q_OBJECT
Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
public:
    MyClass(QString name);
    bool running() const;

public slots:
    void doWork();
    void stopWork();
    //inline void SetStop();
    void setrunning(bool running);
signals:
    void send(int);
    void finished();
    void runningChanged(bool running);

private:
    QString name;
    bool isRunning;
    unsigned long int globalVar2;
    unsigned long int globalVar1;
    int globalVar;
    bool m_running;
};

#endif // MYCLASS_H
