#pragma once

#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QDir>
#include <QQueue>
#include <qmutex.h>
#include "opencv2/opencv.hpp"
#include "qdebug.h"
using namespace std;
using namespace cv;

//#define SYSTEM_DEBUG
typedef enum
{
	CAMERA_LEFT,     // 上面-左侧相机
	CAMERA_RIGHT,    // 上面-右侧相机

}e_CameraType;
typedef struct
{
	Mat image;
	int index;
	e_CameraType type;
}s_AlgoImageInfo;



class CParametersManager :public QObject
{
public:
	static CParametersManager *GetInstance();

	void SetImageCount(int value, e_CameraType type);
	int GetImageCount(e_CameraType type);

	void SetCameraHeight(int value);
	int GetCameraHeight();

	void SetSpeed(int Speed) { m_Speed = Speed; }
	int GetSpeed() { return m_Speed; }

	void SetSavePath(QString SavePath) { m_SavePath = SavePath; }
	QString GetSavePath() { return m_SavePath; }

	void SetXOffset(QString mode, int value);
	int GetXOffset(QString mode);

	void SetYOffset(QString mode, int value);
	int GetYOffset(QString mode);

	void SetGrayThreshold(int value);
	int GetGrayThreshold();

	void SetLength(int value);
	int GetLength();

	void SetDistance(int value);
	int GetDistance();

	void SetHeartBeat(int value) { m_HeartBeat = value; }
	int GetHeartBeat() { return m_HeartBeat; }
private:
	CParametersManager(QObject *parent = NULL);
	static CParametersManager *m_Instance;

	void InitVariables();
private:
	int m_ImageCount;
	int m_RightImageCount;
	int m_ImageHeight;
	int m_Speed;
	int m_XOffset_First;
	int m_XOffset_Last;
	int m_YOffset_First;
	int m_YOffset_Last;
	QString m_SavePath;
	int m_Threshold;
	int m_Length;
	int m_Distance;
	int m_HeartBeat;
};
