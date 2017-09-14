#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bubblethread.h"
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
    void addColumns();
    void sortColumns(int* heights);
    void bubbleSort();
    void randomHeights();
    void deleteColumns();
    void showFinish();
    void setSpeed(int speed);

private:
    Ui::MainWindow *ui;
    int number = 0;
    int *heights;
    bool sorting = false;
    QLabel *labels;
    BubbleThread *bubbleThread;
};

#endif // MAINWINDOW_H
