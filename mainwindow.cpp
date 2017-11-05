#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //限制QLineEdit输入的只能是数字
    ui->numberLineEdit->setValidator(new QIntValidator(1, 999999999, this));

    //设置滑动条控件的最小值
    ui->horizontalSlider->setMinimum(1);
    //设置滑动条控件的最大值
    ui->horizontalSlider->setMaximum(100);
    //设置滑动条控件初始的值
    ui->horizontalSlider->setValue(50);

    heapThread = new HeapThread();
    quickThread = new QuickThread();
    bubbleThread = new BubbleThread();

    //设置不同的信号槽
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(randomHeights()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteColumns()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));

    connect(ui->heapButton, SIGNAL(clicked(bool)), this, SLOT(heapSort()));
    connect(heapThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(heapThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));

    connect(ui->quickButton, SIGNAL(clicked(bool)), this, SLOT(quickSort()));
    connect(quickThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(quickThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));

    connect(ui->bubbleButton, SIGNAL(clicked(bool)), this, SLOT(bubbleSort()));
    connect(bubbleThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(bubbleThread, SIGNAL(returnHeights(int, int, int*)), this, SLOT(sortColumns(int, int, int*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] labels;
    delete [] heights;
    delete bubbleThread;
}

//添加若干高度不同的“柱子”
void MainWindow::randomHeights()
{
    //处理异常输入，最大输入值为300，最小为1
    if(ui->numberLineEdit->text() == "")
    {
        QMessageBox::warning(this, "Error!", "Please input the number!");
        return;
    }

    if(ui->numberLineEdit->text().toInt() > 300)
    {
        QMessageBox::warning(this, "Error!", "The number can't be larger than 300!");
        return;
    }

    if(ui->numberLineEdit->text().toInt() == 0)
    {
        QMessageBox::warning(this, "Error!", "The number must be larger than 0!");
        return;
    }

    //排序期间不能添加
    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    sorted = false;
    //把之前的“柱子”全部删除
    deleteColumns();
    number = ui->numberLineEdit->text().toInt();

    heights = new int[number];
    //设置排序后高度差均等
    int dif = 300 / number;
    heights[0] = dif;

    for(int i = 1; i < number; i++)
    {
        heights[i] = heights[i - 1] + dif;
    }

    //打乱有序数组的顺序
    for(int j = 0; j < number; j++)
    {
       int r = j + qrand() % (number - j);
       int temp = heights[j];
       heights[j] = heights[r];
       heights[r] = temp;
    }

    //设置“柱子”的样式并依次加入到布局中
    labels = new QLabel[number];
    for(int i = 0; i < number; i++)
    {
        labels[i].setFixedWidth(HLAYOUTWIDTH/number);
        labels[i].setFixedHeight(heights[i]);
        labels[i].setStyleSheet("background-color:grey");
        ui->hLayout->addWidget(&labels[i], 0, Qt::AlignBottom);
    }
}

//更新一次交换结果的函数，接受线程发来的信号
void MainWindow::sortColumns(int a, int b, int *newHeights)
{
    labels[a].setFixedHeight(newHeights[a]);
    labels[b].setFixedHeight(newHeights[b]);
}

//删除layout中的标签
void MainWindow::deleteColumns()
{
    //排序期间不能删除
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

//开启冒泡排序的线程
void MainWindow::bubbleSort()
{
    //如果当前是排序结束的状态需要重新添加
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    //排序期间不能开启排序
    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    bubbleSorting = true;
    bubbleThread->setAttr(number, heights, speed);
    bubbleThread->start();
}

//开启快速排序的线程
void MainWindow::quickSort()
{
    //如果当前是排序结束的状态需要重新添加
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    //排序期间不能开启排序
    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    quickSorting = true;
    quickThread->setAttr(number, heights, speed);
    quickThread->start();
}

//开启堆排序的线程
void MainWindow::heapSort()
{
    //如果当前是排序结束的状态需要重新添加
    if(sorted)
    {
        QMessageBox::warning(this, "Error!", "Please re-add the columns!");
        return;
    }

    //排序期间不能开启排序
    if(bubbleSorting || quickSorting || heapSorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    heapSorting = true;
    heapThread->setAttr(number, heights, speed);
    heapThread->start();
}

//展示排序结果
void MainWindow::showFinish(int sortType)
{
    //动画效果
    for(int i = 0; i < number; i++)
    {
        labels[i].setStyleSheet("background-color:red");
        QEventLoop eventloop;
        QTimer::singleShot(10, &eventloop, SLOT(quit()));
        eventloop.exec();
    }

    //休眠当前线程
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

//设置排序速度
void MainWindow::setSpeed(int speed)
{
    if(bubbleSorting)
        bubbleThread->setSpeed(speed);
    else if(quickSorting)
        quickThread->setSpeed(speed);
    else if(heapSorting)
        heapThread->setSpeed(speed);

    this->speed = speed;
}
