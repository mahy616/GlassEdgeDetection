#include "IKapCamera.h"

IKapCamera::IKapCamera(QObject *parent /* = NULL */)
	:QObject(parent)
{
	ITKSTATUS res = ITKSTATUS_OK;
	res = ItkManInitialize();
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkManInitialize Fail";
	}
}

IKapCamera::~IKapCamera()
{
	ItkManTerminate();
}

bool IKapCamera::openDevice(QString CameraName, uint32_t _timeout)
{
	m_nTimeOut = _timeout;
	if(m_bDeviceOpen)
	{
		qDebug() << "Camera has opened";
		return false;
	}
	if (m_AllDevInfo.size() == 0)
	{
		qDebug() << "No Camera Exist";
		return false;
	}

	ITKSTATUS res = ITKSTATUS_INVALID_HANDLE;
	for (int i = 0; i < m_AllDevInfo.size(); i++)
	{
		QString Name = m_AllDevInfo[i].definedName + "_" + m_AllDevInfo[i].serialNum;
		if(CameraName == Name)
		{
			res = ItkDevOpen(i, ITKDEV_VAL_ACCESS_MODE_EXCLUSIVE, &m_hCamera);
			break;
		}
	}

	if (ITKSTATUS_OK != res)
	{
		qDebug() << "Open Camera [" << CameraName << " Failed";
		return false;
	}
	m_bDeviceOpen = true;
	return true;
}

#if 0
bool IKapCamera::openDeviceForSerialNum(QString _serialNum, uint32_t _timeout)
{
	m_nTimeOut = _timeout;
	if (m_bDeviceOpen)
	{
		qDebug() << "Camera has opened";
		return false;
	}
	if (m_AllDevInfo.size() == 0)
	{
		qDebug() << "No Camera Exist";
		return false;
	}
	ITKSTATUS res = ITKSTATUS_INVALID_HANDLE;
	for (int i = 0; i < m_AllDevInfo.size(); i++)
	{
		if (_serialNum == m_AllDevInfo[i].serialNum)
		{
			res = ItkDevOpen(i, ITKDEV_VAL_ACCESS_MODE_EXCLUSIVE, &m_hCamera);
			break;
		}
	}

	if (ITKSTATUS_OK != res)
	{
		qDebug() << "Open Camera [" << _serialNum << " Failed";
		return false;
	}
	m_bDeviceOpen = true;
	return true;
}
#endif

bool IKapCamera::closeDevice()
{
	if (!m_bDeviceOpen)
	{
		qDebug() << "Camera has closed";
		return false;
	}
	ITKSTATUS res = ITKSTATUS_OK;
	if (NULL == m_hStream)
	{
		qDebug() << "NULL == m_hStream";
		return false;
	}
	res = ItkDevClose(m_hCamera);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "Close Camera Failed";
		return false;
	}
	m_bDeviceOpen = false;
	return true;
}

bool IKapCamera::enumDeviceInfo(QStringList &CameraNames)
{
	m_AllDevInfo.clear();
	ITKSTATUS res = ITKSTATUS_OK;
	uint32_t numCameras = 0;
	qDebug() << "GetDeviceCount Start";
	res = ItkManGetDeviceCount(&numCameras);//枚举设备
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "GetDeviceCount Fail";
		return false;
	}
	if (numCameras == 0)
	{
		qDebug() << "No Device Founded";
		return false;
	}

	for (uint32_t i = 0; i < numCameras; i++)
	{
		qDebug() << " Device Size:" << numCameras<<endl;
		ITKDEV_INFO di;//相机信息结构体
		res = ItkManGetDeviceInfo(i, &di);//根据数量枚举得到的每个相机的信息
		if (ITKSTATUS_OK != res)
		{
			m_AllDevInfo.clear();
			qDebug() << "Check Index[" << i << "] ITKDEV_INFO Fail";
			return false;
		}
		QString Name = QString::fromLocal8Bit(di.UserDefinedName) + "_" + QString(di.SerialNumber);
		qDebug() << "Scan Camera Name:" << Name;
		CameraNames.push_back(Name);
		IKapInfo info = { i, di.SerialNumber ,QString::fromLocal8Bit(di.UserDefinedName), di.DeviceClass };
		m_AllDevInfo.append(info);
	}
	return true;
}

