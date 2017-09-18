#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "heapthread.h"
#include "bubblethread.h"
#include "quickthread.h"
#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const int HLAYOUTWIDTH = 500;
    const int HLAYOUTHEIGHT = 300;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void heapSort();
    void quickSort();
    void bubbleSort();
    void randomHeights();
    void deleteColumns();
    void setSpeed(int speed);
    void showFinish(int sortType);
    void sortColumns(int a, int b, int* heights);

private:
    Ui::MainWindow *ui;
    int number = 0;
    int speed = 50;
    int *heights;
    bool sorted = false;
    bool heapSorting = false;
    bool quickSorting = false;
    bool bubbleSorting = false;
    QLabel *labels;
    HeapThread *heapThread;
    QuickThread *quickThread;
    BubbleThread *bubbleThread;
};

#endif // MAINWINDOW_H
