#include "mainwindow.h"
#include <QApplication>
#include "alldata.h"
#include "createorshowdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CreateOrShowData questionWindow;
    questionWindow.show();
    return a.exec();
}
