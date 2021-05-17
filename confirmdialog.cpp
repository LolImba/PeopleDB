#include "confirmdialog.h"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::addText(QString *text)
{
    ui->textBrowser->setText(*text);
}

void ConfirmDialog::closeEvent(QCloseEvent *bar)
{
    rejected();
}
