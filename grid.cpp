#include "grid.h"
#include "./ui_grid.h"
#include "sudokuFrame.h"

grid::grid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grid)
{
    ui->setupUi(this); // contains pointers to the widgets

    auto* model = new SudokuFrame(this); // create the frame, with grid as the parent
    ui->tableView->setModel(model); // table view uses the SudokuFrame as its data sources

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Fill the widget
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();
}

grid::~grid()
{
    delete ui;
}
