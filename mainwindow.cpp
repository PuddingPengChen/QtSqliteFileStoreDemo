#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btnCreate_clicked()
{
    CreateConnection();
}
bool MainWindow::CreateConnection()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("image.db");
    //打开数据库
    if(!database.open())
    {
        qDebug()<<"create database failed!";
        //        qFatal("failed to connect.") ;
        return false;
    }
    else
    {
        qDebug()<<"create successful!";
        return true;
    }
}

void MainWindow::on_pushButton_clicked()
{

    QStringList tableList = database.tables();
    QSqlQuery query(database);
    if(!tableList.contains("files"))
    {
        QString createTable = "create table files (id integer primary key,"
                "filename varchar(128) unique, filecontent blob)";
        if(!query.exec(createTable))
        {
            qDebug()<<"Execut table error!";
        }
    }

}

void MainWindow::on_btnStore_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),".","Image(*.jpg *.png *.jpeg)");
    QSqlQuery query(database);
    QFile File(filename);
    if(File.open(QIODevice::ReadOnly))
    {
        QByteArray tdata = File.readAll();
        QByteArray data = qCompress(tdata,9);
        query.prepare("INSERT INTO files (id,filename,filecontent)"
                      "VALUES(NULL,:filename,:filecontent)");
        query.bindValue(":filename", filename);
        query.bindValue(":filecontent", data);
        if(!query.exec())
        {
            qDebug()<<"Store database error";

        }
        else
        {
            qDebug()<<"Store database sucessful";
        }

    }
}
//导出文件
void MainWindow::on_btnExport_clicked()
{
    QSqlQuery query(database);
    query.prepare("select filecontent from files");
    query.exec();
    query.next();
    QByteArray tdata = query.value(0).toByteArray();
    QByteArray data = qUncompress(tdata);
    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),".","Image(*.jpg *.png *.jpeg)");
    QFile File(filename);
    if(File.open(QIODevice::WriteOnly))
    {
        File.write(data);
        File.close();
    }
    else
    {
        qDebug()<<"export sussful!";
    }
}
