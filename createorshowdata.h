#ifndef CREATEORSHOWDATA_H
#define CREATEORSHOWDATA_H

#include "alldata.h"
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class CreateOrShowData;
}

class CreateOrShowData : public QDialog
{
    Q_OBJECT

public:
    explicit CreateOrShowData(QWidget *parent = nullptr);
    ~CreateOrShowData();
signals:
    void signalCreateDataList();

private slots:
    void on_CreateBtn_clicked();

    void on_ShowBtn_clicked();

private:
    Ui::CreateOrShowData *ui;
    MainWindow *w;
    AllData *allDataWindow;
};

#endif // CREATEORSHOWDATA_H
