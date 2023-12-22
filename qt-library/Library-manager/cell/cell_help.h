#ifndef CELL_HELP_H
#define CELL_HELP_H

#include <QWidget>

namespace Ui {
class Cell_help;
}

class Cell_help : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_help(QWidget *parent = nullptr);
    ~Cell_help();

private:
    Ui::Cell_help *ui;
};

#endif // CELL_HELP_H
