#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QRunnable>

class Generate : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void run() override;

public slots:
    void recvNum(int num);

signals:
    void sendArray(QVector<int> num);
private:
    int m_num;
};


class BubbleSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
public slots:
    void recvArray(QVector<int> list);

public:
    void run() override;

signals:
    void finish(QVector<int> num);
private:
    QVector<int> m_list;
};


class QuickSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
public slots:
    void recvArray(QVector<int> list);

public:
    void run() override;
private:
    void quickSort(QVector<int> &s, int l, int r);
signals:
    void finish(QVector<int> list);
private:
    QVector<int> m_list;
};



#endif // MYTHREAD_H
