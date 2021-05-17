#include "createorshowdata.h"
#include "ui_createorshowdata.h"
#include "mainwindow.h"
#include "alldata.h"

CreateOrShowData::CreateOrShowData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateOrShowData)
{
    ui->setupUi(this);
    w = new MainWindow;
    QString filename = "Data.txt";
    allDataWindow = new AllData;
    connect(allDataWindow, SIGNAL(returnToStart()), this, SLOT(show()));
    connect(w, SIGNAL(returnToStart()), this, SLOT(show()));
    connect(this, SIGNAL(signalCreateDataList()), allDataWindow, SLOT(createDataList()));
}

CreateOrShowData::~CreateOrShowData()
{
    delete ui;
}

void CreateOrShowData::on_CreateBtn_clicked()
{
    w->show();
    hide();
}

void CreateOrShowData::on_ShowBtn_clicked()
{
    allDataWindow->show();
    signalCreateDataList();
    hide();
}
