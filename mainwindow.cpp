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
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(randomHeights()));
    connect(ui->bubbleButton, SIGNAL(clicked(bool)), this, SLOT(bubbleSort()));
    connect(bubbleThread, SIGNAL(sortFinish(int)), this, SLOT(showFinish(int)));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteColumns()));
    connect(bubbleThread, SIGNAL(returnHeights(int*)), this, SLOT(sortColumns(int*)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
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

    if(sorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    deleteColumns();
    number = ui->numberLineEdit->text().toInt();
    int already[HLAYOUTHEIGHT] = {0};
    heights = new int[number];

    for(int i = 0; i < number; i++)
    {
        int height = qrand()%HLAYOUTHEIGHT;
        while(already[height])
        {
            height = qrand()%HLAYOUTHEIGHT;
        }
        heights[i] = height;
        already[height] = 1;
    }

    addColumns();
}

void MainWindow::addColumns()
{
    labels = new QLabel[number];
    for(int i = 0; i < number; i++)
    {
        labels[i].setFixedWidth(HLAYOUTWIDTH/number);
        labels[i].setFixedHeight(heights[i]);
        labels[i].setStyleSheet("background-color:grey");
        ui->hLayout->addWidget(&labels[i], 0, Qt::AlignBottom);
    }
}

void MainWindow::sortColumns(int *newHeights)
{
    for(int i = 0; i < number; i++)
    {
        labels[i].setFixedHeight(newHeights[i]);
    }
}

void MainWindow::deleteColumns()
{
    if(sorting)
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
    if(sorting)
    {
        QMessageBox::warning(this, "Error!", "I'm sorting!");
        return;
    }

    sorting = true;
    bubbleThread->setAttr(number, heights);
    bubbleThread->start();
}

void MainWindow::showFinish(int sortType)
{
    for(int i = 0; i < number; i++)
    {
        labels[i].setStyleSheet("background-color:red");
        QEventLoop eventloop;
        QTimer::singleShot(50, &eventloop, SLOT(quit()));
        eventloop.exec();
        labels[i].setStyleSheet("background-color:grey");
    }

    sorting = false;

    switch(sortType)
    {
    case 0:
        bubbleThread->quit();
        bubbleThread->wait();
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

void MainWindow::setSpeed(int speed)
{
    bubbleThread->setSpeed(speed);
}