bool IKapCamera::getExposure(double* _max, double* _min, double* _current)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "ExposureTime", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature ExposureTime Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMax(hFeature, _max);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMax ExposureTime Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMin(hFeature, _min);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMin ExposureTime Failed";
		return false;
	}
	res = ItkDevFreeFeature(hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "FreeFeature ExposureTime Failed";
		return false;
	}

	res = ItkDevGetDouble(m_hCamera, "ExposureTime", _current);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "ItkDevGetDoubleMax ExposureTime Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setExposure(double _value)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}

	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "ExposureTime", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature ExposureTime Failed";
		return false;
	}
	res = ItkFeatureSetDouble(hFeature, _value);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "SetDouble ExposureTime Failed";
		return false;
	}
	res = ItkDevFreeFeature(hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "FreeFeature ExposureTime Failed";
		return false;
	}
	return true;
}

bool IKapCamera::getGain(double* _max, double* _min, double* _current)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "DigitalGain", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature DigitalGain Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMax(hFeature, _max);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMax DigitalGain Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMin(hFeature, _min);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMin DigitalGain Failed";
		return false;
	}
	res = ItkDevFreeFeature(hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "FreeFeature DigitalGain Failed";
		return false;
	}

	res = ItkDevGetDouble(m_hCamera, "DigitalGain", _current);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "ItkDevGetDoubleMax DigitalGain Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setGain(double _value)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}

	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "DigitalGain", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature DigitalGain Failed";
		return false;
	}
	res = ItkFeatureSetDouble(hFeature, _value);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "SetDouble DigitalGain Failed";
		return false;
	}
	res = ItkDevFreeFeature(hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "FreeFeature DigitalGain Failed";
		return false;
	}
	return true;
}

bool IKapCamera::getAcquisitionLineRate(double*_max, double*_min,double*_current)
{
	//AcquisitionLineRate
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}

	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "AcquisitionLineRate", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature AcquisitionLineRate Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMax(hFeature, _max);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMax AcquisitionLineRate Failed";
		return false;
	}
	res = ItkFeatureGetDoubleMin(hFeature, _min);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "GetDoubleMin AcquisitionLineRate Failed";
		return false;
	}
	res = ItkDevGetDouble(m_hCamera, "AcquisitionLineRate", _current);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "ItkDevGetDoubleMax AcquisitionLineRate Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setAcquisitionLineRate(double _value)
{
	//AcquisitionLineRate
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}

	ITKFEATURE hFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "AcquisitionLineRate", &hFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature AcquisitionLineRate Failed";
		return false;
	}
	res = ItkFeatureSetDouble(hFeature, _value);
	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "SetDouble AcquisitionLineRate Failed";
		return false;
	}

	if (ITKSTATUS_OK != res)
	{
		ItkDevFreeFeature(hFeature);
		qDebug() << "FreeFeature AcquisitionLineRate Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setHeight(int64_t _height)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKSTATUS res = ItkDevSetInt64(m_hCamera, "Height", _height);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "setHeight Failed";
		return false;
	}
	return true;
}

bool IKapCamera::getHeight(int64_t *_height)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKSTATUS res = ItkDevGetInt64(m_hCamera, "Height", _height);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "getHeight Failed";
		return false;
	}
	return true;
}

bool IKapCamera::SetFreeRun()
{
	return setTriggerMode(ETriggerMode::Off);
}

bool IKapCamera::SetSoftTrigger()
{
	bool bRet = setTriggerSelector(ETriggerSelector::FrameStart);
	if (!bRet)
		return false;
	bRet = setTriggerMode(ETriggerMode::On);
	if (!bRet)
		return false;
	return setTriggerSource(ETriggerSource::Software,1);
}

bool IKapCamera::SetExternalTrigger(int FrameCount)
{
	bool bRet = setTriggerSelector(ETriggerSelector::FrameActive);
	if (!bRet)
		return false;
	bRet = setTriggerMode(ETriggerMode::On);
	if (!bRet)
		return false;
	return setTriggerSource(ETriggerSource::Line3, FrameCount);
}

