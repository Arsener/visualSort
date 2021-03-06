#include "heapthread.h"

HeapThread::HeapThread()
{

}


HeapThread::~HeapThread()
{
    delete [] heights;
}

void HeapThread::setAttr(int number, int *heights, int speed)
{
    this->number = number;
    this->heights = heights;
    this->speed = speed;
}

void HeapThread::setSpeed(int speed)
{
    this->speed = speed;
}

void HeapThread::run()
{
    //调用堆排序函数
    heapSort();

    //排序结束，发送结束的信号
    emit sortFinish(2);
}

//调整堆结构
void HeapThread::heapAdjust(int parent, int length)
{
    //先获得左孩子
    int child = 2 * parent + 1;

     while (child < length) {
         //如果有右孩子结点，并且右孩子结点的值大于左孩子结点，则选取右孩子结点
        if (child + 1 < length && heights[child] < heights[child + 1]) {
             child++;
         }

         //如果父结点的值已经大于孩子结点的值，则直接结束
        if (heights[parent] >= heights[child])
             break;

        //tmp保存当前父节点
        int tmp = heights[parent];
         //把孩子结点的值赋给父结点
        heights[parent] = heights[child];
        heights[child] = tmp;

        //发生了一次交换，发送信号
        emit returnHeights(parent, child, heights);

        msleep(speed);

        //选取孩子结点的左孩子结点,继续向下筛选
        parent = child;
        child = 2 * child + 1;
     }

}

void HeapThread::heapSort()
{
    //将乱序的数组化为大顶堆
    for(int i = number / 2; i >= 0; i--)
    {
        heapAdjust(i, number);
    }

    for(int i = number - 1; i >= 0; i--)
    {
        //将堆顶元素放至最后
        int tmp = heights[i];
        heights[i] = heights[0];
        heights[0] = tmp;

        emit returnHeights(0, i, heights);
        msleep(speed);

        //调整堆
        heapAdjust(0, i);
    }
}
