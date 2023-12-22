#include "cell_help.h"
#include "ui_cell_help.h"

Cell_help::Cell_help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_help)
{
    ui->setupUi(this);
    ui->textEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

Cell_help::~Cell_help()
{
    delete ui;
}
