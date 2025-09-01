#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
public slots:
    void recvNum(int num);

protected:
    void run() override;

signals:
    void sendArray(QVector<int> num);
private:
    int m_num;
};

#endif // MYTHREAD_H
