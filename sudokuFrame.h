#ifndef SUDOKUFRAME_H
#define SUDOKUFRAME_H

#include <QAbstractTableModel>

class SudokuFrame : public QAbstractTableModel
{
    Q_OBJECT
    int board[9][9];
public:
    explicit SudokuFrame(QObject *parent = nullptr);

    // Defining table size
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Cell appearance
    QVariant data(const QModelIndex &index, int role) const override;

    // Modifying per cell
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    // What is allowed in each cell
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // SUDOKUFRAME_H
