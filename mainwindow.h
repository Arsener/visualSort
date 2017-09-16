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
    void sortColumns(int a, int b, int* heights);
    void quickSort();
    void bubbleSort();
    void heapSort();
    void randomHeights();
    void deleteColumns();
    void showFinish(int sortType);
    void setSpeed(int speed);

private:
    Ui::MainWindow *ui;
    int number = 0;
    int speed = 50;
    int *heights;
    bool bubbleSorting = false;
    bool quickSorting = false;
    bool heapSorting = false;
    bool sorted = false;
    QLabel *labels;
    BubbleThread *bubbleThread;
    QuickThread *quickThread;
    HeapThread *heapThread;
};

#endif // MAINWINDOW_H
