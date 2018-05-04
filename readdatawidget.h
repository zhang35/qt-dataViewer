#ifndef READDATAWIDGET_H
#define READDATAWIDGET_H

#include <QWidget>

namespace Ui {
    class ReadDataWidget;
}

class ReadDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReadDataWidget(QWidget *parent = 0);
    ~ReadDataWidget();

private:
    Ui::ReadDataWidget *ui;

private slots:
    void on_pushButton_extract_clicked();
};

#endif // READDATAWIDGET_H
