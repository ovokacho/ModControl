#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QStandardItemModel>
#include <QComboBox>
#include <qdynamicelement.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    Ui::Form *ui;
    void fillToolListMain();

private:
    QString SettingsOfFile;
    void loadini(QString tool);


private slots:
    //void on_addButton_clicked();    // СЛОТ-обработчик нажатия кнопки добавления
    //void on_deleteButton_clicked(); // СЛОТ-обработчик нажатия кнопки удаления
    //void slotGetNumber();           // СЛОТ для получения номера нажатой динамической кнопки
    void addCheckBoxAtt(QString name);
    void addCheckBoxFv(QString name);
    void addCheckBoxElse(QString name);
    void toolcomboselected();
    void on_pushButton_clicked();
    void on_pushButtonRefresh_clicked();
};



#endif // FORM_H
