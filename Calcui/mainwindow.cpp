#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorbyAlgoMethods)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));

    QPushButton *numButtons[10];

    for(int i = 0; i < 10; ++i){
        QString butName = "button_" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->plus, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->minus, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->division, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->clear, SIGNAL(released()), this,
            SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::NumPressed(){

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
        ui->Display->setText(butVal);
    else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed(){

    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "x", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->Display->setText("");
}
void MainWindow::EqualButtonPressed(){

    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger ){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}
void MainWindow::clear()
{
    ui->Display->setText("0.0");

}

