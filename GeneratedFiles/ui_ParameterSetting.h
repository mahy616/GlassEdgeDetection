/********************************************************************************
** Form generated from reading UI file 'ParameterSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERSETTING_H
#define UI_PARAMETERSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_CamNames_Right;
    QPushButton *pushButton_Open_Right;
    QPushButton *pushButton_Grab_Right;
    QLabel *label_7;
    QSpinBox *spinBox_Exposure_Right;
    QLabel *label_9;
    QSpinBox *spinBox_Gain_Right;
    QRadioButton *radioButton_FreeRun_Right;
    QLabel *label_14;
    QSpinBox *spinBox_Freq_Right;
    QLabel *label_15;
    QSpinBox *spinBox_Height_Right;
    QRadioButton *radioButton_External_Right;
    QLabel *label_16;
    QSpinBox *spinBox_ImageCount_Right;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_11;
    QPushButton *pushButton_LoadImage_Right;
    QPushButton *pushButton_DetectOnce_Right;
    QCheckBox *checkBox_Render_2;
    QRadioButton *radioButton_First_Right;
    QRadioButton *radioButton_Middle_Right;
    QRadioButton *radioButton_Last_Right;
    QLabel *label_30;
    QSpinBox *spinBox_Threshold_Right;
    QLabel *label_31;
    QSpinBox *spinBox_Length_Right;
    QLabel *label_32;
    QSpinBox *spinBox_Distance_Right;
    QLabel *label_22;
    QSpinBox *spinBox_XOffset_Right;
    QLabel *label_33;
    QSpinBox *spinBox_YOffset_Right;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_SavePath;
    QPushButton *pushButton_BrowseSavePath;
    QLineEdit *lineEdit_SavePath_Right;
    QPushButton *pushButton_BrowseSavePath_2;
    MyLabel *label_Image;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QLabel *label_8;
    QSpinBox *spinBox_Speed;
    QLabel *label_13;
    QComboBox *comboBox_SysType;
    QPushButton *pushButton_SaveConfig;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QPushButton *pushButton_LoadImage;
    QPushButton *pushButton_DetectOnce;
    QCheckBox *checkBox_Render;
    QRadioButton *radioButton_First;
    QRadioButton *radioButton_Middle;
    QRadioButton *radioButton_Last;
    QLabel *label_25;
    QSpinBox *spinBox_Threshold;
    QLabel *label_26;
    QSpinBox *spinBox_Length;
    QLabel *label_27;
    QSpinBox *spinBox_Distance;
    QLabel *label_21;
    QSpinBox *spinBox_XOffset;
    QLabel *label_28;
    QSpinBox *spinBox_YOffset;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_10;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QLabel *label_29;
    QSpinBox *spinBox;
    QPushButton *pushButton_Connect;
    QLabel *label_Status;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *comboBox_CamNames;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Grab;
    QLabel *label_5;
    QSpinBox *spinBox_Exposure;
    QLabel *label_6;
    QSpinBox *spinBox_Gain;
    QRadioButton *radioButton_FreeRun;
    QLabel *label_10;
    QSpinBox *spinBox_Freq;
    QLabel *label_11;
    QSpinBox *spinBox_Height;
    QRadioButton *radioButton_External;
    QLabel *label_12;
    QSpinBox *spinBox_ImageCount;
    MyLabel *label_Image_Right;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName(QString::fromUtf8("DialogSettings"));
        DialogSettings->resize(1049, 843);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogSettings->setWindowIcon(icon);
        gridLayout_4 = new QGridLayout(DialogSettings);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_2 = new QGroupBox(DialogSettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(458, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_CamNames_Right = new QComboBox(groupBox_2);
        comboBox_CamNames_Right->setObjectName(QString::fromUtf8("comboBox_CamNames_Right"));

        gridLayout_2->addWidget(comboBox_CamNames_Right, 0, 0, 1, 4);

        pushButton_Open_Right = new QPushButton(groupBox_2);
        pushButton_Open_Right->setObjectName(QString::fromUtf8("pushButton_Open_Right"));
        pushButton_Open_Right->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(pushButton_Open_Right, 0, 4, 1, 1);

        pushButton_Grab_Right = new QPushButton(groupBox_2);
        pushButton_Grab_Right->setObjectName(QString::fromUtf8("pushButton_Grab_Right"));
        pushButton_Grab_Right->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(pushButton_Grab_Right, 0, 5, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(30, 16777215));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        spinBox_Exposure_Right = new QSpinBox(groupBox_2);
        spinBox_Exposure_Right->setObjectName(QString::fromUtf8("spinBox_Exposure_Right"));
        spinBox_Exposure_Right->setMinimumSize(QSize(60, 0));
        spinBox_Exposure_Right->setMinimum(0);
        spinBox_Exposure_Right->setMaximum(99);
        spinBox_Exposure_Right->setValue(0);

        gridLayout_2->addWidget(spinBox_Exposure_Right, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(30, 16777215));

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1);

        spinBox_Gain_Right = new QSpinBox(groupBox_2);
        spinBox_Gain_Right->setObjectName(QString::fromUtf8("spinBox_Gain_Right"));
        spinBox_Gain_Right->setMinimumSize(QSize(60, 0));
        spinBox_Gain_Right->setMaximum(99);

        gridLayout_2->addWidget(spinBox_Gain_Right, 1, 3, 1, 1);

        radioButton_FreeRun_Right = new QRadioButton(groupBox_2);
        radioButton_FreeRun_Right->setObjectName(QString::fromUtf8("radioButton_FreeRun_Right"));

        gridLayout_2->addWidget(radioButton_FreeRun_Right, 1, 4, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(30, 16777215));

        gridLayout_2->addWidget(label_14, 2, 0, 1, 1);

        spinBox_Freq_Right = new QSpinBox(groupBox_2);
        spinBox_Freq_Right->setObjectName(QString::fromUtf8("spinBox_Freq_Right"));
        spinBox_Freq_Right->setMinimumSize(QSize(60, 0));
        spinBox_Freq_Right->setReadOnly(true);
        spinBox_Freq_Right->setMinimum(1);
        spinBox_Freq_Right->setMaximum(51000);

        gridLayout_2->addWidget(spinBox_Freq_Right, 2, 1, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMaximumSize(QSize(30, 16777215));

        gridLayout_2->addWidget(label_15, 2, 2, 1, 1);

        spinBox_Height_Right = new QSpinBox(groupBox_2);
        spinBox_Height_Right->setObjectName(QString::fromUtf8("spinBox_Height_Right"));
        spinBox_Height_Right->setMinimumSize(QSize(60, 0));
        spinBox_Height_Right->setMinimum(32);
        spinBox_Height_Right->setMaximum(32000);

        gridLayout_2->addWidget(spinBox_Height_Right, 2, 3, 1, 1);

        radioButton_External_Right = new QRadioButton(groupBox_2);
        radioButton_External_Right->setObjectName(QString::fromUtf8("radioButton_External_Right"));

        gridLayout_2->addWidget(radioButton_External_Right, 2, 4, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMaximumSize(QSize(61, 16777215));

        gridLayout_2->addWidget(label_16, 3, 0, 1, 1);

        spinBox_ImageCount_Right = new QSpinBox(groupBox_2);
        spinBox_ImageCount_Right->setObjectName(QString::fromUtf8("spinBox_ImageCount_Right"));
        spinBox_ImageCount_Right->setMinimumSize(QSize(60, 0));
        spinBox_ImageCount_Right->setMinimum(1);
        spinBox_ImageCount_Right->setMaximum(200000);

        gridLayout_2->addWidget(spinBox_ImageCount_Right, 3, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 8, 0, 1, 1);

        groupBox_9 = new QGroupBox(DialogSettings);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setMaximumSize(QSize(458, 16777215));
        gridLayout_11 = new QGridLayout(groupBox_9);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        pushButton_LoadImage_Right = new QPushButton(groupBox_9);
        pushButton_LoadImage_Right->setObjectName(QString::fromUtf8("pushButton_LoadImage_Right"));

        gridLayout_11->addWidget(pushButton_LoadImage_Right, 0, 0, 1, 1);

        pushButton_DetectOnce_Right = new QPushButton(groupBox_9);
        pushButton_DetectOnce_Right->setObjectName(QString::fromUtf8("pushButton_DetectOnce_Right"));

        gridLayout_11->addWidget(pushButton_DetectOnce_Right, 0, 1, 1, 1);

        checkBox_Render_2 = new QCheckBox(groupBox_9);
        checkBox_Render_2->setObjectName(QString::fromUtf8("checkBox_Render_2"));
        checkBox_Render_2->setChecked(true);

        gridLayout_11->addWidget(checkBox_Render_2, 0, 2, 1, 1);

        radioButton_First_Right = new QRadioButton(groupBox_9);
        radioButton_First_Right->setObjectName(QString::fromUtf8("radioButton_First_Right"));
        radioButton_First_Right->setChecked(true);

        gridLayout_11->addWidget(radioButton_First_Right, 0, 3, 1, 1);

        radioButton_Middle_Right = new QRadioButton(groupBox_9);
        radioButton_Middle_Right->setObjectName(QString::fromUtf8("radioButton_Middle_Right"));

        gridLayout_11->addWidget(radioButton_Middle_Right, 0, 4, 1, 1);

        radioButton_Last_Right = new QRadioButton(groupBox_9);
        radioButton_Last_Right->setObjectName(QString::fromUtf8("radioButton_Last_Right"));

        gridLayout_11->addWidget(radioButton_Last_Right, 0, 5, 1, 1);

        label_30 = new QLabel(groupBox_9);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_11->addWidget(label_30, 1, 0, 1, 1);

        spinBox_Threshold_Right = new QSpinBox(groupBox_9);
        spinBox_Threshold_Right->setObjectName(QString::fromUtf8("spinBox_Threshold_Right"));
        spinBox_Threshold_Right->setMaximum(255);
        spinBox_Threshold_Right->setValue(10);

        gridLayout_11->addWidget(spinBox_Threshold_Right, 1, 1, 1, 1);

        label_31 = new QLabel(groupBox_9);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_11->addWidget(label_31, 1, 2, 1, 1);

        spinBox_Length_Right = new QSpinBox(groupBox_9);
        spinBox_Length_Right->setObjectName(QString::fromUtf8("spinBox_Length_Right"));
        spinBox_Length_Right->setMinimum(1);
        spinBox_Length_Right->setMaximum(200);
        spinBox_Length_Right->setValue(50);

        gridLayout_11->addWidget(spinBox_Length_Right, 1, 3, 1, 1);

        label_32 = new QLabel(groupBox_9);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_11->addWidget(label_32, 1, 4, 1, 1);

        spinBox_Distance_Right = new QSpinBox(groupBox_9);
        spinBox_Distance_Right->setObjectName(QString::fromUtf8("spinBox_Distance_Right"));
        spinBox_Distance_Right->setMinimum(1);
        spinBox_Distance_Right->setMaximum(200);
        spinBox_Distance_Right->setValue(20);

        gridLayout_11->addWidget(spinBox_Distance_Right, 1, 5, 1, 1);

        label_22 = new QLabel(groupBox_9);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_11->addWidget(label_22, 2, 2, 1, 1);

        spinBox_XOffset_Right = new QSpinBox(groupBox_9);
        spinBox_XOffset_Right->setObjectName(QString::fromUtf8("spinBox_XOffset_Right"));
        spinBox_XOffset_Right->setMinimum(50);
        spinBox_XOffset_Right->setMaximum(500);

        gridLayout_11->addWidget(spinBox_XOffset_Right, 2, 3, 1, 1);

        label_33 = new QLabel(groupBox_9);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_11->addWidget(label_33, 2, 4, 1, 1);

        spinBox_YOffset_Right = new QSpinBox(groupBox_9);
        spinBox_YOffset_Right->setObjectName(QString::fromUtf8("spinBox_YOffset_Right"));
        spinBox_YOffset_Right->setMinimum(50);
        spinBox_YOffset_Right->setMaximum(500);

        gridLayout_11->addWidget(spinBox_YOffset_Right, 2, 5, 1, 1);


        gridLayout_4->addWidget(groupBox_9, 6, 0, 1, 1);

        groupBox_4 = new QGroupBox(DialogSettings);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(458, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEdit_SavePath = new QLineEdit(groupBox_4);
        lineEdit_SavePath->setObjectName(QString::fromUtf8("lineEdit_SavePath"));
        lineEdit_SavePath->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_SavePath, 0, 0, 1, 1);

        pushButton_BrowseSavePath = new QPushButton(groupBox_4);
        pushButton_BrowseSavePath->setObjectName(QString::fromUtf8("pushButton_BrowseSavePath"));
        pushButton_BrowseSavePath->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(pushButton_BrowseSavePath, 0, 1, 1, 1);

        lineEdit_SavePath_Right = new QLineEdit(groupBox_4);
        lineEdit_SavePath_Right->setObjectName(QString::fromUtf8("lineEdit_SavePath_Right"));
        lineEdit_SavePath_Right->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_SavePath_Right, 1, 0, 1, 1);

        pushButton_BrowseSavePath_2 = new QPushButton(groupBox_4);
        pushButton_BrowseSavePath_2->setObjectName(QString::fromUtf8("pushButton_BrowseSavePath_2"));
        pushButton_BrowseSavePath_2->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(pushButton_BrowseSavePath_2, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 3, 0, 1, 1);

        label_Image = new MyLabel(DialogSettings);
        label_Image->setObjectName(QString::fromUtf8("label_Image"));
        label_Image->setStyleSheet(QString::fromUtf8("border-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout_4->addWidget(label_Image, 0, 1, 4, 1);

        groupBox_7 = new QGroupBox(DialogSettings);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMaximumSize(QSize(458, 16777215));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(54, 16777215));

        gridLayout_8->addWidget(label_8, 0, 0, 1, 1);

        spinBox_Speed = new QSpinBox(groupBox_7);
        spinBox_Speed->setObjectName(QString::fromUtf8("spinBox_Speed"));
        spinBox_Speed->setMaximumSize(QSize(200, 16777215));
        spinBox_Speed->setMinimum(500);
        spinBox_Speed->setMaximum(100000);

        gridLayout_8->addWidget(spinBox_Speed, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(54, 16777215));

        gridLayout_8->addWidget(label_13, 0, 2, 1, 1);

        comboBox_SysType = new QComboBox(groupBox_7);
        comboBox_SysType->setObjectName(QString::fromUtf8("comboBox_SysType"));

        gridLayout_8->addWidget(comboBox_SysType, 0, 3, 1, 1);

        pushButton_SaveConfig = new QPushButton(groupBox_7);
        pushButton_SaveConfig->setObjectName(QString::fromUtf8("pushButton_SaveConfig"));
        pushButton_SaveConfig->setMinimumSize(QSize(61, 0));
        pushButton_SaveConfig->setMaximumSize(QSize(61, 16777215));

        gridLayout_8->addWidget(pushButton_SaveConfig, 0, 4, 1, 1);


        gridLayout_4->addWidget(groupBox_7, 4, 0, 1, 1);

        groupBox_6 = new QGroupBox(DialogSettings);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMaximumSize(QSize(458, 16777215));
        gridLayout_9 = new QGridLayout(groupBox_6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pushButton_LoadImage = new QPushButton(groupBox_6);
        pushButton_LoadImage->setObjectName(QString::fromUtf8("pushButton_LoadImage"));

        gridLayout_9->addWidget(pushButton_LoadImage, 0, 0, 1, 1);

        pushButton_DetectOnce = new QPushButton(groupBox_6);
        pushButton_DetectOnce->setObjectName(QString::fromUtf8("pushButton_DetectOnce"));

        gridLayout_9->addWidget(pushButton_DetectOnce, 0, 1, 1, 1);

        checkBox_Render = new QCheckBox(groupBox_6);
        checkBox_Render->setObjectName(QString::fromUtf8("checkBox_Render"));
        checkBox_Render->setChecked(true);

        gridLayout_9->addWidget(checkBox_Render, 0, 2, 1, 1);

        radioButton_First = new QRadioButton(groupBox_6);
        radioButton_First->setObjectName(QString::fromUtf8("radioButton_First"));
        radioButton_First->setChecked(true);

        gridLayout_9->addWidget(radioButton_First, 0, 3, 1, 1);

        radioButton_Middle = new QRadioButton(groupBox_6);
        radioButton_Middle->setObjectName(QString::fromUtf8("radioButton_Middle"));

        gridLayout_9->addWidget(radioButton_Middle, 0, 4, 1, 1);

        radioButton_Last = new QRadioButton(groupBox_6);
        radioButton_Last->setObjectName(QString::fromUtf8("radioButton_Last"));

        gridLayout_9->addWidget(radioButton_Last, 0, 5, 1, 1);

        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_9->addWidget(label_25, 1, 0, 1, 1);

        spinBox_Threshold = new QSpinBox(groupBox_6);
        spinBox_Threshold->setObjectName(QString::fromUtf8("spinBox_Threshold"));
        spinBox_Threshold->setMaximum(255);
        spinBox_Threshold->setValue(10);

        gridLayout_9->addWidget(spinBox_Threshold, 1, 1, 1, 1);

        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_9->addWidget(label_26, 1, 2, 1, 1);

        spinBox_Length = new QSpinBox(groupBox_6);
        spinBox_Length->setObjectName(QString::fromUtf8("spinBox_Length"));
        spinBox_Length->setMinimum(1);
        spinBox_Length->setMaximum(200);
        spinBox_Length->setValue(50);

        gridLayout_9->addWidget(spinBox_Length, 1, 3, 1, 1);

        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_9->addWidget(label_27, 1, 4, 1, 1);

        spinBox_Distance = new QSpinBox(groupBox_6);
        spinBox_Distance->setObjectName(QString::fromUtf8("spinBox_Distance"));
        spinBox_Distance->setMinimum(1);
        spinBox_Distance->setMaximum(200);
        spinBox_Distance->setValue(20);

        gridLayout_9->addWidget(spinBox_Distance, 1, 5, 1, 1);

        label_21 = new QLabel(groupBox_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_9->addWidget(label_21, 2, 2, 1, 1);

        spinBox_XOffset = new QSpinBox(groupBox_6);
        spinBox_XOffset->setObjectName(QString::fromUtf8("spinBox_XOffset"));
        spinBox_XOffset->setMinimum(50);
        spinBox_XOffset->setMaximum(500);

        gridLayout_9->addWidget(spinBox_XOffset, 2, 3, 1, 1);

        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_9->addWidget(label_28, 2, 4, 1, 1);

        spinBox_YOffset = new QSpinBox(groupBox_6);
        spinBox_YOffset->setObjectName(QString::fromUtf8("spinBox_YOffset"));
        spinBox_YOffset->setMinimum(50);
        spinBox_YOffset->setMaximum(500);

        gridLayout_9->addWidget(spinBox_YOffset, 2, 5, 1, 1);


        gridLayout_4->addWidget(groupBox_6, 5, 0, 1, 1);

        groupBox_8 = new QGroupBox(DialogSettings);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setMaximumSize(QSize(458, 16777215));
        gridLayout_10 = new QGridLayout(groupBox_8);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        lineEdit_IP = new QLineEdit(groupBox_8);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));

        gridLayout_10->addWidget(lineEdit_IP, 0, 0, 1, 1);

        lineEdit_Port = new QLineEdit(groupBox_8);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));
        lineEdit_Port->setMinimumSize(QSize(71, 0));
        lineEdit_Port->setMaximumSize(QSize(71, 16777215));

        gridLayout_10->addWidget(lineEdit_Port, 0, 1, 1, 1);

        label_29 = new QLabel(groupBox_8);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_10->addWidget(label_29, 0, 2, 1, 1);

        spinBox = new QSpinBox(groupBox_8);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setValue(3);

        gridLayout_10->addWidget(spinBox, 0, 3, 1, 1);

        pushButton_Connect = new QPushButton(groupBox_8);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        pushButton_Connect->setMinimumSize(QSize(50, 0));
        pushButton_Connect->setMaximumSize(QSize(50, 16777215));

        gridLayout_10->addWidget(pushButton_Connect, 0, 4, 1, 1);

        label_Status = new QLabel(groupBox_8);
        label_Status->setObjectName(QString::fromUtf8("label_Status"));
        label_Status->setMinimumSize(QSize(21, 21));
        label_Status->setMaximumSize(QSize(21, 21));
        label_Status->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        gridLayout_10->addWidget(label_Status, 0, 5, 1, 1);


        gridLayout_4->addWidget(groupBox_8, 7, 0, 1, 1);

        groupBox = new QGroupBox(DialogSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(458, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_CamNames = new QComboBox(groupBox);
        comboBox_CamNames->setObjectName(QString::fromUtf8("comboBox_CamNames"));

        gridLayout->addWidget(comboBox_CamNames, 0, 0, 1, 4);

        pushButton_Open = new QPushButton(groupBox);
        pushButton_Open->setObjectName(QString::fromUtf8("pushButton_Open"));
        pushButton_Open->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_Open, 0, 4, 1, 1);

        pushButton_Grab = new QPushButton(groupBox);
        pushButton_Grab->setObjectName(QString::fromUtf8("pushButton_Grab"));
        pushButton_Grab->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_Grab, 0, 5, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        spinBox_Exposure = new QSpinBox(groupBox);
        spinBox_Exposure->setObjectName(QString::fromUtf8("spinBox_Exposure"));
        spinBox_Exposure->setMinimumSize(QSize(60, 0));
        spinBox_Exposure->setMinimum(0);
        spinBox_Exposure->setMaximum(99);
        spinBox_Exposure->setValue(0);

        gridLayout->addWidget(spinBox_Exposure, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        spinBox_Gain = new QSpinBox(groupBox);
        spinBox_Gain->setObjectName(QString::fromUtf8("spinBox_Gain"));
        spinBox_Gain->setMinimumSize(QSize(60, 0));
        spinBox_Gain->setMaximum(99);

        gridLayout->addWidget(spinBox_Gain, 1, 3, 1, 1);

        radioButton_FreeRun = new QRadioButton(groupBox);
        radioButton_FreeRun->setObjectName(QString::fromUtf8("radioButton_FreeRun"));

        gridLayout->addWidget(radioButton_FreeRun, 1, 4, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(label_10, 2, 0, 1, 1);

        spinBox_Freq = new QSpinBox(groupBox);
        spinBox_Freq->setObjectName(QString::fromUtf8("spinBox_Freq"));
        spinBox_Freq->setMinimumSize(QSize(60, 0));
        spinBox_Freq->setReadOnly(true);
        spinBox_Freq->setMinimum(1);
        spinBox_Freq->setMaximum(51000);

        gridLayout->addWidget(spinBox_Freq, 2, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(label_11, 2, 2, 1, 1);

        spinBox_Height = new QSpinBox(groupBox);
        spinBox_Height->setObjectName(QString::fromUtf8("spinBox_Height"));
        spinBox_Height->setMinimumSize(QSize(60, 0));
        spinBox_Height->setMinimum(32);
        spinBox_Height->setMaximum(32000);

        gridLayout->addWidget(spinBox_Height, 2, 3, 1, 1);

        radioButton_External = new QRadioButton(groupBox);
        radioButton_External->setObjectName(QString::fromUtf8("radioButton_External"));

        gridLayout->addWidget(radioButton_External, 2, 4, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(61, 16777215));

        gridLayout->addWidget(label_12, 3, 0, 1, 1);

        spinBox_ImageCount = new QSpinBox(groupBox);
        spinBox_ImageCount->setObjectName(QString::fromUtf8("spinBox_ImageCount"));
        spinBox_ImageCount->setMinimumSize(QSize(60, 0));
        spinBox_ImageCount->setMinimum(1);
        spinBox_ImageCount->setMaximum(200000);

        gridLayout->addWidget(spinBox_ImageCount, 3, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 2, 1);

        label_Image_Right = new MyLabel(DialogSettings);
        label_Image_Right->setObjectName(QString::fromUtf8("label_Image_Right"));
        label_Image_Right->setMinimumSize(QSize(362, 362));
        label_Image_Right->setStyleSheet(QString::fromUtf8("border-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout_4->addWidget(label_Image_Right, 5, 1, 3, 1);


        retranslateUi(DialogSettings);
        QObject::connect(pushButton_Connect, SIGNAL(clicked()), DialogSettings, SLOT(ConnectToServer()));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetHeartBeat(int)));
        QObject::connect(spinBox_Speed, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetSpeed(int)));
        QObject::connect(pushButton_SaveConfig, SIGNAL(clicked()), DialogSettings, SLOT(SaveConfig()));
        QObject::connect(pushButton_Open, SIGNAL(clicked()), DialogSettings, SLOT(OpenCamera()));
        QObject::connect(pushButton_Grab, SIGNAL(clicked()), DialogSettings, SLOT(CameraGrab()));
        QObject::connect(pushButton_BrowseSavePath, SIGNAL(clicked()), DialogSettings, SLOT(BrowseSaveImagePath()));
        QObject::connect(pushButton_LoadImage, SIGNAL(clicked()), DialogSettings, SLOT(LoadImage()));
        QObject::connect(pushButton_DetectOnce, SIGNAL(clicked()), DialogSettings, SLOT(DetectOnce()));
        QObject::connect(spinBox_Exposure, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetCameraExposure(int)));
        QObject::connect(spinBox_Gain, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetCameraGain(int)));
        QObject::connect(spinBox_Freq, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetCameraFreq(int)));
        QObject::connect(spinBox_Height, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetCameraHeight(int)));
        QObject::connect(spinBox_ImageCount, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetImageCount(int)));
        QObject::connect(checkBox_Render, SIGNAL(clicked(bool)), DialogSettings, SLOT(ShowRender(bool)));
        QObject::connect(spinBox_Threshold, SIGNAL(valueChanged(int)), DialogSettings, SLOT(SetThreshold(int)));
        QObject::connect(pushButton_LoadImage_Right, SIGNAL(clicked()), DialogSettings, SLOT(RightLoadImage()));
        QObject::connect(pushButton_DetectOnce_Right, SIGNAL(clicked()), DialogSettings, SLOT(RightDetectOnce()));
        QObject::connect(pushButton_Open_Right, SIGNAL(clicked()), DialogSettings, SLOT(RightOpenCamera()));
        QObject::connect(pushButton_Grab_Right, SIGNAL(clicked()), DialogSettings, SLOT(RightDetectOnce()));

        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QCoreApplication::translate("DialogSettings", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DialogSettings", "\345\217\263\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        pushButton_Open_Right->setText(QCoreApplication::translate("DialogSettings", "\346\211\223\345\274\200\347\233\270\346\234\272", nullptr));
        pushButton_Grab_Right->setText(QCoreApplication::translate("DialogSettings", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        label_7->setText(QCoreApplication::translate("DialogSettings", "\346\233\235\345\205\211", nullptr));
        label_9->setText(QCoreApplication::translate("DialogSettings", "\345\242\236\347\233\212", nullptr));
        radioButton_FreeRun_Right->setText(QCoreApplication::translate("DialogSettings", "\350\207\252\347\224\261\351\207\207\351\233\206", nullptr));
        label_14->setText(QCoreApplication::translate("DialogSettings", "\350\241\214\351\242\221", nullptr));
        label_15->setText(QCoreApplication::translate("DialogSettings", "\350\241\214\351\253\230", nullptr));
        radioButton_External_Right->setText(QCoreApplication::translate("DialogSettings", "\347\241\254\350\247\246\345\217\221", nullptr));
        label_16->setText(QCoreApplication::translate("DialogSettings", "\345\233\276\345\203\217\346\225\260\351\207\217", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("DialogSettings", "\345\217\263\347\233\270\346\234\272\346\243\200\346\265\213\345\217\202\346\225\260", nullptr));
        pushButton_LoadImage_Right->setText(QCoreApplication::translate("DialogSettings", "\345\212\240\350\275\275\345\233\276\345\203\217", nullptr));
        pushButton_DetectOnce_Right->setText(QCoreApplication::translate("DialogSettings", "\346\243\200\346\265\213\344\270\200\346\254\241", nullptr));
        checkBox_Render_2->setText(QCoreApplication::translate("DialogSettings", "\346\270\262\346\237\223\345\233\276", nullptr));
        radioButton_First_Right->setText(QCoreApplication::translate("DialogSettings", "\347\254\254\344\270\200\345\274\240", nullptr));
        radioButton_Middle_Right->setText(QCoreApplication::translate("DialogSettings", "\344\270\255\351\227\264\345\233\276", nullptr));
        radioButton_Last_Right->setText(QCoreApplication::translate("DialogSettings", "\346\234\200\345\220\216\344\270\200\345\274\240", nullptr));
        label_30->setText(QCoreApplication::translate("DialogSettings", "\347\201\260\345\272\246\345\200\274", nullptr));
        label_31->setText(QCoreApplication::translate("DialogSettings", "\347\274\272\351\231\267\351\225\277\345\272\246", nullptr));
        label_32->setText(QCoreApplication::translate("DialogSettings", "\350\276\271\347\274\230\350\267\235\347\246\273", nullptr));
        label_22->setText(QCoreApplication::translate("DialogSettings", "X\345\201\217\347\247\273", nullptr));
        label_33->setText(QCoreApplication::translate("DialogSettings", "Y\345\201\217\347\247\273", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("DialogSettings", "\346\225\260\346\215\256\345\255\230\346\241\243", nullptr));
        lineEdit_SavePath->setPlaceholderText(QCoreApplication::translate("DialogSettings", "\345\267\246\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        pushButton_BrowseSavePath->setText(QCoreApplication::translate("DialogSettings", "\346\211\223\345\274\200\350\267\257\345\276\204", nullptr));
        lineEdit_SavePath_Right->setPlaceholderText(QCoreApplication::translate("DialogSettings", "\345\217\263\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        pushButton_BrowseSavePath_2->setText(QCoreApplication::translate("DialogSettings", "\346\211\223\345\274\200\350\267\257\345\276\204", nullptr));
        label_Image->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("DialogSettings", "\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        label_8->setText(QCoreApplication::translate("DialogSettings", "\345\271\263\345\217\260\351\200\237\345\272\246", nullptr));
        spinBox_Speed->setSuffix(QCoreApplication::translate("DialogSettings", "mm/s", nullptr));
        label_13->setText(QCoreApplication::translate("DialogSettings", "\347\263\273\347\273\237\346\250\241\345\274\217", nullptr));
        pushButton_SaveConfig->setText(QCoreApplication::translate("DialogSettings", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("DialogSettings", "\345\267\246\347\233\270\346\234\272\346\243\200\346\265\213\345\217\202\346\225\260", nullptr));
        pushButton_LoadImage->setText(QCoreApplication::translate("DialogSettings", "\345\212\240\350\275\275\345\233\276\345\203\217", nullptr));
        pushButton_DetectOnce->setText(QCoreApplication::translate("DialogSettings", "\346\243\200\346\265\213\344\270\200\346\254\241", nullptr));
        checkBox_Render->setText(QCoreApplication::translate("DialogSettings", "\346\270\262\346\237\223\345\233\276", nullptr));
        radioButton_First->setText(QCoreApplication::translate("DialogSettings", "\347\254\254\344\270\200\345\274\240", nullptr));
        radioButton_Middle->setText(QCoreApplication::translate("DialogSettings", "\344\270\255\351\227\264\345\233\276", nullptr));
        radioButton_Last->setText(QCoreApplication::translate("DialogSettings", "\346\234\200\345\220\216\344\270\200\345\274\240", nullptr));
        label_25->setText(QCoreApplication::translate("DialogSettings", "\347\201\260\345\272\246\345\200\274", nullptr));
        label_26->setText(QCoreApplication::translate("DialogSettings", "\347\274\272\351\231\267\351\225\277\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("DialogSettings", "\350\276\271\347\274\230\350\267\235\347\246\273", nullptr));
        label_21->setText(QCoreApplication::translate("DialogSettings", "X\345\201\217\347\247\273", nullptr));
        label_28->setText(QCoreApplication::translate("DialogSettings", "Y\345\201\217\347\247\273", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("DialogSettings", "\351\200\232\350\256\257", nullptr));
        lineEdit_IP->setPlaceholderText(QCoreApplication::translate("DialogSettings", "\346\234\215\345\212\241\347\253\257IP", nullptr));
        lineEdit_Port->setPlaceholderText(QCoreApplication::translate("DialogSettings", "\347\253\257\345\217\243\345\217\267", nullptr));
        label_29->setText(QCoreApplication::translate("DialogSettings", "\345\277\203\350\267\263\351\227\264\351\232\224", nullptr));
        spinBox->setSuffix(QCoreApplication::translate("DialogSettings", "s", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("DialogSettings", "\350\277\236\346\216\245", nullptr));
        label_Status->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("DialogSettings", "\345\267\246\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        pushButton_Open->setText(QCoreApplication::translate("DialogSettings", "\346\211\223\345\274\200\347\233\270\346\234\272", nullptr));
        pushButton_Grab->setText(QCoreApplication::translate("DialogSettings", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        label_5->setText(QCoreApplication::translate("DialogSettings", "\346\233\235\345\205\211", nullptr));
        label_6->setText(QCoreApplication::translate("DialogSettings", "\345\242\236\347\233\212", nullptr));
        radioButton_FreeRun->setText(QCoreApplication::translate("DialogSettings", "\350\207\252\347\224\261\351\207\207\351\233\206", nullptr));
        label_10->setText(QCoreApplication::translate("DialogSettings", "\350\241\214\351\242\221", nullptr));
        label_11->setText(QCoreApplication::translate("DialogSettings", "\350\241\214\351\253\230", nullptr));
        radioButton_External->setText(QCoreApplication::translate("DialogSettings", "\347\241\254\350\247\246\345\217\221", nullptr));
        label_12->setText(QCoreApplication::translate("DialogSettings", "\345\233\276\345\203\217\346\225\260\351\207\217", nullptr));
        label_Image_Right->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERSETTING_H
