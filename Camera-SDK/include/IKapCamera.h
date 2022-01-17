#pragma once
#include <qstring.h>
#include <qdebug.h>
#include <IKapC.h>
#include <qvector.h>
#include <qstringlist.h>
#include <opencv2/opencv.hpp>
#include <qobject.h>
#include <QDateTime>

struct IKapInfo
{
	uint32_t index;
	QString serialNum;
	QString definedName;
	QString deviceClass;
};

enum ETriggerMode
{
	On,
	Off
};

enum ETriggerSelector
{
	LineStart,
	FrameActive,
	FrameStart
};

enum ETriggerSource
{
	Line1,
	Line2,
	Line3,
	Software,
	RotaryEncoder1
};

class IKapCamera : public QObject
{
	Q_OBJECT
public:
	IKapCamera(QObject *parent = NULL);
	~IKapCamera();
	bool openDevice(QString, uint32_t);
	bool closeDevice();
	bool enumDeviceInfo(QStringList&);

	bool getExposure(double*, double*, double*);
	bool setExposure(double);

	bool getGain(double*, double*, double*);
	bool setGain(double);

	bool getAcquisitionLineRate(double*,double*,double*);
	bool setAcquisitionLineRate(double);

	bool setHeight(int64_t);
	bool getHeight(int64_t*);

	bool SetFreeRun();
	bool SetSoftTrigger();
	bool SetExternalTrigger(int);

	bool softwareTriggerOnce();

	bool startGrab();
	bool stopGrab();

	bool loadCameraConfigFile(char *fileName);
	bool saveCameraConfigFile(char *fileName);

signals:
	void sendCameraImage(cv::Mat &image);

private:
	bool createStreamAndBuffer();
	bool configureStream();

	bool setTriggerMode(ETriggerMode);
	bool setTriggerSource(ETriggerSource, int);
	bool setTriggerSelector(ETriggerSelector);

private:
	static void IKAPC_CC cbStartOfStream(uint32_t eventType, void* pContext);
	static void IKAPC_CC cbEndOfStream(uint32_t eventType, void* pContext);
	static void IKAPC_CC cbOnEndOfFrame(uint32_t eventType, void* pContext);
	static void IKAPC_CC cbOnTimeOut(uint32_t eventType, void* pContext);
	static void IKAPC_CC cbOnFrameLost(uint32_t eventType, void* pContext);

private:
	QVector<IKapInfo> m_AllDevInfo;
	bool m_bDeviceOpen = false;
	bool m_bDeviceGrab = false;

	uint32_t  m_nFormat = ITKBUFFER_VAL_FORMAT_MONO8;
	ITKDEVICE m_hCamera = NULL;
	ITKSTREAM m_hStream = NULL;
	ITKBUFFER m_hBuffer = NULL;
	char* m_hData = NULL;
	int64_t		m_nWidth = 0;																	/* Image width.								*/
	int64_t		m_nHeight = 0;

	uint32_t m_nTimeOut;

	ETriggerMode m_Mode;

	QDateTime m_start, m_end;
};

