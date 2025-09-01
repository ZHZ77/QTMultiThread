#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mythread.h"
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1.创建子线程对象
    QThread* t_gen = new QThread;
    QThread* t_bubble = new QThread;
    QThread* t_quick = new QThread;
    // 2.创建任务类对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;


    // 3.将任务对象移动到子线程中
    gen->moveToThread(t_gen);
    bubble->moveToThread(t_bubble);
    quick->moveToThread(t_quick);

    connect(this, &MainWindow::starting, gen, &Generate::working);
    connect(ui->start,&QPushButton::clicked,this,[=](){
            emit starting(10000);
            t_gen->start();
    });

    connect(gen,&Generate::sendArray,bubble, &BubbleSort::working);
    connect(gen,&Generate::sendArray,quick, &QuickSort::working);

    // 4.接受子线程的发送操作
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list){
        t_bubble->start();
        t_quick->start();
        for(int i=0;i<list.size();++i){
                ui->randList->addItem(QString::number(list.at(i)));
            }
            });

    connect(bubble,&BubbleSort::finish,this,[=](QVector<int> list){
        for(int i=0;i<list.size();++i){
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });

    connect(quick,&QuickSort::finish,this,[=](QVector<int> list){
        for(int i=0;i<list.size();++i){
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });
    connect(this,&MainWindow::destroyed,this,[=](){
        t_gen->quit();
        t_gen->wait();
        t_gen->deleteLater();

        t_bubble->quit();
        t_bubble->wait();
        t_bubble->deleteLater();

        t_quick->quit();
        t_quick->wait();
        t_quick->deleteLater();

        delete gen;
        delete bubble;
        delete quick;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
