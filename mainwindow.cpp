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
       //����ȡ����ini�ļ�������QString�У���ȡֵ��Ȼ��ͨ��toString()����ת����QString����
       QString daotiaoIP = configIniRead->value("/ip/daotiao").toString();
       QString redIP = configIniRead->value("/ip/red").toString();
       QString blueIP = configIniRead->value("/ip/blue").toString();
       //��ӡ�õ��Ľ��
       qDebug() << daotiaoIP;
       qDebug() << redIP;
        qDebug() << blueIP;
       //��������ɺ�ɾ��ָ��
       delete configIniRead;

    ui->comboBox->addItem("����", daotiaoIP);
    ui->comboBox->addItem("���", redIP);
    ui->comboBox->addItem("����", blueIP);
    ui->comboBox->setCurrentIndex(0);

    ui->tableView->setSortingEnabled(true);

    this->setButtonsEnable(false);
    this->setWindowTitle(tr("ָ��ϵͳ���ݲ鿴����"));

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
          QString message = tr("���ӳɹ���") + ui->comboBox->currentText();
         statusBar()->showMessage(message);
         this->setButtonsEnable(true);
      }
      else{
           statusBar()->showMessage("����ʧ��");
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
       //����ȡ����ini�ļ�������QString�У���ȡֵ��Ȼ��ͨ��toString()����ת����QString����
        int port = configIniRead->value("/port/port").toInt();

       QString database = configIniRead->value("/mysql/database").toString();
       QString username = configIniRead->value("/mysql/username").toString();
       QString password = configIniRead->value("/mysql/password").toString();
       //��ӡ�õ��Ľ��
       qDebug() << database;
       qDebug() << username;
        qDebug() << password;
       //��������ɺ�ɾ��ָ��
       delete configIniRead;
    QString ip = ui->comboBox->itemData(ui->comboBox->currentIndex()).toString();
    connectDB(ip, port, database, username, password);
}

void MainWindow::showAbout(){
    QMessageBox::information( this,tr("����"), tr("ָ��ϵͳ���ݲ鿴����V1.0 By ZJQ") ,tr("ȷ��"),0);
}

void MainWindow::on_action_about_triggered()
{
    this->showAbout();
}

void MainWindow::on_pushButton_type_kongyu_clicked()
{
    this->readDataWidget.show();
}
