#include "readdatawidget.h"
#include "ui_readdatawidget.h"
#include <QDebug>
ReadDataWidget::ReadDataWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ReadDataWidget)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("¿ÕÓòÂ¼Èë¹¤¾ß"));

}

ReadDataWidget::~ReadDataWidget()
{
    delete ui;
}

void ReadDataWidget::on_pushButton_extract_clicked()
{
    QString data = ui->textEdit->toPlainText();


    QList<QString> list;
    QString coordinate = "";

    int i = 0;
    int count = 0;
    while(1)
    {
        bool isEnd = false;
        while (data[i]<'0' || data[i]>'9')
        {
            i++;
            if (i>=data.length())
            {
                isEnd = true;
                break;
            }
        }

        if (isEnd){
            break;
        }
        while (data[i]>='0' && data[i]<='9')
        {
            coordinate.append(data[i]);
            i++;
            if (i>=data.length())
            {
                isEnd = true;
                break;
            }
        }

        switch (count){
        case 0:
            coordinate.append("¡ã");
            break;
        case 1:
            coordinate.append("¡ä");
            break;
        case 2:
            coordinate.append("¡å");

            list.append(coordinate);
            coordinate = "";
            break;
        }
        count = (count+1)%3;

        if (isEnd){
            break;
        }

    }

    QString x, y;
    for (int j=0; j<list.size(); j++){

        if (j%2==0)
        {
            x = list.at(j);
        }
        else
        {
            y = list.at(j);
            qDebug()<< QString("E"+ x + "N" + y);
        }
    }

}
