#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCreate_clicked();

    void on_pushButton_clicked();

    void on_btnStore_clicked();

    void on_btnExport_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;

    //function
    bool CreateConnection();
};

#endif // MAINWINDOW_H
