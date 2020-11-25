#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QComboBox>
#include <qdynamicelement.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    void fillToolListMain();

private:
   // Ui::MainWindow *ui;
    QString SettingsOfFile;
    void loadini(QString tool);


private slots:

    void toolcomboselected();
    void on_pushButton_clicked();
    void on_pushButtonRefresh_clicked();
};

#endif // MAINWINDOW_H
