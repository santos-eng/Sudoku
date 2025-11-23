#include "grid.h"
#include "./ui_grid.h"

grid::grid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grid)
{
    ui->setupUi(this);
}

grid::~grid()
{
    delete ui;
}
