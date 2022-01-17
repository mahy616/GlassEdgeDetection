/********************************************************************************
** Form generated from reading UI file 'DataManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMANAGER_H
#define UI_DATAMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_DataManager
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_DBName;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_Password;
    QPushButton *pushButton_ConnectDB;
    QLabel *label_DBStatus;
    QLineEdit *lineEdit_JPN;
    QDateEdit *dateEdit_StartDate;
    QDateEdit *dateEdit_EndDate;
    QPushButton *pushButton_Query;
    QTableWidget *tableWidget;
    QCheckBox *checkBox_Date;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    MyLabel *label_Image;
    QLabel *label_CurPath;

    void setupUi(QDialog *DataManager)
    {
        if (DataManager->objectName().isEmpty())
            DataManager->setObjectName(QString::fromUtf8("DataManager"));
        DataManager->resize(1523, 723);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/data.png"), QSize(), QIcon::Normal, QIcon::Off);
        DataManager->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(DataManager);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(DataManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(681, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit_DBName = new QLineEdit(groupBox);
        lineEdit_DBName->setObjectName(QString::fromUtf8("lineEdit_DBName"));

        gridLayout_2->addWidget(lineEdit_DBName, 0, 0, 1, 1);

        lineEdit_UserName = new QLineEdit(groupBox);
        lineEdit_UserName->setObjectName(QString::fromUtf8("lineEdit_UserName"));

        gridLayout_2->addWidget(lineEdit_UserName, 0, 1, 1, 1);

        lineEdit_Password = new QLineEdit(groupBox);
        lineEdit_Password->setObjectName(QString::fromUtf8("lineEdit_Password"));
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_Password, 0, 2, 1, 1);

        pushButton_ConnectDB = new QPushButton(groupBox);
        pushButton_ConnectDB->setObjectName(QString::fromUtf8("pushButton_ConnectDB"));

        gridLayout_2->addWidget(pushButton_ConnectDB, 0, 3, 1, 1);

        label_DBStatus = new QLabel(groupBox);
        label_DBStatus->setObjectName(QString::fromUtf8("label_DBStatus"));
        label_DBStatus->setMinimumSize(QSize(21, 21));
        label_DBStatus->setMaximumSize(QSize(21, 21));
        label_DBStatus->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        gridLayout_2->addWidget(label_DBStatus, 0, 4, 1, 1);

        lineEdit_JPN = new QLineEdit(groupBox);
        lineEdit_JPN->setObjectName(QString::fromUtf8("lineEdit_JPN"));

        gridLayout_2->addWidget(lineEdit_JPN, 1, 0, 1, 1);

        dateEdit_StartDate = new QDateEdit(groupBox);
        dateEdit_StartDate->setObjectName(QString::fromUtf8("dateEdit_StartDate"));
        dateEdit_StartDate->setCalendarPopup(true);

        gridLayout_2->addWidget(dateEdit_StartDate, 1, 1, 1, 1);

        dateEdit_EndDate = new QDateEdit(groupBox);
        dateEdit_EndDate->setObjectName(QString::fromUtf8("dateEdit_EndDate"));
        dateEdit_EndDate->setCalendarPopup(true);

        gridLayout_2->addWidget(dateEdit_EndDate, 1, 2, 1, 1);

        pushButton_Query = new QPushButton(groupBox);
        pushButton_Query->setObjectName(QString::fromUtf8("pushButton_Query"));

        gridLayout_2->addWidget(pushButton_Query, 1, 3, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 2, 0, 1, 5);

        checkBox_Date = new QCheckBox(groupBox);
        checkBox_Date->setObjectName(QString::fromUtf8("checkBox_Date"));

        gridLayout_2->addWidget(checkBox_Date, 1, 4, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DataManager);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Image = new MyLabel(groupBox_2);
        label_Image->setObjectName(QString::fromUtf8("label_Image"));
        label_Image->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout->addWidget(label_Image, 0, 0, 1, 1);

        label_CurPath = new QLabel(groupBox_2);
        label_CurPath->setObjectName(QString::fromUtf8("label_CurPath"));
        label_CurPath->setMaximumSize(QSize(16777215, 16));

        gridLayout->addWidget(label_CurPath, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);


        retranslateUi(DataManager);
        QObject::connect(pushButton_ConnectDB, SIGNAL(clicked()), DataManager, SLOT(ConnectToDB()));
        QObject::connect(pushButton_Query, SIGNAL(clicked()), DataManager, SLOT(QueryData()));
        QObject::connect(checkBox_Date, SIGNAL(clicked(bool)), DataManager, SLOT(SetDateEnabled(bool)));
        QObject::connect(tableWidget, SIGNAL(clicked(QModelIndex)), DataManager, SLOT(ClickedOnTableWidget(QModelIndex)));

        QMetaObject::connectSlotsByName(DataManager);
    } // setupUi

    void retranslateUi(QDialog *DataManager)
    {
        DataManager->setWindowTitle(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\346\237\245\350\257\242", nullptr));
        lineEdit_DBName->setText(QCoreApplication::translate("DataManager", "PanelDeteResult", nullptr));
        lineEdit_DBName->setPlaceholderText(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\345\272\223\345\220\215\347\247\260", nullptr));
        lineEdit_UserName->setText(QCoreApplication::translate("DataManager", "sa", nullptr));
        lineEdit_UserName->setPlaceholderText(QCoreApplication::translate("DataManager", "\347\224\250\346\210\267\345\220\215", nullptr));
        lineEdit_Password->setText(QCoreApplication::translate("DataManager", "k-touch1234", nullptr));
        lineEdit_Password->setPlaceholderText(QCoreApplication::translate("DataManager", "\345\257\206\347\240\201", nullptr));
        pushButton_ConnectDB->setText(QCoreApplication::translate("DataManager", "\350\277\236\346\216\245", nullptr));
        label_DBStatus->setText(QString());
        lineEdit_JPN->setPlaceholderText(QCoreApplication::translate("DataManager", "\346\226\231\345\217\267", nullptr));
        dateEdit_StartDate->setDisplayFormat(QCoreApplication::translate("DataManager", "yyyy-MM-dd hh:mm:ss", nullptr));
        dateEdit_EndDate->setDisplayFormat(QCoreApplication::translate("DataManager", "yyyy-MM-dd hh:mm:ss", nullptr));
        pushButton_Query->setText(QCoreApplication::translate("DataManager", "\346\237\245\350\257\242", nullptr));
        checkBox_Date->setText(QCoreApplication::translate("DataManager", "\346\227\266\351\227\264", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DataManager", "\346\243\200\346\265\213\347\273\223\346\236\234", nullptr));
        label_Image->setText(QString());
        label_CurPath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataManager: public Ui_DataManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMANAGER_H
