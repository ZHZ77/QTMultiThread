#include "mythread.h"
#include <QVector>
#include <QElapsedTimer>
#include <QDebug>


Generate::Generate(QObject *parent) : QThread{parent}
{


}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug() << "生成随机数的线程的线程地址：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for (int i =0; i < m_num; ++i)
    {
        list.push_back(qrand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug() << "生成" << m_num << "个随机数共用时" << milsec << "ms";
    emit sendArray(list);
}
