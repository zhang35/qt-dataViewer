#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings *configIniRead = new QSettings("config.ini", QSettings::IniFormat);
       //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
       QString daotiaoIP = configIniRead->value("/ip/daotiao").toString();
       QString redIP = configIniRead->value("/ip/red").toString();
       QString blueIP = configIniRead->value("/ip/blue").toString();
       //打印得到的结果
       qDebug() << daotiaoIP;
       qDebug() << redIP;
        qDebug() << blueIP;
       //读入入完成后删除指针
       delete configIniRead;

    ui->comboBox->addItem("导调", daotiaoIP);
    ui->comboBox->addItem("红军", redIP);
    ui->comboBox->addItem("蓝军", blueIP);
    ui->comboBox->setCurrentIndex(0);

    ui->tableView->setSortingEnabled(true);

    this->setButtonsEnable(false);
    this->setWindowTitle(tr("指控系统数据查看工具"));

        this->db = QSqlDatabase::addDatabase("QMYSQL");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDB(QString ip, int port, QString database, QString username, QString password){
     this->db.setHostName(ip);
     this->db.setPort(port);
     this->db.setDatabaseName(database);
     this->db.setUserName(username);
     this->db.setPassword(password);
      if (db.open()){
          QString message = tr("连接成功：") + ui->comboBox->currentText();
         statusBar()->showMessage(message);
         this->setButtonsEnable(true);
      }
      else{
           statusBar()->showMessage("连接失败");
      }
}

void MainWindow::setButtonsEnable(bool enable){
            ui->pushButton_exec->setEnabled(enable);
            ui->pushButton_mark->setEnabled(enable);
                ui->pushButton_kongyu->setEnabled(enable);
                ui->pushButton_hangxian->setEnabled(enable);
}

void MainWindow::setSortableTableView(QSqlQueryModel *model){
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);
}

void MainWindow::on_pushButton_mark_clicked()
{
           QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("SELECT * FROM mark_tab");
           setSortableTableView(model);

}

void MainWindow::on_pushButton_kongyu_clicked()
{

           QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("SELECT * FROM kongyu_tab");
           setSortableTableView(model);

}

void MainWindow::on_pushButton_hangxian_clicked()
{

    QSqlQueryModel *model = new QSqlQueryModel;
     model->setQuery("SELECT * FROM hangxian_tab");
    setSortableTableView(model);
}

void MainWindow::on_pushButton_exec_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;        
    QString sql= ui->lineEdit_sql->text();
            model->setQuery(sql);
           setSortableTableView(model);
}

void MainWindow::on_pushButton_connect_clicked()
{
    if (db.isValid())
    {
        db.close();
    }
    QSettings *configIniRead = new QSettings("config.ini", QSettings::IniFormat);
       //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
        int port = configIniRead->value("/port/port").toInt();

       QString database = configIniRead->value("/mysql/database").toString();
       QString username = configIniRead->value("/mysql/username").toString();
       QString password = configIniRead->value("/mysql/password").toString();
       //打印得到的结果
       qDebug() << database;
       qDebug() << username;
        qDebug() << password;
       //读入入完成后删除指针
       delete configIniRead;
    QString ip = ui->comboBox->itemData(ui->comboBox->currentIndex()).toString();
    connectDB(ip, port, database, username, password);
}

void MainWindow::showAbout(){
    QMessageBox::information( this,tr("关于"), tr("指控系统数据查看工具V1.0 By ZJQ") ,tr("确定"),0);
}

void MainWindow::on_action_about_triggered()
{
    this->showAbout();
}

void MainWindow::on_pushButton_type_kongyu_clicked()
{
    this->readDataWidget.show();
}
