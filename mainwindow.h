#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include "readdatawidget.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void connectDB(QString ip, int port, QString database, QString username, QString password);
    QSqlDatabase db;
    ReadDataWidget readDataWidget;
private slots:
    void on_pushButton_type_kongyu_clicked();
    void on_action_about_triggered();
    void on_pushButton_connect_clicked();
    void on_pushButton_mark_clicked();
    void on_pushButton_kongyu_clicked();
    void on_pushButton_hangxian_clicked();
    void on_pushButton_exec_clicked();
    void showAbout();
    void setButtonsEnable(bool enable);
    void setSortableTableView(QSqlQueryModel *model);
};

#endif // MAINWINDOW_H
