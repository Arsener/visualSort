#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    ui->numberLineEdit->setValidator(new QIntValidator(1, 999999999, this));

    //设置滑动条控件的最小值
    ui->horizontalSlider->setMinimum(1);
    //设置滑动条控件的最大值
    ui->horizontalSlider->setMaximum(100);
    //设置滑动条控件的值
    ui->horizontalSlider->setValue(50);
    bubbleThread = new BubbleThread();
    quickThread = new QuickThread();
    heapThread = new HeapThread();
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(randomHeights()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteColumns()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));

    connect(ui->bubbleButton, SIGNAL(clicked(bool)), this, SLOT(bubbleSort()));
    connect(bubbleThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(bubbleThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));

    connect(ui->quickButton, SIGNAL(clicked(bool)), this, SLOT(quickSort()));
    connect(quickThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(quickThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));

    connect(ui->heapButton, SIGNAL(clicked(bool)), this, SLOT(heapSort()));
    connect(heapThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(heapThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] labels;
    delete [] heights;
    delete bubbleThread;
}

void MainWindow::randomHeights()
{
    if(ui->numberLineEdit->text().toInt() > 300)
    {
        QMessageBox::warning(this, "Error!", "The number can't be larger than 300!");
        return;
    }

    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    sorted = false;
    deleteColumns();
    number = ui->numberLineEdit->text().toInt();
    heights = new int[number];
    int dif = 300 / number;
    heights[0] = dif;

    for(int i = 1; i < number; i++)
    {
        heights[i] = heights[i - 1] + dif;
    }

    for(int j = 0; j < number; j++)
    {
       int r = j + qrand() % (number - j);
       int temp = heights[j];
       heights[j] = heights[r];
       heights[r] = temp;
    }

    labels = new QLabel[number];
    for(int i = 0; i < number; i++)
    {
        labels[i].setFixedWidth(HLAYOUTWIDTH/number);
        labels[i].setFixedHeight(heights[i]);
        labels[i].setStyleSheet("background-color:grey");
        ui->hLayout->addWidget(&labels[i], 0, Qt::AlignBottom);
    }
}

void MainWindow::sortColumns(int a, int b, int *newHeights)
{
    labels[a].setFixedHeight(newHeights[a]);
    labels[b].setFixedHeight(newHeights[b]);
}

void MainWindow::deleteColumns()
{
    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    for(int i = 0; i < number; i++)
    {
        ui->hLayout->removeWidget(&labels[i]);
        labels[i].deleteLater();
    }

    number = 0;
}

void MainWindow::bubbleSort()
{
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    bubbleSorting = true;
    bubbleThread->setAttr(number, heights);
    bubbleThread->start();
}

void MainWindow::quickSort()
{
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    quickSorting = true;
    quickThread->setAttr(number, heights);
    quickThread->start();
}

void MainWindow::heapSort()
{
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    heapSorting = true;
    heapThread->setAttr(number, heights);
    heapThread->start();
}

void MainWindow::showFinish(int sortType)
{
    for(int i = 0; i < number; i++)
    {
        labels[i].setStyleSheet("background-color:red");
        QEventLoop eventloop;
        QTimer::singleShot(10, &eventloop, SLOT(quit()));
        eventloop.exec();
    }

    switch(sortType)
    {
    case 0:
        bubbleThread->quit();
        bubbleThread->wait();
        bubbleSorting = false;
        break;
    case 1:
        quickThread->quit();
        quickThread->wait();
        quickSorting = false;
        break;
    case 2:
        heapThread->quit();
        heapThread->wait();
        heapSorting = false;
        break;
    }
    sorted = true;
}

void MainWindow::setSpeed(int speed)
{
    if(bubbleSorting)
        bubbleThread->setSpeed(speed);
    else if(quickSorting)
        quickThread->setSpeed(speed);
    else if(heapSorting)
        heapThread->setSpeed(speed);
}
