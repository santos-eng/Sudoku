#include "sudokuFrame.h"
#include "solver.h"

SudokuFrame::SudokuFrame(QObject *parent)
    : QAbstractTableModel{parent}
{}


int SudokuFrame::rowCount(const QModelIndex &parent) const {
    return 9;
}

int SudokuFrame::columnCount(const QModelIndex &parent) const {
    return 9;
}

bool SudokuFrame::cellInvalid(const int r, const int c) const {
    int boxId = (r/3) * 3 + (c/3);
    return invalRow[r] || invalCol[c] || invalBox[boxId];
}

// Cell appearance
QVariant SudokuFrame::data(const QModelIndex &index, int role) const {
    int r = index.row(), c = index.column();

    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    if (role == Qt::BackgroundRole) {
        // Selected Cells
        if (view && view->selectionModel()) {
            QModelIndex currSelected = view->selectionModel()->currentIndex(); // selection model is a pointer for selecting in the table
            if (currSelected == index && fixed[r][c]) {
                if (cellInvalid(r,c))
                    return QBrush(QColor(74, 1, 5)); // dark red
                if (state == Validator::State::Complete)
                    return QBrush(QColor(1, 66, 12)); // dark green
                return QBrush(QColor(2, 70, 227)); // dark blue
            }
            // Free
            if (currSelected == index) {
                if (cellInvalid(r,c))
                    return QBrush(QColor(204, 0, 24)); // medium red
                if (state == Validator::State::Complete)
                    return QBrush(QColor(3, 135, 34)); // medium green
                return QBrush(QColor(137, 140, 138)); // grey
            }
        }

        // Unselected Cells
        if (fixed[r][c]) {
            if (cellInvalid(r,c))
                return QBrush(QColor(140, 1, 18)); // red
            if (state == Validator::State::Complete)
                return QBrush(QColor(7, 94, 1)); // dark green
            return QBrush(QColor(74, 161, 255)); // light blue
        }
        if (cellInvalid(r,c))
            return QBrush(QColor(247, 99, 99)); // red
        if (state == Validator::State::Complete)
            return QBrush(QColor(117, 250, 117)); // light green
        return QBrush(QColor(255, 255, 255)); // white
    }

    if (role == Qt::ForegroundRole) {
        return QBrush(QColor(0, 0, 0));
    }

    if (role == Qt::FontRole) {
        QFont font;
        if (fixed[r][c])
            font.setBold(true);
        return font;
    }


    if (role == Qt::DisplayRole) {
        int value = board[r][c];
        return value == 0 ? QVariant() : QVariant(value); // display nothing for 0 only show 1-9
    }

    return {};
}

// Modifying per cell
bool SudokuFrame::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole) // return empty QVariant if the role is not editing the cell;
        return false;
    if (fixed[index.row()][index.column()])
        return false;
    if (value.toInt() < 0 || value.toInt() > 9)
        return false;

    board[index.row()][index.column()] = value.toInt();
    state = Validator::isValid(board,invalRow,invalCol,invalBox);

    emit dataChanged(this->index(0,0),this->index(8,8)); // signal that change has occured.
    return true;
}

// What is allowed in each cell
Qt::ItemFlags SudokuFrame::flags(const QModelIndex &index) const {
    if (fixed[index.row()][index.column()])
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void SudokuFrame::setView(QAbstractItemView* view) {
    this->view = view;
}

void SudokuFrame::clearBoard() {
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++) {
            board[r][c] = 0;
            fixed[r][c] = false;
        }

}

void SudokuFrame::loadFromInitConditions(const QString& initialBoard) {
    clearBoard();

    int row = 0, col = 0;
    for (QChar c : initialBoard) {
        if (!c.isDigit())
            continue;
        int value = c.digitValue();

        board[row][col] = value;
        fixed[row][col] = value != 0; // non-zero will fix cell.

        col++;
        if (col == 9) {
            col = 0;
            row++;
            if (row == 9)
                break;
        }
    }

    emit dataChanged(this->index(0,0),this->index(8,8)); // Indicate that the whole board needs refreshing
}

void SudokuFrame::autoSolve() {
    Solver::backtrackSolve(board);
    emit dataChanged(this->index(0,0),this->index(8,8));
}