bool IKapCamera::setTriggerMode(ETriggerMode _mode)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKSTATUS res = ITKSTATUS_OK;
	switch (_mode)
	{
	case On:
		res = ItkDevFromString(m_hCamera, "TriggerMode", "On");
		m_Mode = ETriggerMode::On;
		break;
	case Off:
		res = ItkDevFromString(m_hCamera, "TriggerMode", "Off");
		m_Mode = ETriggerMode::Off;
		break;
	}
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "setTriggerMode Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setTriggerSource(ETriggerSource _source,int FrameCount)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKSTATUS res = ITKSTATUS_OK;
	switch (_source)
	{
	case Line1:
		res = ItkDevFromString(m_hCamera, "TriggerSource", "Line1");
		break;
	case Line2:
		res = ItkDevFromString(m_hCamera, "TriggerSource", "Line2");
		break;
	case Line3:
		res = ItkDevFromString(m_hCamera, "TriggerSource", "Line3");
		break;
	case Software:
		res = ItkDevFromString(m_hCamera, "TriggerSource", "Software");
		break;
	case RotaryEncoder1:
		res = ItkDevFromString(m_hCamera, "TriggerSource", "RotaryEncoder1");
		break;
	}
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "setTriggerSource Failed";
		return false;
	}
	printf("set TriggerFrameCount:%d\n", FrameCount);
	res = ItkDevSetInt64(m_hCamera, "TriggerFrameCount", FrameCount);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "TriggerFrameCount Failed";
		return false;
	}
	return true;
}

bool IKapCamera::setTriggerSelector(ETriggerSelector _selector)
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKSTATUS res = ITKSTATUS_OK;
	switch (_selector)
	{
	case LineStart:
		res = ItkDevFromString(m_hCamera, "TriggerSelector", "LineStart");
		break;
	case FrameActive:
		res = ItkDevFromString(m_hCamera, "TriggerSelector", "FrameActive");
		break;
	case FrameStart:
		res = ItkDevFromString(m_hCamera, "TriggerSelector", "FrameStart");
		break;
	}
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "setTriggerSelector Failed";
		return false;
	}
	return true;
}

bool IKapCamera::softwareTriggerOnce()
{
	m_start = QDateTime::currentDateTime();
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	ITKFEATURE itkFeature;
	ITKSTATUS res = ItkDevAllocFeature(m_hCamera, "TriggerSoftware", &itkFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature Failed";
		return false;
	}
	res = ItkFeatureExecuteCommand(itkFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature Failed";
		ItkDevFreeFeature(itkFeature);
		return false;
	}
	res = ItkDevFreeFeature(itkFeature);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocFeature Failed";
		return false;
	}
	return true;
}

