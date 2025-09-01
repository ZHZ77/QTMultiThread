#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void working(int num);

signals:
    void sendArray(QVector<int> list);

};


class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void working(QVector<int> list);


signals:
    void finish(QVector<int> num);

};


class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void working(QVector<int> list);

private:
    void quickSort(QVector<int> &s, int l, int r);
signals:
    void finish(QVector<int> list);

};



#endif // MYTHREAD_H
