#pragma once
#include <QThread>
#include <QQueue>
#include <QMutex>
#include "opencv2/opencv.hpp"
#include "qdebug.h"
using namespace std;
using namespace cv;

typedef struct
{
	QString SavePath; //保存目录
	QString MiddleDir;  //中间目录，DateTime/JPN
	QString FileName;    //文件名
	Mat image;
}s_ImageInfo;

typedef QQueue<s_ImageInfo> QImageInfos;

class CSaveImage :public QThread
{
	Q_OBJECT
public:
	CSaveImage(QThread *parent = NULL);
	void StopThread();
	void SetImageInfo(s_ImageInfo ImageInfo);
private:
	void SaveImage(s_ImageInfo &ImageInfo);
	quint64 GetDiskFreeSpace(QString DiskName);
	void DeleteEarliestDir(QString Path);
private:
	QImageInfos m_ImageInfos;
	QMutex m_Mutex;
	bool m_bStop;
private:
	void run();
};