bool IKapCamera::createStreamAndBuffer()
{
	if (NULL == m_hCamera)
	{
		qDebug() << "NULL == m_hCamera";
		return false;
	}
	
	uint32_t		streamCount = 0;															/*Stream count.							*/																	/* Image height.							*/
			/* Image format							*/
	int64_t		nImageSize = 0;															/* Image size									*/
	char				pixelFormat[16];															/* Image pixel format.					*/
	uint32_t		pixelFormatLen = 16;													/* Image pixel format length.	*/

	// Get stream count
	ITKSTATUS res = ITKSTATUS_OK;
	res = ItkDevGetStreamCount(m_hCamera, &streamCount);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevGetStreamCount Failed";
		return false;
	}
	if (streamCount == 0)
	{
		//ItkManTerminate();
		return false;
	}

	res = ItkDevGetInt64(m_hCamera, "Width", &m_nWidth);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevGetInt64 Width Failed";
		return false;
	}

	res = ItkDevGetInt64(m_hCamera, "Height", &m_nHeight);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevGetInt64 Height Failed";
		return false;
	}

	res = ItkDevToString(m_hCamera, "PixelFormat", pixelFormat, &pixelFormatLen);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevToString PixelFormat Failed";
		return false;
	}
	if (strcmp(pixelFormat, "Mono8") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_MONO8;
	else if (strcmp(pixelFormat, "Mono10") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_MONO10;
	else if (strcmp(pixelFormat, "Mono10Packed") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_MONO10PACKED;
	else if (strcmp(pixelFormat, "BayerGR8") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_BAYER_GR8;
	else if (strcmp(pixelFormat, "BayerRG8") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_BAYER_RG8;
	else if (strcmp(pixelFormat, "BayerGB8") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_BAYER_GB8;
	else if (strcmp(pixelFormat, "BayerBG8") == 0)
		m_nFormat = ITKBUFFER_VAL_FORMAT_BAYER_BG8;
	else
	{
		//ItkManTerminate();
		qDebug() << "pixelFormat error";
	}

	res = ItkBufferNew(m_nWidth, m_nHeight, m_nFormat, &m_hBuffer);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkBufferNew Failed";
		return false;
	}

	// Get buffer size
	res = ItkBufferGetPrm(m_hBuffer, ITKBUFFER_PRM_SIZE, &nImageSize);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkBufferGetPrm Failed";
		return false;
	}
	// apply buffer data
	m_hData = (char*)malloc(nImageSize);
	if (m_hData == NULL)
	{
		return false;
	}

	/* Allocate stream handle for image grab. */
	res = ItkDevAllocStream(m_hCamera, 0, m_hBuffer, &m_hStream);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevAllocStream Failed";
		return false;
	}
	return true;
}

bool IKapCamera::configureStream()
{
	if (NULL == m_hCamera || NULL == m_hStream)
	{
		qDebug() << "NULL == m_hCamera or NULL == m_hStream";
		return false;
	}
	ITKSTATUS	res = ITKSTATUS_OK;
	uint32_t			xferMode = ITKSTREAM_VAL_TRANSFER_MODE_SYNCHRONOUS_WITH_PROTECT;				/* Transfer image in asynchronous mode. */
	uint32_t         startMode = ITKSTREAM_VAL_START_MODE_NON_BLOCK;
	uint32_t			timeOut = m_nTimeOut;		/* Image transfer timeout.					*/

	/* Set block mode which means the grab will not be stopped before an entire image
	come into buffer. */
	res = ItkStreamSetPrm(m_hStream, ITKSTREAM_PRM_START_MODE, &startMode);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamSetPrm ITKSTREAM_PRM_START_MODE Failed";
		return false;
	}

	res = ItkStreamSetPrm(m_hStream, ITKSTREAM_PRM_TRANSFER_MODE, &xferMode);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamSetPrm ITKSTREAM_PRM_TRANSFER_MODE Failed";
		return false;
	}

	res = ItkStreamSetPrm(m_hStream, ITKSTREAM_PRM_TIME_OUT, &timeOut);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamSetPrm ITKSTREAM_PRM_TIME_OUT Failed";
		return false;
	}

	/* Register callback which will be called at the begin of stream. */
	res = ItkStreamRegisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_START_OF_STREAM, cbStartOfStream, this);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamRegisterCallback Failed";
		return false;
	}

	/* Register callback which will be called at the end of stream. */
	res = ItkStreamRegisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_END_OF_STREAM, cbEndOfStream, this);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamRegisterCallback Failed";
		return false;
	}

	/* Register callback which will be called at the end of one image completely. */
	res = ItkStreamRegisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_END_OF_FRAME, cbOnEndOfFrame, this);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamRegisterCallback Failed";
		return false;
	}

	res = ItkStreamRegisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_TIME_OUT, cbOnTimeOut, this);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamRegisterCallback Failed";
		return false;
	}

	res = ItkStreamRegisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_FRAME_LOST, cbOnFrameLost, this);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamRegisterCallback Failed";
		return false;
	}
	return true;
}

bool IKapCamera::startGrab()
{
	if (m_bDeviceGrab)
	{
		qDebug() << "Device is Grabbing";
		return false;
	}
	bool bRet = createStreamAndBuffer();
	if (!bRet)
	{
		qDebug() << "createStreamAndBuffer Failed";
		return false;
	}
	bRet = configureStream();
	if (!bRet)
	{
		qDebug() << "configureStream Failed";
		return false;
	}

	ITKSTATUS	res = ITKSTATUS_OK;
	res = ItkDevFromString(m_hCamera, "AcquisitionMode", "Continuous");
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkDevFromString AcquisitionMode Failed";
		return false;
	}
	res = ItkStreamStart(m_hStream, ITKSTREAM_CONTINUOUS);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamStart Failed";
		return false;
	}
	m_bDeviceGrab = true;
	return true;
}

