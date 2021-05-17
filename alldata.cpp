#include "alldata.h"
#include "ui_alldata.h"

#include <QFile>
#include <QLabel>
#include <QScrollArea>
#include <QTextBrowser>
#include <QTextStream>
#include <QVBoxLayout>

AllData::AllData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllData)
{
    ui->setupUi(this);
}

AllData::~AllData()
{
    delete ui;
}

void AllData::createDataList()
{
    QString filename = "Data.txt";
    QFile *dataFile = new QFile(filename);
    if(dataFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(dataFile);
        QVBoxLayout* layout = new QVBoxLayout;
        while(true)
        {
            QString currentText = stream.readLine();
            if(currentText.contains("{"))
            {
                currentText = "";
                while(true)
                {
                    QString temp = stream.readLine();
                    if(temp != "}")
                    {
                        int startIndex = temp.indexOf(":") + 2;
                        int endIndex;
                        if(temp.contains(","))
                            endIndex = temp.indexOf(",") - 1;
                        else {
                            endIndex = temp.size() - 1;
                        }

                        currentText += temp.mid(4, startIndex - 7) + " : " + temp.mid(startIndex, endIndex - startIndex) + "\n";
                    }
                    else {
                        break;
                    }
                }
                QTextBrowser *textBrowser = new QTextBrowser;
                textBrowser->setMinimumHeight(140);
                textBrowser->setText(currentText);
                layout->addWidget(textBrowser);
            }
            else {
                break;
            }
        }
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->scrollArea->setWidgetResizable(true);
        QWidget *widget = new QWidget();

        ui->scrollArea->setWidget(widget);
        widget->setLayout(layout);
    }
}

void AllData::on_Ok_clicked()
{
    hide();
    returnToStart();
}

void AllData::closeEvent(QCloseEvent *bar)
{
    returnToStart();
}
