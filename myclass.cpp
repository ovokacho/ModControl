#include "myclass.h"
#include <QDebug>
#include <windows.h>

MyClass::MyClass(QString s) : name(s)
{

}

bool MyClass::running() const
{
    return m_running;
}

void MyClass::doWork()
{
    int i = 0;
    while(m_running)
    {
    emit send(i);
    Sleep(1000);
    i++;
}
emit finished();
//for(int i = 0; i <= 100; i++)
//{
//emit send(i);
//Sleep(1000);
//}
//}
}

//inline void MyClass::SetStop( void ) { isRunning = false; }

void MyClass::stopWork()
{
isRunning = false;
}


void MyClass::setrunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}