bool IKapCamera::stopGrab()
{
	if (!m_bDeviceGrab)
	{
		qDebug() << "Device is not Grabbing";
		return false;
	}
	if (NULL == m_hCamera || NULL == m_hStream)
	{
		qDebug() << "NULL == m_hCamera or NULL == m_hStream";
		return false;
	}
	ITKSTATUS	res = ITKSTATUS_OK;
	res = ItkStreamStop(m_hStream);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkStreamStop Failed";
		return false;
	}
	res = ItkStreamUnregisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_START_OF_STREAM);
	res = ItkStreamUnregisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_END_OF_STREAM);
	res = ItkStreamUnregisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_END_OF_FRAME);
	res = ItkStreamUnregisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_TIME_OUT);
	res = ItkStreamUnregisterCallback(m_hStream, ITKSTREAM_VAL_EVENT_TYPE_FRAME_LOST);
	ItkStreamRemoveBuffer(m_hStream, m_hBuffer);
	ItkBufferFree(m_hBuffer);
	ItkDevFreeStream(m_hStream);
	if (m_hData != NULL)
		free(m_hData);
	m_bDeviceGrab = false;
	return true;
}

bool IKapCamera::loadCameraConfigFile(char *fileName)
{
	if (m_bDeviceOpen)
	{
		ITKSTATUS res = ItkDevLoadConfigurationFromFile(m_hCamera, fileName);
		if (res != ITKSTATUS_OK)
		{
			qDebug() << "save config failed:" << fileName;
			return false;
		}
	}
	else
	{
		qDebug() << "camera is not opened";
		return false;
	}
	return true;
}

bool IKapCamera::saveCameraConfigFile(char *fileName)
{
	if (m_bDeviceOpen)
	{
		ITKSTATUS res = ItkDevSaveConfigurationToFile(m_hCamera, fileName);
		if (res != ITKSTATUS_OK)
		{
			qDebug() << "save config failed:" << fileName;
			return false;
		}
	}
	else
	{
		qDebug() << "camera is not opened";
		return false;
	}
	return true;
}

void IKAPC_CC IKapCamera::cbStartOfStream(uint32_t eventType, void * pContext)
{
	qDebug() << "cbStartOfStream";
}

void IKAPC_CC IKapCamera::cbEndOfStream(uint32_t eventType, void * pContext)
{
	qDebug() << "cbEndOfStream";
}

void IKAPC_CC IKapCamera::cbOnEndOfFrame(uint32_t eventType, void * pContext)
{
	IKapCamera* camera = (IKapCamera*)pContext;
	if (NULL == camera)
	{
		qDebug() << "Get pContext Failed";
		return;
	}
	ITKSTATUS res = ITKSTATUS_OK;
	unsigned bufferStatus = 0;
	int64_t     nImageSize = 0;
	ITKBUFFER  hBuffer = camera->m_hBuffer;

	res = ItkBufferGetPrm(hBuffer, ITKBUFFER_PRM_STATE, &bufferStatus);
	if (ITKSTATUS_OK != res)
	{
		qDebug() << "ItkBufferGetPrm ITKBUFFER_PRM_STATE Failed";
		return;
	}
	if (bufferStatus == ITKBUFFER_VAL_STATE_FULL || bufferStatus == ITKBUFFER_VAL_STATE_UNCOMPLETED)
	{
		// Read buffer
		res = ItkBufferGetPrm(hBuffer, ITKBUFFER_PRM_SIZE, &nImageSize);
		if (ITKSTATUS_OK != res)
		{
			qDebug() << "ItkBufferGetPrm ITKBUFFER_PRM_SIZE Failed";
			return;
		}
		res = ItkBufferRead(hBuffer, 0, camera->m_hData, (uint32_t)nImageSize);//真正copy图像数据的地方
		if (ITKSTATUS_OK != res)
		{
			qDebug() << "ItkBufferGetPrm ITKBUFFER_PRM_SIZE Failed";
			return;
		}
		if (ITKBUFFER_VAL_FORMAT_MONO8 == camera->m_nFormat)
		{
			cv::Mat image = cv::Mat(camera->m_nHeight, camera->m_nWidth, CV_8UC1, camera->m_hData);
			emit camera->sendCameraImage(image.clone());
			qDebug() << "CallBack Get One Frame";
		}
		else
			qDebug() << "Error Format";
	}
	else
		qDebug() << "Read Image Buffer Failed";

	camera->m_end = QDateTime::currentDateTime();
	//qDebug() << "Elapse = " << camera->m_start.msecsTo(camera->m_end);
}

void IKAPC_CC IKapCamera::cbOnTimeOut(uint32_t eventType, void * pContext)
{
	qDebug() << "cbOnTimeOut";
}

void IKAPC_CC IKapCamera::cbOnFrameLost(uint32_t eventType, void * pContext)
{
	qDebug() << "cbOnFrameLost";
}
