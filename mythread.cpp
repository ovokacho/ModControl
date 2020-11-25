#include "mythread.h"
#include <QDebug>
#include <windows.h>

MyThread::MyThread(QString s) : name(s)
{
}

void MyThread::run()
{
for(int i = 0; i <= 100; i++)
{
emit send(i);
Sleep(1000);
}
}

void MyThread::receiveGlobalVar(int globalVar)
{
qDebug() << "globalVar = " << globalVar;
this->globalVar = globalVar;
}
