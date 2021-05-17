#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QTextStream>
#include "confirmdialog.h"


Q_DECLARE_METATYPE(QMenu*)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    onClose = false;
    ui->setupUi(this);
    nationality = "Russian";
    ui->FNText->setPlaceholderText("Enter your first name");
    ui->LNText->setPlaceholderText("Enter your last name");
    QRegExp rx("[a-zA-Z]+");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->FNText->setValidator(validator);
    ui->LNText->setValidator(validator);


    QMenu *rusMenu = new QMenu("Russia");      //Set up parameters for toolbar(Select nationality box)
    QMenu  *usaMenu = new QMenu ("USA");
    rusMenu->addAction("Russian");
    rusMenu->addAction("Ukrainian");
    rusMenu->addAction("Tatar");
    rusMenu->addAction("Bashkir");

    usaMenu->addAction("German");
    usaMenu->addAction("African American");
    usaMenu->addAction("Mexican");
    usaMenu->addAction("American");

    QToolBar *toolbar = new QToolBar();
    ui->formLayout->insertRow(3,"Nationality", toolbar);
    QMenu *mainMenu = new QMenu("Russian");
    QAction *swedenAction = new QAction("Sweden");
    QAction *polishAction = new QAction("Poland");
    mainMenu->addAction(rusMenu->menuAction());
    mainMenu->addAction(usaMenu->menuAction());
    mainMenu->addAction(swedenAction);
    mainMenu->addAction(polishAction);
    toolbar->addAction(mainMenu->menuAction());
    for (auto *action : rusMenu->actions()) {
        connect(action, &QAction::triggered, mainMenu, [=](){
            mainMenu->setTitle(action->text());
            nationality = action->text();
        });
    }
    for (auto *action : usaMenu->actions()) {
        connect(action, &QAction::triggered, mainMenu, [=](){
            mainMenu->setTitle(action->text());
            nationality = action->text();
        });
    }
    connect(swedenAction, &QAction::triggered, mainMenu, [=](){
        mainMenu->setTitle(swedenAction->text());
        nationality = swedenAction->text();
    });
    connect(polishAction, &QAction::triggered, mainMenu, [=](){
        mainMenu->setTitle(polishAction->text());
        nationality = polishAction->text();
    });
    connect(this, &MainWindow::resetToolBar, mainMenu, [=](){
            mainMenu->setTitle("Russian");
            nationality = "Russian";
        });


    ui->DODEdit->hide();
    connect(ui->DODCheck, SIGNAL(ui->DODCheck->stateChanged(int)), this, SLOT(on_DODCheck_stateChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DODCheck_stateChanged(int arg1)
{
    if(ui->DODCheck->isChecked())
        ui->DODEdit->show();
    else
        ui->DODEdit->hide();
}

void MainWindow::on_SaveButton_clicked()
{
    if(checkInfo())                         //Final check for every parameter
    {
        ConfirmDialog *confirmDialog = new ConfirmDialog();             //Creating the text for ConfirmDialog
        QString lastName = ui->LNText->text();
        QString firstName = ui->FNText->text();
        bool male = true;
        if(ui->SexBox->currentIndex() == 1)
            male = false;
        int age = ui->AgeBox->value();
        int height = ui->HeightBox->value();
        int weight = ui->WeightBox->value();
        QDate dateOfBirth = ui->DOBEdit->date();
        bool death = ui->DODCheck->isChecked();
        QDate dateOfDeath;
        QString dobString;
        if(death)
            dateOfDeath = ui->DODEdit->date();
        if(dateOfBirth.month() < 10)
            dobString = QString::number(dateOfBirth.day()) + "." + "0" + QString::number(dateOfBirth.month()) + "." + QString::number(dateOfBirth.year());
        else
            dobString = QString::number(dateOfBirth.day()) + "." + QString::number(dateOfBirth.month()) + "." + QString::number(dateOfBirth.year());


        QString text = "First Name: " + firstName + "\n" + "Last Name: " + lastName + "\n" +
                "Sex: " + (male ? "Male" : "Female") + "\n" + "Age: " + QString::number(age) + "\n" +
                "Height: " + QString::number(height) + "\n" + "Weight: " + QString::number(weight) + "\n" +
                "Nationality: " + nationality + "\n" + "Date of birth:" + dobString + "\n" +
               // QString::number(dateOfBirth.day()) + "." + QString::number(dateOfBirth.month()) + "." + QString::number(dateOfBirth.year()) + "\n" +
                "Date of death: ";
        if(death)
        {
            if(dateOfDeath.month() < 10)
                text += QString::number(dateOfDeath.day()) + "." + "0" + QString::number(dateOfDeath.month()) + "." + QString::number(dateOfDeath.year());
            else {
                text += QString::number(dateOfDeath.day()) + "." + QString::number(dateOfDeath.month()) + "." + QString::number(dateOfDeath.year());
            }
        }
        else {
            text += "No";
        }
        connect(this, SIGNAL(sendText(QString*)), confirmDialog, SLOT(addText(QString*)));
        connect(confirmDialog, SIGNAL(accepted()),this, SLOT(saveDataToFile()));
        connect(confirmDialog, SIGNAL(rejected()),this, SLOT(setWindowEnable()));
        confirmDialog->show();
        sendText(&text);
        setDisabled(true);
    }
   // returnToStart();
}

void MainWindow::on_AgeBox_editingFinished()
{
    if((ui->AgeBox->value() < 5 || ui->AgeBox->value() > 150) && !onClose)
    {
        ui->AgeBox->setValue(18);
        QDialog *wrongAge = new QDialog();
        wrongAge->setGeometry(300,300,300,50);
        wrongAge->setWindowTitle("Wrong Age");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongAge);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongAge, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel("Wrong Age. Enter it again"));
        layout->addWidget(btnBox);
        wrongAge->setLayout(layout);
        wrongAge->exec();
    }
}

