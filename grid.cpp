#include "grid.h"
#include "./ui_grid.h"
#include "sudokuFrame.h"
#include <chrono>

grid::grid(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grid)
{
    ui->setupUi(this); // contains pointers to the widgets
    this->setStyleSheet(R"(
        QPushButton {
            background-color: #2f2f2f;
            color: #eee;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 13px;
            border: 1px solid #444;
        }

        QPushButton:hover {
            background-color: #3c3c3c;
        }

        QPushButton:pressed {
            background-color: #222;
        }
        QRadioButton {
            spacing: 6px;
            font-size: 13px;
        }

        QCheckBox {
            spacing: 6px;
            font-size: 13px;
        }

        QLabel {
            font-size: 13px;
            font-weight: bold;
        }
    )");
    this->setWindowTitle("Sudoku");

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
        model->loadTestBoard(initialBoard);
    } else {
        int minClues;
        if (difficulty == "easy")
            minClues = 45;
        else if (difficulty == "medium")
            minClues = 35;
        else
            minClues = 25;
        std::chrono::duration<double, std::milli> genTime = model->generateRandom(minClues);
        ui->genTimeLbl->setText(QString::number(genTime.count()));
    }
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

void grid::on_testBoardCheck_checkStateChanged(const Qt::CheckState &arg)
{
    if (arg == Qt::CheckState::Checked) {
        ui->loadPuzzleBtn->setText("Load Test Sudoku");
    } else {
        ui->loadPuzzleBtn->setText("Generate Random Sudoku");
    }
}
