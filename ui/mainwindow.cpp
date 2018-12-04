#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <thread>
#pragma execution_character_set("utf-8")

std::string Path;
std::string Port;
std::string execString;
//std::string location=".\\SimpleHttpServer.exe";
std::string location="E:\\document\\computer\\clone\\hust-report\\todo\\network\\SimpleHttpServer\\SimpleHttpServer\\Debug/SimpleHttpServer.exe";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_clicked()
{
    Port = this->ui->lineEdit_Port->text().toStdString();
    Path = this->ui->lineEdit_Path->text().toStdString();
    execString=location+" "+Path+" "+Port;
    const char* tmp=execString.c_str();
    system(tmp);


}
