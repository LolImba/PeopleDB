#ifndef ALLDATA_H
#define ALLDATA_H

#include <QDialog>


namespace Ui {
class AllData;
}

class AllData : public QDialog
{
    Q_OBJECT

public:
    explicit AllData(QWidget *parent = nullptr);
    ~AllData();
signals:
    void signalOkClicked();
    void returnToStart();
private:
    Ui::AllData *ui;
private slots:
    void createDataList();
    void on_Ok_clicked();
private:
    void closeEvent(QCloseEvent *bar);
};

#endif // ALLDATA_H
