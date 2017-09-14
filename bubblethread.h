#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class BubbleThread : public QThread
{
    Q_OBJECT

public:
    BubbleThread();
    ~BubbleThread();
    void setAttr(int number, int *heights);
    void setSpeed(int speed);

signals:
    void returnHeights(int*);
    void sortFinish(int);

protected:
    void run();

private:
    int speed;
    int number;
    int *heights;
};

#endif // MYTHREAD_H
