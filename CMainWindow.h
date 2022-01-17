#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QLabel>
#include <qlistview.h>
#include <QStandardItemModel>
#include <QMouseEvent>
#include "ui_CMainWindow.h"
#include "MyLabel.h"
#include "ParameterSettings.h"
#include "DataManager.h"

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow(QWidget *parent = Q_NULLPTR);
private:
	Ui::CMainWindowClass ui;
	CParamterSetting m_Parameter;
	QLabel *m_LeftResult;
	QLabel *m_RightResult;
	QDockWidget *m_LeftResultDetials;
	QDockWidget *m_RightResultDetials;
	QListView *m_ListView;
	QStandardItemModel *m_LogModel;
	QLabel *m_Label;
	int m_TotalCount;
	int m_SuccessCount;
	bool m_bStart;
	bool m_bLeftOK;
	bool m_bRightOK;
	QVector<QLabel *> m_LeftResults;
	QVector<QLabel *> m_RightResults;
	QVector<Mat> m_LeftImages;
	QVector<Mat> m_RightImages;
	QString m_PartNumber;
	QMap<e_CameraType, bool> m_Result;
private:
	void InitVariables();
	void InitConnections();
	QImage MattoQImage(Mat image);
	void InitResultDetials();
	void InitRightResultDetials();
	void RefreshResultDetials();
	void AddLog(QString log);
	void ProcessDetectionResult(bool bok);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
private slots:
	void StartDetection();
	void StopDetection();
	void OpenSetting();
	void OpenDataManager();
	void ReceiveAlgoImage(Mat RenderImage, e_CameraType Type,int index, bool bOK);
	void ReceiveParameterCloseEvent();
	void ReceivePartNumber(QString partNumber);
};
