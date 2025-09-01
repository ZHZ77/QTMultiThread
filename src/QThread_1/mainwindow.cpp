#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 1.创建子线程对象
    Generate* gen = new Generate;

    connect(this, &MainWindow::starting, gen, &Generate::recvNum);

    // 2.启动子线程
    connect(ui->start,&QPushButton::clicked,this,[=](){
            emit starting(100000);
            gen->start();
    });

    // 3.接受子线程的发送操作
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list){
            for(int i=0;i<list.size();++i){
                ui->randList->addItem(QString::number(list.at(i)));
            }
            });


}

MainWindow::~MainWindow()
{
    delete ui;
}
