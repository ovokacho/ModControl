#include "exampleobject.h"
#include <QDebug>
#include <windows.h>

ExampleObject::ExampleObject(QObject *parent) : QObject(parent)
{

}

bool ExampleObject::running() const
{
    return m_running;
}

unsigned long ExampleObject::msg() const
{
    return m_msg;
}

void ExampleObject::run()
{
    int i = 0;
    while(m_running)
    {
    emit send(i);
    //Sleeper::msleep(2000);
    Sleep(m_msg);
    i++;
    }
    emit finished();

}
//void ExampleObject::receiveGlobalVar(int globalVar)
//{
//qDebug() << "globalVar = " << globalVar;
//this->globalVar = static_cast<unsigned long>(globalVar);
//qDebug() << "globalVar1 = " << this->globalVar;
//}
void ExampleObject::setrunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void ExampleObject::setMsg(unsigned long msg)
{
    if (m_msg == msg)
        return;

    m_msg = msg;
    emit msgChanged(m_msg);
}


