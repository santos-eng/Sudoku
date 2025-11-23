#ifndef GRID_H
#define GRID_H

#include <QMainWindow>

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

private:
    Ui::grid *ui;
};
#endif // GRID_H
