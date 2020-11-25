#include "dialog.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include "form.h"
#include "mainw.h"
#include "settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainW f;
    f.show();

    return a.exec();
}
