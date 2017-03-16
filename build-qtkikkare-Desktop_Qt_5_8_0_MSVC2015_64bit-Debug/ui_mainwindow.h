/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *btn0;
    QLabel *result;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QPushButton *btnEquals;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QPushButton *btn9;
    QPushButton *btn7;
    QPushButton *btn4;
    QPushButton *btn8;
    QPushButton *btn1;
    QPushButton *btn3;
    QPushButton *btn6;
    QPushButton *btn2;
    QPushButton *btn5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(328, 318);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 50, 241, 20));
        btn0 = new QPushButton(centralWidget);
        btn0->setObjectName(QStringLiteral("btn0"));
        btn0->setGeometry(QRect(90, 180, 81, 22));
        result = new QLabel(centralWidget);
        result->setObjectName(QStringLiteral("result"));
        result->setGeometry(QRect(10, 20, 241, 20));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 220, 241, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnPlus = new QPushButton(widget);
        btnPlus->setObjectName(QStringLiteral("btnPlus"));

        horizontalLayout->addWidget(btnPlus);

        btnMinus = new QPushButton(widget);
        btnMinus->setObjectName(QStringLiteral("btnMinus"));

        horizontalLayout->addWidget(btnMinus);

        btnEquals = new QPushButton(widget);
        btnEquals->setObjectName(QStringLiteral("btnEquals"));

        horizontalLayout->addWidget(btnEquals);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 90, 239, 83));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn9 = new QPushButton(widget1);
        btn9->setObjectName(QStringLiteral("btn9"));

        gridLayout->addWidget(btn9, 0, 2, 1, 1);

        btn7 = new QPushButton(widget1);
        btn7->setObjectName(QStringLiteral("btn7"));

        gridLayout->addWidget(btn7, 0, 0, 1, 1);

        btn4 = new QPushButton(widget1);
        btn4->setObjectName(QStringLiteral("btn4"));

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn8 = new QPushButton(widget1);
        btn8->setObjectName(QStringLiteral("btn8"));

        gridLayout->addWidget(btn8, 0, 1, 1, 1);

        btn1 = new QPushButton(widget1);
        btn1->setObjectName(QStringLiteral("btn1"));

        gridLayout->addWidget(btn1, 2, 0, 1, 1);

        btn3 = new QPushButton(widget1);
        btn3->setObjectName(QStringLiteral("btn3"));

        gridLayout->addWidget(btn3, 2, 2, 1, 1);

        btn6 = new QPushButton(widget1);
        btn6->setObjectName(QStringLiteral("btn6"));

        gridLayout->addWidget(btn6, 1, 2, 1, 1);

        btn2 = new QPushButton(widget1);
        btn2->setObjectName(QStringLiteral("btn2"));

        gridLayout->addWidget(btn2, 2, 1, 1, 1);

        btn5 = new QPushButton(widget1);
        btn5->setObjectName(QStringLiteral("btn5"));

        gridLayout->addWidget(btn5, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 328, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        btn0->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        result->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        btnPlus->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        btnMinus->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        btnEquals->setText(QApplication::translate("MainWindow", "=", Q_NULLPTR));
        btn9->setText(QApplication::translate("MainWindow", "9", Q_NULLPTR));
        btn7->setText(QApplication::translate("MainWindow", "7", Q_NULLPTR));
        btn4->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        btn8->setText(QApplication::translate("MainWindow", "8", Q_NULLPTR));
        btn1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        btn3->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        btn6->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        btn2->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        btn5->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
