#ifndef QUICKTHREAD_H
#define QUICKTHREAD_H

#include <QThread>

class QuickThread : public QThread
{
    Q_OBJECT

public:
    QuickThread();
    ~QuickThread();
    void setAttr(int number, int *heights, int speed);
    void setSpeed(int speed);
    void quickSort(int left, int right);

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

#endif // QUICKTHREAD_H
