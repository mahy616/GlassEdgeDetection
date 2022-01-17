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
	QDockWidget *m_ResultDetials;
	QListView *m_ListView;
	QStandardItemModel *m_LogModel;
	bool m_bStart;
	Mat m_LeftImage;
	Mat m_RightImage;
	int m_LeftIndex;
	int m_RightIndex;
	bool m_bLeftOK;
	bool m_bRightOK;
	QVector<MyLabel *> m_LeftWindows;
	QVector<MyLabel *> m_RightWindows;
	QVector<QLabel *> m_LeftResults;
	QVector<QLabel *> m_RightResults;
private:
	void InitVariables();
	void InitConnections();
	QImage MattoQImage(Mat image);
	void InitWindows();
	void InitResultDetials();
	void SaveLeftImage(Mat image,bool bOK);
	void SaveRightImage(Mat image, bool bOK);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
private slots:
	void StartDetection();
	void StopDetection();
	void OpenSetting();
	void ReceiveCameraImage(Mat img, e_CameraType type,bool bOK);
	void ReceiveParameterCloseEvent();
};
