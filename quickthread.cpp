#include "quickthread.h"

QuickThread::QuickThread()
{
    speed = 50;
}


QuickThread::~QuickThread()
{
    delete [] heights;
}

void QuickThread::setAttr(int number, int *heights)
{

    this->number = number;
    this->heights = heights;
}

void QuickThread::setSpeed(int speed)
{
    this->speed = speed;
}

void QuickThread::run()
{
    quickSort(0, number - 1);

    emit sortFinish(1);
}

void QuickThread::quickSort(int left, int right)
{
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

    quickSort(left, k - 1);
    quickSort(k + 1, right);
}