void MainWindow::setWindowEnable()
{
    setEnabled(true);
}

void MainWindow::saveDataToFile()
{
    QString lastName = ui->LNText->text();
    QString firstName = ui->FNText->text();
    bool male = true;
    if(ui->SexBox->currentIndex() == 1)
        male = false;
    int age = ui->AgeBox->value();
    int height = ui->HeightBox->value();
    int weight = ui->WeightBox->value();
    QDate dateOfBirth = ui->DOBEdit->date();
    bool death = ui->DODCheck->isChecked();
    QDate dateOfDeath;
    if(death)
        dateOfDeath = ui->DODEdit->date();

    QString filename = "Data.txt";
    dataFile = new QFile(filename);
    if(dataFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(dataFile);
        stream << "{" << endl;
        stream << "   " << "\"First Name\":"<< "\"" << firstName << "\"," << endl;
        stream << "   " << "\"Last Name\":"<< "\"" << lastName << "\"," << endl;
        QString sex = male ? "Male" : "Female";
        stream << "   " << "\"Sex\":"<< "\"" << sex << "\"," << endl;
        stream << "   " << "\"Age\":"<< "\"" << age << "\"," << endl;
        stream << "   " << "\"Height\":"<< "\"" << height << "\"," << endl;
        stream << "   " << "\"Weight\":"<< "\"" << weight << "\"," << endl;
        stream << "   " << "\"Nationality\":"<< "\"" << nationality << "\"," << endl;
        QString dobString;
        if(dateOfBirth.month() < 10)
            dobString = QString::number(dateOfBirth.day()) + "." + "0" + QString::number(dateOfBirth.month()) + "." + QString::number(dateOfBirth.year());
        else
            dobString = QString::number(dateOfBirth.day()) + "." + QString::number(dateOfBirth.month()) + "." + QString::number(dateOfBirth.year());

        stream << "   " << "\"Date of birth\":"<< "\"" << dobString << "\"," << endl;

        QString dodString;

        if(death)
        {
            if(dateOfDeath.month() < 10)
                dodString = QString::number(dateOfDeath.day()) + "." + "0" + QString::number(dateOfDeath.month()) + "." + QString::number(dateOfDeath.year());
            else {
                QString::number(dateOfDeath.day()) + "." + QString::number(dateOfDeath.month()) + "." + QString::number(dateOfDeath.year());
            }
                stream << "   " << "\"Date of death\":"<< "\"" << dodString << "\"" << endl;
        }
        else
            stream << "   " << "\"Date of death\":"<< "\"" << "No" << "\"" << endl;
        stream << "}" << endl;
    }

    setEnabled(true);
    ui->FNText->setText("");
    ui->LNText->setText("");
    ui->AgeBox->setValue(18);
    ui->WeightBox->setValue(70);
    ui->HeightBox->setValue(180);
    ui->SexBox->setCurrentIndex(0);
    resetToolBar();
    ui->DOBEdit->setDate(QDate(2000,1,1));
    ui->DODCheck->setChecked(false);
    ui->DODEdit->setDate(QDate(2000,1,1));
    close();
}

void MainWindow::closeEvent(QCloseEvent *bar)
{
    onClose = true;
    returnToStart();
}

