#ifndef QUICKSWITCHMODE_H
#define QUICKSWITCHMODE_H

#include <QDialog>

namespace Ui {
class quickSwitchMode;
}

class quickSwitchMode : public QDialog
{
    Q_OBJECT

public:
    explicit quickSwitchMode(QWidget *parent = nullptr);
    ~quickSwitchMode();

private:
    Ui::quickSwitchMode *ui;
};

#endif // QUICKSWITCHMODE_H
