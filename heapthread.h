#ifndef HEAPTHREAD_H
#define HEAPTHREAD_H

#include <QThread>

class HeapThread : public QThread
{
    Q_OBJECT

public:
    HeapThread();
    ~HeapThread();
    void setAttr(int number, int *heights);
    void setSpeed(int speed);
    void heapAdjust(int parent, int length);
    void heapSort();

signals:
    void returnHeights(int, int, int*);
    void sortFinish(int);

protected:
    void run();

private:
    int speed;
    int number;
    int *heights;
};

#endif // HEAPTHREAD_H
