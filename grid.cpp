#include "grid.h"
#include "./ui_grid.h"
#include "sudokuFrame.h"
#include <chrono>

// To do, make it so that the highlighted cell is a different colour, grey when selected or dark blue if a set cell
// Insert the dark colum borders

// Then recognise issues with red highlight

// Recognise Success


grid::grid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grid)
{
    ui->setupUi(this); // contains pointers to the widgets

    ui->easyRadio->setChecked(true);

    auto* model = new SudokuFrame(this); // create the frame, with grid as the parent
    ui->tableView->setModel(model); // table view uses the SudokuFrame as its data sources
    model->setView(ui->tableView); // Model has pointer to view it is used by

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Fill the widget
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();

    QFont font = ui->tableView->font();
    font.setPointSize(24);
    ui->tableView->setFont(font);

    // Ensure that navigating the grid with the mouse or arrow keys calls shading updates
    // connect(Qobj* sender, func1 signal, QObj* receiver, func2 slot)
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this,
            [this](const QModelIndex &, const QModelIndex &) { // currentChanged has the addresses of current and previous selections
                ui->tableView->viewport()->update();
            }
    );
}

grid::~grid()
{
    delete ui;
}

void grid::on_loadPuzzleBtn_clicked()
{
    SudokuFrame* model = qobject_cast<SudokuFrame*>(ui->tableView->model());

    QString difficulty;
    if (ui->easyRadio->isChecked())
        difficulty = "easy";
    else if (ui->mediumRadio->isChecked())
        difficulty = "medium";
    else
        difficulty = "hard";

    QString initialBoard{};
    if (ui->testBoardCheck->isChecked()) {
        QString folder = QCoreApplication::applicationDirPath() + "/testPuzzles/" + difficulty + ".txt";

        QFile file(folder);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Couldn't open puzzle file:\n" + folder);
            return;
        }
        initialBoard = file.readAll();
    }

    model->loadTestBoard(initialBoard);
}


void grid::on_solveBtn_clicked()
{
    SudokuFrame* model = qobject_cast<SudokuFrame*>(ui->tableView->model());
    std::chrono::duration<double, std::milli> solveTime = model->autoSolve();
    if (solveTime.count() < 0)
        ui->autoSolveTimeLbl->setText(QString("INVALID"));
    else
        ui->autoSolveTimeLbl->setText(QString::number(solveTime.count())); // count is number of millisecond ticks
}

