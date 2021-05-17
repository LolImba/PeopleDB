#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();
private slots:
    void addText(QString *text);
private:
    Ui::ConfirmDialog *ui;
private:
    void closeEvent(QCloseEvent *bar);
};

#endif // CONFIRMDIALOG_H
