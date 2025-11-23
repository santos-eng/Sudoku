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
    // Center Allignment no text cursor
    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    if (!index.isValid() || role != Qt::DisplayRole) // return empty QVariant if the role is not display related;
        return {};

    int value = board[index.row()][index.column()];
    return value == 0 ? QVariant() : QVariant(value); // display nothing for 0 only show 1-9
}

// Modifying per cell
bool SudokuFrame::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole) // return empty QVariant if the role is not editing the cell;
        return false;
    if (value.toInt() < 0 || value.toInt() > 9)
        return false;

    board[index.row()][index.column()] = value.toInt();
    emit dataChanged(index,index); // signal that change has occured.
    return true;
}

// What is allowed in each cell
Qt::ItemFlags SudokuFrame::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}
