#ifndef GRID_H
#define GRID_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class grid;
}
QT_END_NAMESPACE

class grid : public QMainWindow
{
    Q_OBJECT

public:
    grid(QWidget *parent = nullptr);
    ~grid();

private slots:
    void on_loadPuzzleBtn_clicked();

    void on_solveBtn_clicked();

    void on_testBoardCheck_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::grid *ui;
};
#endif // GRID_H
