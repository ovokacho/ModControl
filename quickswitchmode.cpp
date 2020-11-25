#include "quickswitchmode.h"
#include "ui_quickswitchmode.h"

quickSwitchMode::quickSwitchMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quickSwitchMode)
{
    ui->setupUi(this);
}

quickSwitchMode::~quickSwitchMode()
{
    delete ui;
}
