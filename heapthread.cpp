#include "heapthread.h"

HeapThread::HeapThread()
{
    speed = 50;
}


HeapThread::~HeapThread()
{
    delete [] heights;
}

void HeapThread::setAttr(int number, int *heights)
{

    this->number = number;
    this->heights = heights;
}

void HeapThread::setSpeed(int speed)
{
    this->speed = speed;
}

void HeapThread::run()
{
    heapSort();

    emit sortFinish(2);
}

void HeapThread::heapAdjust(int parent, int length)
{
    int child = 2 * parent + 1; // 先获得左孩子

     while (child < length) {
         // 如果有右孩子结点，并且右孩子结点的值大于左孩子结点，则选取右孩子结点
        if (child + 1 < length && heights[child] < heights[child + 1]) {
             child++;
         }

         // 如果父结点的值已经大于孩子结点的值，则直接结束
        if (heights[parent] >= heights[child])
             break;

        int tmp = heights[parent]; // tmp保存当前父节点
         // 把孩子结点的值赋给父结点
        heights[parent] = heights[child];
        heights[child] = tmp;

        emit returnHeights(parent, child, heights);

        msleep(speed);

         // 选取孩子结点的左孩子结点,继续向下筛选
        parent = child;
        child = 2 * child + 1;
     }

}

void HeapThread::heapSort()
{
    for(int i = number / 2; i >= 0; i--)
    {
        heapAdjust(i, number);
    }

    for(int i = number - 1; i >= 0; i--)
    {
        int tmp = heights[i];
        heights[i] = heights[0];
        heights[0] = tmp;

        emit returnHeights(0, i, heights);
        msleep(speed);

        heapAdjust(0, i);
    }
}
