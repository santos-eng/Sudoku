#include "sudokuFrame.h"

SudokuFrame::SudokuFrame(QObject *parent)
    : QAbstractTableModel{parent}
{}


int SudokuFrame::rowCount(const QModelIndex &parent) const {
    return 9;
}

int SudokuFrame::columnCount(const QModelIndex &parent) const {
    return 9;
}

// Cell appearance
QVariant SudokuFrame::data(const QModelIndex &index, int role) const {
    int r = index.row(), c = index.column();
    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    if (role == Qt::BackgroundRole) {
        if (fixed[r][c])
            return QBrush(QColor(23, 197, 255));
        else
            return QBrush(QColor(255, 255, 255));
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
    emit dataChanged(index,index); // signal that change has occured.
    return true;
}

// What is allowed in each cell
Qt::ItemFlags SudokuFrame::flags(const QModelIndex &index) const {
    if (fixed[index.row()][index.column()])
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
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

    emit dataChanged(index(0,0),index(8,8)); // Indicate that the whole board needs refreshing
}





