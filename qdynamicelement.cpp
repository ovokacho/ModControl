#include "qdynamicelement.h"

QDynamicElement::QDynamicElement(QWidget *parent) :
    QCheckBox(parent)
{
    //ResID++;            // Увеличение счетчика на единицу
    //CbID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                        // * дальнейшая работа с кнопок
                       //  * */

}

QDynamicElement::~QDynamicElement()
{

}

/* Метод для возврата значения номера кнопки
 * */
//int QDynamicElement::getID()
//{
//    //return CbID;
//}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
//int QDynamicElement::ResID = 0;
