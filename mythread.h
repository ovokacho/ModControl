#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>

class MyThread : public QThread
{
Q_OBJECT
public:
explicit MyThread(QString s);

void run();

public slots:
void receiveGlobalVar (int i);

signals:
void send(int);

private:
QString name;

int globalVar;
};

#endif // MYTHREAD_H
