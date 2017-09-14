#include "bubblethread.h"

BubbleThread::BubbleThread()
{
    speed = 50;
}


BubbleThread::~BubbleThread()
{
    delete [] heights;
}

void BubbleThread::setAttr(int number, int *heights)
{

    this->number = number;
    this->heights = heights;
}

void BubbleThread::setSpeed(int speed)
{
    this->speed = speed;
}

void BubbleThread::run()
{
    for(int i = number - 1; i > 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            if(heights[j] > heights[j + 1])
            {
                int tmp = heights[j];
                heights[j] = heights[j + 1];
                heights[j + 1] = tmp;
            }

            emit returnHeights(heights);
            msleep(speed);
        }
    }

    emit sortFinish();
}
