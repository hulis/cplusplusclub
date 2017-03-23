#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

enum OPERATION
{
    PLUS,
    MINUS
};

int first = 0;
int operation = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* btns[] = {
        ui->btn0,
        ui->btn1,
        ui->btn2,
        ui->btn3,
        ui->btn4,
        ui->btn5,
        ui->btn6,
        ui->btn7,
        ui->btn8,
        ui->btn9,


    };

    for (int i = 0; i < 10; ++i)
    {
        connect(btns[i], &QPushButton::clicked, [=](){
            ui->lineEdit->setText(
                        ui->lineEdit->text() + QString::number(i)
            );
        });
    }

    connect(ui->btnPlus, &QPushButton::clicked, [&](){
        first = std::atoi(ui->lineEdit->text().toLatin1().data());
        ui->lineEdit->clear();
        operation = PLUS;
    });

    connect(ui->btnMinus, &QPushButton::clicked, [&](){
        first = std::atoi(ui->lineEdit->text().toLatin1().data());
        ui->lineEdit->clear();
        operation = MINUS;
    });

    connect(ui->btnEquals, &QPushButton::clicked, [&](){
        int second = std::atoi(ui->lineEdit->text().toLatin1().data());
        switch (operation)
        {
        case PLUS:
            ui->result->setText(
                        QString::number(first) +
                        QLatin1String(" + ") +
                        QString::number(second) +
                        QLatin1String(" = ") +
                        QString::number(first + second)
                        );
            break;
        case MINUS:
            ui->result->setText(
                        QString::number(first) +
                        QLatin1String(" - ") +
                        QString::number(second) +
                        QLatin1String(" = ") +
                        QString::number(first - second)
                        );
            break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
