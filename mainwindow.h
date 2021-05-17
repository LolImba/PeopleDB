#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFile *dataFile;
    bool onClose;
    QString nationality;
signals:
    void returnToStart();
    void sendText(QString *text);
    void resetToolBar();
private slots:
    void on_DODCheck_stateChanged(int arg1);
    void on_SaveButton_clicked();
    void on_AgeBox_editingFinished();
    void setWindowEnable();
    void saveDataToFile();
    void on_HeightBox_editingFinished();

    void on_WeightBox_editingFinished();

    void on_DOBEdit_editingFinished();

    void on_DODEdit_editingFinished();

private:
    void closeEvent(QCloseEvent *bar);
    bool checkInfo();
};

#endif // MAINWINDOW_H
