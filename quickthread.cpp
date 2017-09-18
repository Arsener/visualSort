#include "quickthread.h"

QuickThread::QuickThread()
{

}


QuickThread::~QuickThread()
{
    delete [] heights;
}

void QuickThread::setAttr(int number, int *heights, int speed)
{
    this->number = number;
    this->heights = heights;
    this->speed = speed;
}

void QuickThread::setSpeed(int speed)
{
    this->speed = speed;
}

void QuickThread::run()
{
    //调用快速排序的函数
    quickSort(0, number - 1);

    //排序结束，发送结束的信号
    emit sortFinish(1);
}

//快速排序
void QuickThread::quickSort(int left, int right)
{
    //递归返回条件
    if(left >= right)
    {
        return;
    }

    int i = left, j = right, k = left;
    int direction = 0;
    while(i<=j)
    {
        if(direction)
        {
            if(heights[i] > heights[k])
            {
                int tmp = heights[i];
                heights[i] = heights[k];
                heights[k] = tmp;
                direction = 0;

                emit returnHeights(i,k,heights);
                msleep(speed);
                k = i;
            }
            i++;
        }
        else
        {
            if(heights[j] < heights[k])
            {
                int tmp = heights[j];
                heights[j] = heights[k];
                heights[k] = tmp;
                direction = 1;

                emit returnHeights(j,k,heights);
                msleep(speed);
                k = j;
            }
            j--;
        }

    }

    //递归调用次函数，依次排序左右两侧的数组
    quickSort(left, k - 1);
    quickSort(k + 1, right);
}
