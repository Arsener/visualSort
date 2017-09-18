#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class BubbleThread : public QThread
{
    Q_OBJECT

public:
    BubbleThread();
    ~BubbleThread();
    void setSpeed(int speed);
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

#endif // MYTHREAD_H
