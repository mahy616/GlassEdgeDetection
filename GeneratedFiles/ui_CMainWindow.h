/********************************************************************************
** Form generated from reading UI file 'CMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_CMainWindowClass
{
public:
    QAction *action_Start;
    QAction *action_Stop;
    QAction *action_Setting;
    QAction *action_DataManager;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    MyLabel *label_Image;
    MyLabel *label_Image_Right;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindowClass)
    {
        if (CMainWindowClass->objectName().isEmpty())
            CMainWindowClass->setObjectName(QString::fromUtf8("CMainWindowClass"));
        CMainWindowClass->resize(1161, 795);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CMainWindowClass->setWindowIcon(icon);
        action_Start = new QAction(CMainWindowClass);
        action_Start->setObjectName(QString::fromUtf8("action_Start"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/CMainWindow/Resources/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Start->setIcon(icon1);
        action_Stop = new QAction(CMainWindowClass);
        action_Stop->setObjectName(QString::fromUtf8("action_Stop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/CMainWindow/Resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop->setIcon(icon2);
        action_Setting = new QAction(CMainWindowClass);
        action_Setting->setObjectName(QString::fromUtf8("action_Setting"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/CMainWindow/Resources/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Setting->setIcon(icon3);
        action_DataManager = new QAction(CMainWindowClass);
        action_DataManager->setObjectName(QString::fromUtf8("action_DataManager"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/CMainWindow/Resources/data.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DataManager->setIcon(icon4);
        centralWidget = new QWidget(CMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Image = new MyLabel(centralWidget);
        label_Image->setObjectName(QString::fromUtf8("label_Image"));
        label_Image->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout->addWidget(label_Image, 0, 0, 2, 1);

        label_Image_Right = new MyLabel(centralWidget);
        label_Image_Right->setObjectName(QString::fromUtf8("label_Image_Right"));
        label_Image_Right->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout->addWidget(label_Image_Right, 0, 1, 2, 1);

        CMainWindowClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(50, 50));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        CMainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CMainWindowClass->setStatusBar(statusBar);

        mainToolBar->addAction(action_Start);
        mainToolBar->addAction(action_Stop);
        mainToolBar->addAction(action_Setting);
        mainToolBar->addAction(action_DataManager);

        retranslateUi(CMainWindowClass);

        QMetaObject::connectSlotsByName(CMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindowClass)
    {
        CMainWindowClass->setWindowTitle(QCoreApplication::translate("CMainWindowClass", "\347\216\273\347\222\203\351\235\242\346\235\277\347\274\272\351\231\267\346\243\200\346\265\213_V1.0.0", nullptr));
        action_Start->setText(QCoreApplication::translate("CMainWindowClass", "\345\274\200\345\247\213", nullptr));
        action_Stop->setText(QCoreApplication::translate("CMainWindowClass", "\345\201\234\346\255\242", nullptr));
        action_Setting->setText(QCoreApplication::translate("CMainWindowClass", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        action_DataManager->setText(QCoreApplication::translate("CMainWindowClass", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        label_Image->setText(QString());
        label_Image_Right->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CMainWindowClass: public Ui_CMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
