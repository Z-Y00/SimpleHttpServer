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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QLineEdit *lineEdit_Port;
    QLabel *label_Port;
    QLineEdit *lineEdit_Path;
    QLabel *label_Path;
    QPushButton *pushButton_Start;
    QMenuBar *menuBar;
    QMenu *menuY00;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit_Port = new QLineEdit(centralWidget);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(100, 80, 271, 21));
        lineEdit_Port->setClearButtonEnabled(false);
        label_Port = new QLabel(centralWidget);
        label_Port->setObjectName(QStringLiteral("label_Port"));
        label_Port->setGeometry(QRect(30, 80, 72, 15));
        lineEdit_Path = new QLineEdit(centralWidget);
        lineEdit_Path->setObjectName(QStringLiteral("lineEdit_Path"));
        lineEdit_Path->setGeometry(QRect(100, 120, 271, 21));
        lineEdit_Path->setClearButtonEnabled(false);
        label_Path = new QLabel(centralWidget);
        label_Path->setObjectName(QStringLiteral("label_Path"));
        label_Path->setGeometry(QRect(30, 120, 72, 15));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(20, 180, 361, 61));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuY00 = new QMenu(menuBar);
        menuY00->setObjectName(QStringLiteral("menuY00"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuY00->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        lineEdit_Port->setInputMask(QString());
        lineEdit_Port->setPlaceholderText(QString());
        label_Port->setText(QApplication::translate("MainWindow", "Port\357\274\232", Q_NULLPTR));
        lineEdit_Path->setInputMask(QString());
        lineEdit_Path->setPlaceholderText(QString());
        label_Path->setText(QApplication::translate("MainWindow", "fileBase\357\274\232", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        menuY00->setTitle(QApplication::translate("MainWindow", "Y00", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
