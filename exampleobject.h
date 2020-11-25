#ifndef EXAMPLEOBJECT_H
#define EXAMPLEOBJECT_H

#include <QObject>

class ExampleObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setrunning NOTIFY runningChanged)

    Q_PROPERTY(unsigned long msg READ msg WRITE setMsg NOTIFY msgChanged)
    bool m_running;

public:
    explicit ExampleObject(QObject *parent = nullptr);


bool running() const;



unsigned long msg() const;

signals:
    void finished();
    void runningChanged(bool running);
    void send(int);


    void msgChanged(unsigned long msg);

public slots:
    //void receiveGlobalVar (int i);
    void run();
    void setrunning(bool running);


    void setMsg(unsigned long msg);

private:
    unsigned long globalVar = 100;

    unsigned long m_msg;
};

#endif // EXAMPLEOBJECT_H
