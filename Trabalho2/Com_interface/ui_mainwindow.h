/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *startButton;
    QLabel *label_PF;
    QLineEdit *lineEdit;
    QLabel *label_Frame;
    QListWidget *listWidget_OPT;
    QSpinBox *spinBox;
    QListWidget *listWidget_LRU;
    QListWidget *listWidget_FIFO;
    QLabel *label_OPT_result;
    QLabel *label_OPT;
    QLabel *label_LRU;
    QLabel *label_FIFO;
    QLabel *label_LRU_result;
    QLabel *label_FIFO_result;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(767, 381);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(280, 90, 151, 21));
        label_PF = new QLabel(centralwidget);
        label_PF->setObjectName(QString::fromUtf8("label_PF"));
        label_PF->setGeometry(QRect(90, 40, 91, 31));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 40, 161, 31));
        label_Frame = new QLabel(centralwidget);
        label_Frame->setObjectName(QString::fromUtf8("label_Frame"));
        label_Frame->setGeometry(QRect(360, 40, 61, 31));
        listWidget_OPT = new QListWidget(centralwidget);
        listWidget_OPT->setObjectName(QString::fromUtf8("listWidget_OPT"));
        listWidget_OPT->setGeometry(QRect(40, 140, 211, 171));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(420, 40, 161, 31));
        spinBox->setValue(0);
        listWidget_LRU = new QListWidget(centralwidget);
        listWidget_LRU->setObjectName(QString::fromUtf8("listWidget_LRU"));
        listWidget_LRU->setGeometry(QRect(260, 140, 211, 171));
        listWidget_FIFO = new QListWidget(centralwidget);
        listWidget_FIFO->setObjectName(QString::fromUtf8("listWidget_FIFO"));
        listWidget_FIFO->setGeometry(QRect(480, 140, 211, 171));
        label_OPT_result = new QLabel(centralwidget);
        label_OPT_result->setObjectName(QString::fromUtf8("label_OPT_result"));
        label_OPT_result->setEnabled(true);
        label_OPT_result->setGeometry(QRect(90, 320, 121, 21));
        label_OPT = new QLabel(centralwidget);
        label_OPT->setObjectName(QString::fromUtf8("label_OPT"));
        label_OPT->setGeometry(QRect(120, 120, 41, 16));
        label_LRU = new QLabel(centralwidget);
        label_LRU->setObjectName(QString::fromUtf8("label_LRU"));
        label_LRU->setGeometry(QRect(340, 120, 41, 16));
        label_FIFO = new QLabel(centralwidget);
        label_FIFO->setObjectName(QString::fromUtf8("label_FIFO"));
        label_FIFO->setGeometry(QRect(560, 120, 41, 16));
        label_LRU_result = new QLabel(centralwidget);
        label_LRU_result->setObjectName(QString::fromUtf8("label_LRU_result"));
        label_LRU_result->setEnabled(true);
        label_LRU_result->setGeometry(QRect(310, 320, 121, 21));
        label_FIFO_result = new QLabel(centralwidget);
        label_FIFO_result->setObjectName(QString::fromUtf8("label_FIFO_result"));
        label_FIFO_result->setEnabled(true);
        label_FIFO_result->setGeometry(QRect(540, 320, 121, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 767, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        label_PF->setText(QCoreApplication::translate("MainWindow", "Paging fault", nullptr));
        lineEdit->setText(QString());
        label_Frame->setText(QCoreApplication::translate("MainWindow", "Frames", nullptr));
        label_OPT_result->setText(QString());
        label_OPT->setText(QCoreApplication::translate("MainWindow", "OPT", nullptr));
        label_LRU->setText(QCoreApplication::translate("MainWindow", "LRU", nullptr));
        label_FIFO->setText(QCoreApplication::translate("MainWindow", "FIFO", nullptr));
        label_LRU_result->setText(QString());
        label_FIFO_result->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
