#include <windows.h>
#include "SaveImage.h"
#include "QFileInfoList"
#include "qdir.h"
#include "QDate"
#include "QDebug"

#define GB (1024*1024*1024)


CSaveImage::CSaveImage(QThread *parent /* = NULL */)
	:QThread(parent)
{
	m_bStop = false;
}

void CSaveImage::StopThread()
{
	m_bStop = true;
}

void CSaveImage::SetImageInfo(s_ImageInfo ImageInfo)
{
	m_Mutex.lock();
	m_ImageInfos.push_back(ImageInfo);
	m_Mutex.unlock();
}

quint64 CSaveImage::GetDiskFreeSpace(QString DiskName)
{
	qDebug() << "GetDiskFreeSpace";
	//iDriver为盘符(例如"C\")
	LPCWSTR strDriver = (LPCWSTR)DiskName.utf16();
	ULARGE_INTEGER freeDiskSpaceAvailable, totalDiskSpace, totalFreeDiskSpace;
	//调用函数获取磁盘参数(单位为字节Byte),转化为GB，需要除以(1024*1024*1024)
	GetDiskFreeSpaceEx(strDriver, &freeDiskSpaceAvailable, &totalDiskSpace, &totalFreeDiskSpace);
	return (quint64)freeDiskSpaceAvailable.QuadPart / GB;
}

void CSaveImage::DeleteEarliestDir(QString Path)
{
	qDebug() << "DeleteEarliestDir:"<<Path;
	QDir dir(Path);
	if (!dir.exists())
	{
		qDebug() << QString::fromLocal8Bit("文件目录不存在:") << Path;
		return;
	}
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::DirsFirst);//文件夹排在前面
	QFileInfoList list = dir.entryInfoList();

	QDate EarliestDate = QDate::currentDate();
	QString EarliestDir;
	for (int i = 0; i < list.size(); ++i)
	{
		QString CurPath = list.at(i).absoluteFilePath();
		QDate CurDate = QDate::fromString(CurPath.right(10),"yyyy-MM-dd");
		if (CurDate < EarliestDate)
		{
			EarliestDate = CurDate;
			EarliestDir = CurPath;
		}
	}
	QDir DeleteDir;
	DeleteDir.setPath(EarliestDir);
	DeleteDir.removeRecursively();
}

void CSaveImage::SaveImage(s_ImageInfo &ImageInfo)
{
	QString DiskName = ImageInfo.SavePath.left(3);
	quint64 FreeSpace = GetDiskFreeSpace(DiskName);
	if (FreeSpace < 3)
	{
		qDebug() << "Free Space < 3G,Current free space = " << FreeSpace;
		DeleteEarliestDir(ImageInfo.SavePath);
	}
	QString SavePath = ImageInfo.SavePath + "/" + ImageInfo.MiddleDir;
	QDir dir(SavePath);
	if (!dir.exists(SavePath))
	{
		dir.mkpath(SavePath);
	}
	SavePath += "/" + ImageInfo.FileName;
	QByteArray ba = SavePath.toLocal8Bit();
	char *file = ba.data();
	bool rv = imwrite(file, ImageInfo.image);
	if (rv)
	{
		qDebug() << "save image success:" << file;
	}
	else
	{
		qDebug() << "save image failed:" << file;
	}
}

void CSaveImage::run()
{
	while (1)
	{
		if (m_bStop)
		{
			break;
		}
		if (m_ImageInfos.size() > 0)
		{
			m_Mutex.lock();
			s_ImageInfo info = m_ImageInfos.dequeue();
			m_Mutex.unlock();
			SaveImage(info);
		}
		else
		{
			Sleep(100);
		}
	}
}