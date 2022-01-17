#pragma once
#include "QThread"
#include "QMutex"
#include "QQueue"
#include "ParametersManager.h"
#include "segmentation.h"
#include "find_contour.h"

using namespace smartmore;

class CDetectAlgo :public QThread
{
	Q_OBJECT
public:
	CDetectAlgo(QThread *parent = NULL);
	bool GetInitStatus() { return m_bInitSuccess; }
	void InitAlgo();
	void InitParameters();
	Mat RunAlgoOffLine(Mat image, QString type, bool &bok);
	void RunAlgo(Mat image,int index, e_CameraType type);
	void StopThread();
private:
	bool m_bStop;
	bool m_bInitSuccess;
	QQueue<s_AlgoImageInfo> m_ImageList;
	QMutex m_Mutex;
	smartmore::HuikeAlgo algo;
	smartmore::HuiKeSegModule sdk;
	EdgeConfig x_First_config;
	EdgeConfig x_Last_config;

	EdgeConfig y_First_config;
	EdgeConfig y_Last_config;
	EdgeConfig y_Middle_config;

	EdgeConfig x_First_config_Right;
	EdgeConfig x_Last_config_Right;

	EdgeConfig y_First_config_Right;
	EdgeConfig y_Last_config_Right;
	EdgeConfig y_Middle_config_Right;

private:
	void run();
signals:
	void SendAlgoResult(Mat originalImage,Mat renderImage,int index,bool bOK);
};