bool MainWindow::checkInfo()
{
    QString wrongInfo = "";
    if(ui->FNText->text() == "")
        wrongInfo += "First name must be a nonempty string. \n";
    if(ui->LNText->text() == "")
        wrongInfo += "Last name must be a nonempty string. \n";
    if(ui->AgeBox->value() < 5 || ui->AgeBox->value() > 150)
        wrongInfo += "Wrong age. \n";
    if(ui->HeightBox->value() < 50 || ui->HeightBox->value() > 300)
        wrongInfo += "Wrong height. \n";
    if(ui->WeightBox->value() < 20 || ui->WeightBox->value() > 500)
        wrongInfo += "Wrong weight. \n";
    QDate currentDate = QDate::currentDate();
    QDate enteredDate = ui->DOBEdit->date();
    if(enteredDate.year() + ui->AgeBox->value() == currentDate.year())
    {
        if(enteredDate.dayOfYear() > currentDate.dayOfYear())
            wrongInfo += "Wrong date of birth. \n";
    }
    else if (enteredDate.year() + ui->AgeBox->value() == currentDate.year() + 1) {
        if(enteredDate.dayOfYear() < currentDate.dayOfYear())
            wrongInfo += "Wrong date of birth. \n";
    }
    else {
        wrongInfo += "Wrong date of birth. \n";
    }
    if(ui->DODCheck->isChecked())
    {
        QDate enteredDOD = ui->DODEdit->date();
        if(enteredDOD.year() == currentDate.year())
        {
            if(enteredDOD.dayOfYear() > currentDate.dayOfYear())
                wrongInfo += "Wrong date of death. \n";
        }
        else if (enteredDOD.year() > currentDate.year()) {
            wrongInfo += "Wrong date of death. \n";
        }
        else if (enteredDOD.year() < ui->DOBEdit->date().year()) {
            wrongInfo += "Wrong date of death. \n";
        }
    }
    if(wrongInfo != "")
    {
        QDialog *wrongDialog = new QDialog();
        wrongDialog->setGeometry(300,300,300,200);
        wrongDialog->setWindowTitle("Wrong info");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongDialog);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongDialog, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel(wrongInfo));
        layout->addWidget(btnBox);
        wrongDialog->setLayout(layout);
        wrongDialog->exec();
        return false;
    }

    return true;
}


void MainWindow::on_HeightBox_editingFinished()
{
    if((ui->HeightBox->value() < 50 || ui->HeightBox->value() > 300) && !onClose)
    {
        ui->HeightBox->setValue(180);
        QDialog *wrongHeight = new QDialog();
        wrongHeight->setGeometry(300,300,300,50);
        wrongHeight->setWindowTitle("Wrong Height");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongHeight);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongHeight, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel("Wrong Height. Enter it again"));
        layout->addWidget(btnBox);
        wrongHeight->setLayout(layout);
        wrongHeight->exec();
    }
}

void MainWindow::on_WeightBox_editingFinished()
{
    if((ui->WeightBox->value() < 20 || ui->WeightBox->value() > 500) && !onClose)
    {
        ui->HeightBox->setValue(70);
        QDialog *wrongWeight = new QDialog();
        wrongWeight->setGeometry(300,300,300,50);
        wrongWeight->setWindowTitle("Wrong Weight");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongWeight);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongWeight, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel("Wrong Weight. Enter it again"));
        layout->addWidget(btnBox);
        wrongWeight->setLayout(layout);
        wrongWeight->exec();
    }
}

void MainWindow::on_DOBEdit_editingFinished()
{
    auto wrongDate = [&](){
        ui->DOBEdit->setDate(QDate(2000,1,1));
        QDialog *wrongDOB = new QDialog();
        wrongDOB->setGeometry(300,300,300,50);
        wrongDOB->setWindowTitle("Wrong Date of birth");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongDOB);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongDOB, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel("Wrong Date of birth. Enter it again"));
        layout->addWidget(btnBox);
        wrongDOB->setLayout(layout);
        wrongDOB->exec();
    };
    QDate currentDate = QDate::currentDate();
    QDate enteredDate = ui->DOBEdit->date();
    if(enteredDate.year() + ui->AgeBox->value() == currentDate.year())
    {
        if(enteredDate.dayOfYear() > currentDate.dayOfYear())
            wrongDate();
    }
    else if (enteredDate.year() + ui->AgeBox->value() == currentDate.year() + 1) {
        if(enteredDate.dayOfYear() < currentDate.dayOfYear())
            wrongDate();
    }
    else {
        wrongDate();
    }
}

void MainWindow::on_DODEdit_editingFinished()
{
    auto wrongDate = [&](){
        ui->DODEdit->setDate(QDate(2000,1,1));
        QDialog *wrongDOD = new QDialog();
        wrongDOD->setGeometry(300,300,300,50);
        wrongDOD->setWindowTitle("Wrong Date of death");
        QDialogButtonBox *btnBox = new QDialogButtonBox(wrongDOD);
        btnBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(btnBox, &QDialogButtonBox::accepted, wrongDOD, &QDialog::accept);
        QFormLayout *layout = new QFormLayout();
        layout->addRow("", new QLabel("Wrong Date of death. Enter it again"));
        layout->addWidget(btnBox);
        wrongDOD->setLayout(layout);
        wrongDOD->exec();
    };
    QDate currentDate = QDate::currentDate();
    QDate enteredDate = ui->DODEdit->date();
    if(enteredDate.year() == currentDate.year())
    {
        if(enteredDate.dayOfYear() > currentDate.dayOfYear())
            wrongDate();
    }
    else if (enteredDate.year() > currentDate.year()) {
        wrongDate();
    }
    else if (enteredDate.year() < ui->DOBEdit->date().year()) {
        wrongDate();
    }
}
