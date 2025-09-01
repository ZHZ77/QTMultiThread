#include "mythread.h"
#include <QVector>
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>

Generate::Generate(QObject *parent) : QObject{parent}
{


}


void Generate::working(int num)
{
    qDebug() << "生成随机数的线程的线程地址：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for (int i =0; i < num; ++i)
    {
        list.push_back(qrand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug() << "生成" << num << "个随机数共用时" << milsec << "ms";
    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent)
{

}


void BubbleSort::working(QVector<int> list)
{
    qDebug() << "冒泡排序线程的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    for (int i =0; i<list.size(); ++i)
    {
        for(int j =0; j<list.size()-i-1; ++j)
        {
            int temp;
            if(list[j]>list[j+1])
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qDebug() << "冒泡排序共用时:" << milsec << "ms";
    emit finish(list);
}

QuickSort::QuickSort(QObject *parent)
{

}



void QuickSort::working(QVector<int> list)
{
    qDebug() << "快速排序线程的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(list, 0, list.size()-1);

    int milsec = time.elapsed();
    qDebug() << "快速排序共用时:" << milsec << "ms";
    emit finish(list);

}




void QuickSort::quickSort(QVector<int> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        int x = s[l]; // 选取基准值（pivot），这里取最左边的元素

        while (i < j)
        {
            // 从右向左找第一个小于基准值的元素
            while (i < j && s[j] >= x)
            {
                j--;
            }
            if (i < j)
            {
                // 将右侧找到的小于基准值的元素放到左侧坑中
                s[i++] = s[j];
            }

            // 从左向右找第一个大于等于基准值的元素
            while (i < j && s[i] < x)
            {
                i++; // 修正：原代码写成了 i--，应为 i++
            }
            if (i < j)
            {
                // 将左侧找到的大于等于基准值的元素放到右侧坑中
                s[j--] = s[i];
            }
        }

        // 最终将基准值放入中间位置
        s[i] = x;

        // 递归处理左右子区间
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}












