#ifndef QDYNAMICELEMENT_H
#define QDYNAMICELEMENT_H

#include <QCheckBox>


class QDynamicElement : public QCheckBox
{
    Q_OBJECT
public:
    explicit QDynamicElement(QWidget *parent = 0);
    ~QDynamicElement();
   // static int ResID;   // Статическая переменная, счетчик номеров кнопок
   // int getID();        // Функция для возврата локального номера кнопки


public slots:

private:
    //int CbID = 0;   // Локальная переменная, номер кнопки
};

#endif // QDYNAMICELEMENT_H
