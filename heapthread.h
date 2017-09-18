#ifndef HEAPTHREAD_H
#define HEAPTHREAD_H

#include <QThread>

class HeapThread : public QThread
{
    Q_OBJECT

public:
    HeapThread();
    ~HeapThread();
    void heapSort();
    void setSpeed(int speed);
    void heapAdjust(int parent, int length);
    void setAttr(int number, int *heights, int speed);

signals:
    void sortFinish(int);
    void returnHeights(int, int, int*);

protected:
    void run();

private:
    int speed;
    int number;
    int *heights;
};

#endif // HEAPTHREAD_H
