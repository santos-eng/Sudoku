#ifndef SUDOKUFRAME_H
#define SUDOKUFRAME_H

#include <QAbstractTableModel>
#include <QBrush>
#include <QFont>
#include <QAbstractItemView>
#include <array>
#include "validator.h"

class SudokuFrame : public QAbstractTableModel
{
    Q_OBJECT
    std::array<std::array<int,9>,9> board{};
    std::array<std::array<bool,9>,9> fixed{};
    QAbstractItemView* view = nullptr;
    Validator::State state;
    std::array<bool,9> invalRow{}, invalCol{}, invalBox{}; // for fast lookup during colouring
    bool cellInvalid(const int r, const int c) const;
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

    void setView(QAbstractItemView* view);

    void clearBoard();
    void loadFromInitConditions(const QString& initialBoard);
    void autoSolve();
};
#endif // SUDOKUFRAME_H
