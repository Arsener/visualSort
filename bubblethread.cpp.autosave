#include "bubblethread.h"

BubbleThread::BubbleThread()
{

}


BubbleThread::~BubbleThread()
{
    delete [] heights;
}

//设置属性值
void BubbleThread::setAttr(int number, int *heights, int speed)
{
    this->number = number;
    this->heights = heights;
    this->speed = speed;
}

//设置速度
void BubbleThread::setSpeed(int speed)
{
    this->speed = speed;
}

void BubbleThread::run()
{
    //冒泡排序具体实现
    for(int i = number - 1; i > 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            //相邻两元素逆序则交换
            if(heights[j] > heights[j + 1])
            {
                int tmp = heights[j];
                heights[j] = heights[j + 1];
                heights[j + 1] = tmp;

                //一次交换之后就发送信号，通知主线程更新界面
                emit returnHeights(j, j+1, heights);
                //小憩一下，此段时间让主线程更新界面
                msleep(speed);
            }
        }
    }

    //排序结束，发送结束的信号
    emit sortFinish(0);
}
