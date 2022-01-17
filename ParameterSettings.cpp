#include "ParameterSettings.h"
#include "ParametersManager.h"
#include "QFileDialog"
#include "QDateTime"
#include "Config.h"
#include "DataManager.h"

CParamterSetting::CParamterSetting(QDialog *parent /* = NULL */)
	:QDialog(parent)
{
	ui.setupUi(this);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinimizeButtonHint;
	flags |= Qt::WindowMaximizeButtonHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	InitVariables();
	InitConnections();
	LoadConfig();
}

CParamterSetting::~CParamterSetting()
{
	if (m_CameraInfo.bCameraOpened)
	{
		qDebug() << "close camera";
		CloseDevice(CAMERA_LEFT);
	}
	if (m_RightCameraInfo.bCameraOpened)
	{
		qDebug() << "close camera";
		CloseDevice(CAMERA_RIGHT);
	}
	m_Algo->StopThread();
	m_Algo->wait(2000);

	m_RightAlgo->StopThread();
	m_RightAlgo->wait(2000);

	m_SaveImage.StopThread();
	m_SaveImage.wait(2000);
}

void CParamterSetting::closeEvent(QCloseEvent *event)
{
	qDebug() << "parameter setting close event";
	emit SendCloseEvent();
}

void CParamterSetting::InitVariables()
{
	qDebug() << "InitVariables";
	m_CameraInfo.init();
	m_RightCameraInfo.init();
#ifdef SYSTEM_DEBUG
	ui.spinBox_Speed->setEnabled(true);
	m_PartNumber = "TEST-PARTNUMBER";
	m_bConnectedServer = true;
#else
	ui.spinBox_Speed->setEnabled(false);
	m_PartNumber.clear();
	m_bConnectedServer = false;
#endif
	m_Group.addButton(ui.radioButton_FreeRun, 1);
	m_Group.addButton(ui.radioButton_External, 2);

	ui.comboBox_SysType->addItem(QString::fromLocal8Bit("运行模式"));
	ui.comboBox_SysType->addItem(QString::fromLocal8Bit("在线Debug模式"));
	ui.comboBox_SysType->addItem(QString::fromLocal8Bit("离线Debug模式"));

	m_SysType = 0;
	m_ImageType = "first";
	m_RightImageType = "first";
	m_IndexGroup.addButton(ui.radioButton_First, 1);
	m_IndexGroup.addButton(ui.radioButton_Middle, 2);
	m_IndexGroup.addButton(ui.radioButton_Last, 3);

	m_IndexGroup.addButton(ui.radioButton_First_Right, 4);
	m_IndexGroup.addButton(ui.radioButton_Middle_Right, 5);
	m_IndexGroup.addButton(ui.radioButton_Last_Right, 6);

	ui.pushButton_DetectOnce->setEnabled(false);
	QRegExp reg("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
	ui.lineEdit_IP->setValidator(new QRegExpValidator(reg));
	
	//初始化算法
	m_Algo = new CDetectAlgo();
	m_Algo->InitAlgo();
	if (m_Algo->GetInitStatus())
	{
		m_Algo->start();
	}

	m_RightAlgo = new CDetectAlgo();
	m_RightAlgo->InitAlgo();
	if (m_RightAlgo->GetInitStatus())
	{
		m_RightAlgo->start();
	}
	m_SaveImage.start();

#ifdef SYSTEM_DEBUG
	InitControllers(true);
	ui.spinBox_Height->setEnabled(true);
#else
	InitControllers(false);
#endif
	m_bStart = false;
	m_RightFrameIndex = 0;
	m_LeftFrameIndex = 0;
	m_iSpeed = 24000;
	InitCameraInfo();
}

void CParamterSetting::InitControllers(bool enabled)
{
	qDebug() << "InitControllers:" << enabled;
	ui.pushButton_Grab->setEnabled(enabled);
	ui.spinBox_Exposure->setEnabled(enabled);
	ui.spinBox_Gain->setEnabled(enabled);
	ui.spinBox_Freq->setEnabled(enabled);
	ui.spinBox_ImageCount->setEnabled(enabled);
	ui.radioButton_FreeRun->setEnabled(enabled);
	ui.radioButton_External->setEnabled(enabled);
}

void CParamterSetting::InitConnections()
{
	qDebug() << "InitConnections";
	connect(&m_Group, SIGNAL(buttonToggled(int, bool)), this, SLOT(SwitchCameraStatus(int, bool)));
	connect(&m_IndexGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(SwitchImageType(int, bool)));
	qRegisterMetaType<cv::Mat>("cv::Mat &");
	connect(&m_CameraInfo.IKapCameraHandle, SIGNAL(sendCameraImage(cv::Mat &)), this, SLOT(ReceiveCameraImage(cv::Mat &)));
	connect(&m_RightCameraInfo.IKapCameraHandle, SIGNAL(sendCameraImage(cv::Mat &)), this, SLOT(ReceiveRightCameraImage(cv::Mat &)));
	qRegisterMetaType<Mat>("Mat");
	connect(m_Algo, SIGNAL(SendAlgoResult(Mat, Mat, int, bool)), this, SLOT(ReceiveLeftAlgoImage(Mat, Mat, int, bool)));
	connect(m_RightAlgo, SIGNAL(SendAlgoResult(Mat, Mat, int, bool)), this, SLOT(ReceiveRightAlgoImage(Mat, Mat, int, bool)));
	connect(ui.comboBox_SysType, SIGNAL(activated(int)), this, SLOT(SwitchSystemType(int)));
	connect(CTcpManager::GetInstance(), SIGNAL(SendConnectStatus(bool)), this, SLOT(ReceiveTcpConnectStatus(bool)));
	connect(CTcpManager::GetInstance(), SIGNAL(SendPartNumber(QString)), this, SLOT(ReceivePartNumber(QString)));
	connect(CTcpManager::GetInstance(), SIGNAL(SendSpeed(int)), this, SLOT(ReceiveSpeed(int)));
}

QImage CParamterSetting::MattoQImage(Mat image)
{
	switch (image.type())
	{
	case CV_8UC1:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols, QImage::Format_Grayscale8);
		return img;
	}
	break;
	case CV_8UC3:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols * 3, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	break;
	default:
	{
		QImage img;
		return img;
	}
	break;
	}
}

void CParamterSetting::InitCameraInfo()
{
	qDebug() << "InitCameraInfo";
	QStringList CameraNames;
	bool rv = m_CameraInfo.IKapCameraHandle.enumDeviceInfo(CameraNames);
	if (rv)
	{
		ui.pushButton_Open->setEnabled(CameraNames.size() > 0);
		ui.comboBox_CamNames->addItems(CameraNames);
	}
	else
	{
		qDebug() << "enum up left camera failed";
	}
	qDebug() << "InitRightCameraInfo";
	QStringList RightCameraNames;
	 rv = m_RightCameraInfo.IKapCameraHandle.enumDeviceInfo(RightCameraNames);
	if (rv)
	{
		ui.pushButton_Open_Right->setEnabled(RightCameraNames.size() > 0);
		ui.comboBox_CamNames_Right->addItems(RightCameraNames);
	}
	else
	{
		qDebug() << "enum up left camera failed";
	}
}

bool CParamterSetting::CloseDevice(e_CameraType type)
{
	if (type == CAMERA_LEFT && m_CameraInfo.bCameraOpened)
	{
		qDebug() << "close camera";
		if (m_CameraInfo.bCameraGrab)
		{
			m_CameraInfo.IKapCameraHandle.stopGrab();
			m_CameraInfo.bCameraGrab = false;
		}
		bool rv = m_CameraInfo.IKapCameraHandle.closeDevice();
		if (!rv)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("关闭相机失败"));
			return false;
		}
	}
	else if (type == CAMERA_RIGHT && m_RightCameraInfo.bCameraOpened)
	{
		qDebug() << "close camera";
		if (m_RightCameraInfo.bCameraGrab)
		{
			m_RightCameraInfo.IKapCameraHandle.stopGrab();
			m_RightCameraInfo.bCameraGrab = false;
		}
		bool rv = m_RightCameraInfo.IKapCameraHandle.closeDevice();
		if (!rv)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("关闭相机失败"));
			return false;
		}
	}

	return true;
}

void CParamterSetting::InitCameraParameter()
{
	QString AppDir = QCoreApplication::applicationDirPath();
	QString CamCfgPath = AppDir + "/OutCamera.ccf";
	QFileInfo info;
	if (info.exists(CamCfgPath))
	{
		QByteArray ba = CamCfgPath.toLocal8Bit();
		char *fileName = ba.data();
		bool rv = m_CameraInfo.IKapCameraHandle.loadCameraConfigFile(fileName);
		if (rv)
		{
			double max, min, current;
			m_CameraInfo.IKapCameraHandle.getExposure(&max, &min, &current);
			int CurValue = current;
			int MinValue = ceil(min);
			int MaxValue = floor(max);
			ui.spinBox_Exposure->setRange(MinValue, MaxValue);
			ui.spinBox_Exposure->setValue(CurValue);
			qDebug() << "camera ExposureTime range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("camera ExposureTime range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			m_CameraInfo.IKapCameraHandle.getGain(&max, &min, &current);

			CurValue = current;
			MinValue = ceil(min);
			MaxValue = floor(max);
			ui.spinBox_Gain->setRange(MinValue, MaxValue);
			ui.spinBox_Gain->setValue(CurValue);
			qDebug() << "camera Gain range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("camera gain range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			m_CameraInfo.IKapCameraHandle.getAcquisitionLineRate(&max, &min, &current);
			CurValue = current;
			MinValue = ceil(min);
			MaxValue = floor(max);
			ui.spinBox_Freq->setRange(MinValue, MaxValue);
			ui.spinBox_Freq->setValue(CurValue);
			qDebug() << "camera line rate range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("camera freq range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			int64_t Height;
			m_CameraInfo.IKapCameraHandle.getHeight(&Height);
			ui.spinBox_Height->setValue(Height);
			qDebug() << "camera Height:" << Height;
			printf("camera Height:%Id\n", Height);
			CParametersManager::GetInstance()->SetCameraHeight(Height);
		}
	}
}
void CParamterSetting::InitRightControllers(bool enabled)
{
	qDebug() << "InitRightControllers:" << enabled;
	ui.pushButton_Grab_Right->setEnabled(enabled);
	ui.spinBox_Exposure_Right->setEnabled(enabled);
	ui.spinBox_Gain_Right->setEnabled(enabled);
	ui.spinBox_Freq_Right->setEnabled(enabled);
	ui.spinBox_ImageCount_Right->setEnabled(enabled);
	ui.radioButton_FreeRun_Right->setEnabled(enabled);
	ui.radioButton_External_Right->setEnabled(enabled);
}
void CParamterSetting::InitRightCameraParameter()
{
	QString AppDir = QCoreApplication::applicationDirPath();
	QString CamCfgPath = AppDir + "/InCamera.ccf";
	QFileInfo info;
	if (info.exists(CamCfgPath))
	{
		QByteArray ba = CamCfgPath.toLocal8Bit();
		char *fileName = ba.data();
		bool rv = m_RightCameraInfo.IKapCameraHandle.loadCameraConfigFile(fileName);
		if (rv)
		{
			double max, min, current;
			m_RightCameraInfo.IKapCameraHandle.getExposure(&max, &min, &current);
			int CurValue = current;
			int MinValue = ceil(min);
			int MaxValue = floor(max);
			ui.spinBox_Exposure_Right->setRange(MinValue, MaxValue);
			ui.spinBox_Exposure_Right->setValue(CurValue);
			qDebug() << "Rightcamera ExposureTime range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("Rightcamera ExposureTime range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			m_RightCameraInfo.IKapCameraHandle.getGain(&max, &min, &current);

			CurValue = current;
			MinValue = ceil(min);
			MaxValue = floor(max);
			ui.spinBox_Gain_Right->setRange(MinValue, MaxValue);
			ui.spinBox_Gain_Right->setValue(CurValue);
			qDebug() << "Rightcamera Gain range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("Rightcamera gain range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			m_RightCameraInfo.IKapCameraHandle.getAcquisitionLineRate(&max, &min, &current);
			CurValue = current;
			MinValue = ceil(min);
			MaxValue = floor(max);
			ui.spinBox_Freq_Right->setRange(MinValue, MaxValue);
			ui.spinBox_Freq_Right->setValue(CurValue);
			qDebug() << "Rightcamera line rate range:" << MinValue << "-" << MaxValue << ",cur:" << CurValue;
			printf("Rightcamera freq range:%d-%d,current value:%d\n", MinValue, MaxValue, CurValue);

			int64_t Height;
			m_RightCameraInfo.IKapCameraHandle.getHeight(&Height);
			ui.spinBox_Height_Right->setValue(Height);
			qDebug() << "Rightcamera Height:" << Height;
			printf("Rightcamera Height:%Id\n", Height);
			CParametersManager::GetInstance()->SetCameraHeight(Height);
		}
	}
}
void CParamterSetting::OpenCamera()
{
	QString name = ui.comboBox_CamNames->currentText();
	if (m_CameraInfo.bCameraOpened)
	{
		qDebug() << "CloseDevice()";
		bool rv = CloseDevice(CAMERA_LEFT);
		if (!rv)
		{
			return;
		}
		ui.pushButton_Open->setText(QString::fromLocal8Bit("打开相机"));
		m_CameraInfo.bCameraOpened = false;
		m_CameraInfo.CameraName.clear();
		InitControllers(false);
	}
	else
	{
		if (name == m_CameraInfo.CameraName)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("相机已被占用"));
			return;
		}
		else
		{
			qDebug() << "OpenCamera()";
			QString errMsg;
			m_CameraInfo.bCameraOpened = m_CameraInfo.IKapCameraHandle.openDevice(name, -1);
			if (!m_CameraInfo.bCameraOpened)
			{
				return;
			}
			InitCameraParameter();
			int FrameCount = CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT);
			m_CameraInfo.IKapCameraHandle.SetExternalTrigger(FrameCount);
			CameraGrab();
			ui.radioButton_External->setChecked(true);
			m_CameraInfo.CameraName = name;
			InitControllers(true);
			ui.pushButton_Open->setText(QString::fromLocal8Bit("关闭相机"));
		}
	}
}

void CParamterSetting::CameraGrab()
{
	if (!m_CameraInfo.bCameraGrab)
	{
		m_CameraInfo.bCameraGrab = m_CameraInfo.IKapCameraHandle.startGrab();
		ui.spinBox_Height->setEnabled(false);
		ui.pushButton_Grab->setText(QString::fromLocal8Bit("停止采集"));
	}
	else
	{
		m_CameraInfo.IKapCameraHandle.stopGrab();
		m_CameraInfo.bCameraGrab = false;
		ui.spinBox_Height->setEnabled(true);
		ui.pushButton_Grab->setText(QString::fromLocal8Bit("开始采集"));
	}
}

void CParamterSetting::RightOpenCamera()
{
	QString name = ui.comboBox_CamNames_Right->currentText();
	if (m_RightCameraInfo.bCameraOpened)
	{
		qDebug() << "CloseDevice()";
		bool rv = CloseDevice(CAMERA_RIGHT);
		if (!rv)
		{
			return;
		}
		ui.pushButton_Open_Right->setText(QString::fromLocal8Bit("打开相机"));
		m_RightCameraInfo.bCameraOpened = false;
		m_RightCameraInfo.CameraName.clear();
		InitRightControllers(false);
	}
	else
	{
		if (name == m_RightCameraInfo.CameraName)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("相机已被占用"));
			return;
		}
		else
		{
			qDebug() << "OpenCamera()";
			QString errMsg;
			m_RightCameraInfo.bCameraOpened = m_RightCameraInfo.IKapCameraHandle.openDevice(name, -1);
			if (!m_RightCameraInfo.bCameraOpened)
			{
				return;
			}
			InitRightCameraParameter();
			int FrameCount = CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT);
			m_RightCameraInfo.IKapCameraHandle.SetExternalTrigger(FrameCount);
			RightCameraGrab();
			ui.radioButton_External_Right->setChecked(true);
			m_RightCameraInfo.CameraName = name;
			InitRightControllers(true);
			ui.pushButton_Open_Right->setText(QString::fromLocal8Bit("关闭相机"));
		}
	}
}

void CParamterSetting::RightCameraGrab()
{
	if (!m_RightCameraInfo.bCameraGrab)
	{
		m_RightCameraInfo.bCameraGrab = m_RightCameraInfo.IKapCameraHandle.startGrab();
		ui.spinBox_Height_Right->setEnabled(false);
		ui.pushButton_Grab_Right->setText(QString::fromLocal8Bit("停止采集"));
	}
	else
	{
		m_RightCameraInfo.IKapCameraHandle.stopGrab();
		m_RightCameraInfo.bCameraGrab = false;
		ui.spinBox_Height_Right->setEnabled(true);
		ui.pushButton_Grab_Right->setText(QString::fromLocal8Bit("开始采集"));
	}
}

void CParamterSetting::SwitchRightCameraStatus(int index, bool checked)
{
	if (checked)
	{
		m_RightCameraInfo.IKapCameraHandle.stopGrab();
		if (index == 1)
		{
			qDebug() << "set camera free fun";
			m_RightCameraInfo.IKapCameraHandle.SetFreeRun();
		}
		else if (index == 2)
		{
			qDebug() << "set camera external trigger";
			int FrameCount = CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT);
			m_RightCameraInfo.IKapCameraHandle.SetExternalTrigger(FrameCount);
		}
		m_RightCameraInfo.IKapCameraHandle.startGrab();
	}
}

void CParamterSetting::SetRightCameraExposure(int value)
{
	bool nRet = m_RightCameraInfo.IKapCameraHandle.setExposure(value);
	printf("Set camera exposure:%d,result = %d\n", value, nRet);
	qDebug() << "set camera exposure:" << value;
}

void CParamterSetting::SetRightCameraGain(int value)
{
	bool nRet = m_RightCameraInfo.IKapCameraHandle.setGain(value);
	printf("Set camera gain:%d,result = %d\n", value, nRet);
	qDebug() << "set camera gain:" << value;
}

void CParamterSetting::SetRightCameraFreq(int value)
{
	bool nRet = m_RightCameraInfo.IKapCameraHandle.setAcquisitionLineRate(value);
	printf("Set camera frame rate:%d,result = %d\n", value, nRet);
	qDebug() << "set camera freq:" << value;
}

void CParamterSetting::SetRightCameraHeight(int value)
{
#ifdef SYSTEM_DEBUG
	printf("Set camera height:%d\n", value);
	CParametersManager::GetInstance()->SetCameraHeight(value);
#else
	bool rv = m_RightCameraInfo.IKapCameraHandle.setHeight(value);
	qDebug() << "set camera height:" << value << ",resutl = " << rv;
	printf("Set camera height:%d,result = %d\n", value, rv);
	if (rv)
	{
		CParametersManager::GetInstance()->SetCameraHeight(value);
	}
#endif
}

void CParamterSetting::SwitchCameraStatus(int index, bool checked)
{
	if (checked)
	{
		m_CameraInfo.IKapCameraHandle.stopGrab();
		if (index == 1)
		{
			qDebug() << "set camera free fun";
			m_CameraInfo.IKapCameraHandle.SetFreeRun();
		}
		else if (index == 2)
		{
			qDebug() << "set camera external trigger";
			int FrameCount = CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT);
			m_CameraInfo.IKapCameraHandle.SetExternalTrigger(FrameCount);
		}
		m_CameraInfo.IKapCameraHandle.startGrab();
	}
}

void CParamterSetting::SetCameraExposure(int value)
{
	bool nRet = m_CameraInfo.IKapCameraHandle.setExposure(value);
	printf("Set camera exposure:%d,result = %d\n", value, nRet);
	qDebug() << "set camera exposure:" << value;
}

void CParamterSetting::SetCameraGain(int value)
{
	bool nRet = m_CameraInfo.IKapCameraHandle.setGain(value);
	printf("Set camera gain:%d,result = %d\n", value, nRet);
	qDebug() << "set camera gain:" << value;
}

void CParamterSetting::SetCameraFreq(int value)
{
	bool nRet = m_CameraInfo.IKapCameraHandle.setAcquisitionLineRate(value);
	printf("Set camera frame rate:%d,result = %d\n", value, nRet);
	qDebug() << "set camera freq:" << value;
}

void CParamterSetting::SetCameraHeight(int value)
{
#ifdef SYSTEM_DEBUG
	printf("Set camera height:%d\n", value);
	CParametersManager::GetInstance()->SetCameraHeight(value);
#else
	bool rv = m_CameraInfo.IKapCameraHandle.setHeight(value);
	qDebug() << "set camera height:" << value << ",resutl = " << rv;
	printf("Set camera height:%d,result = %d\n", value, rv);
	if (rv)
	{
		CParametersManager::GetInstance()->SetCameraHeight(value);
	}
#endif
}

void CParamterSetting::SetImageCount(int value)
{
	CParametersManager::GetInstance()->SetImageCount(value, CAMERA_RIGHT);
	CParametersManager::GetInstance()->SetImageCount(value, CAMERA_LEFT);
	qDebug() << "set image count:" << value;
}


void CParamterSetting::BrowseSaveImagePath()
{
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("图像保存路径"));
	if (path.isEmpty())
	{
		return;
	}
	qDebug() << "browse save path:" << path;
	CParametersManager::GetInstance()->SetSavePath(path);
	ui.lineEdit_SavePath->setText(path);
}

//检测
void CParamterSetting::LoadImage()
{
	QString imagePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("图像文件"), "", "*.bmp;*.jpg;*.png;;All Files(*)");
	if (imagePath.isEmpty())
	{
		return;
	}
	qDebug() << "load image path:" << imagePath;
	QByteArray ba = imagePath.toLocal8Bit();
	char *file = ba.data();
	m_CameraInfo.OriginalImage = imread(file,0);
	QImage qimage = MattoQImage(m_CameraInfo.OriginalImage);
	ui.label_Image->SetImage(qimage);
	ui.pushButton_DetectOnce->setEnabled(true);
}

void CParamterSetting::DetectOnce()
{
	qDebug() << "detect once";
	int BeingTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (!m_Algo->GetInitStatus())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("算法未初始化成功"));
		return;
	}
	bool bok = false;
	m_Algo->InitParameters();
	m_CameraInfo.RenderImage = m_Algo->RunAlgoOffLine(m_CameraInfo.OriginalImage, m_ImageType, bok);
	int EndTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	printf("Detection result:%s\n", bok ? "OK" : "NG");
	printf("cost time:%dms\n", EndTime - BeingTime);
	QImage qimage = MattoQImage(m_CameraInfo.RenderImage);
	ui.label_Image->SetImage(qimage);
}

void CParamterSetting::RightLoadImage()
{
	QString imagePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("图像文件"), "", "*.bmp;*.jpg;*.png;;All Files(*)");
	if (imagePath.isEmpty())
	{
		return;
	}
	qDebug() << "load image path:" << imagePath;
	QByteArray ba = imagePath.toLocal8Bit();
	char *file = ba.data();
	m_CameraInfo.OriginalImage = imread(file, 0);
	QImage qimage = MattoQImage(m_CameraInfo.OriginalImage);
	ui.label_Image_Right->SetImage(qimage);
	ui.pushButton_DetectOnce_Right->setEnabled(true);
}

void CParamterSetting::RightDetectOnce()
{
	qDebug() << "detect once";
	int BeingTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (!m_Algo->GetInitStatus())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("算法未初始化成功"));
		return;
	}
	bool bok = false;
	m_Algo->InitParameters();
	m_CameraInfo.RenderImage = m_Algo->RunAlgoOffLine(m_CameraInfo.OriginalImage, m_RightImageType, bok);
	int EndTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	printf("Detection result:%s\n", bok ? "OK" : "NG");
	printf("cost time:%dms\n", EndTime - BeingTime);
	QImage qimage = MattoQImage(m_CameraInfo.RenderImage);
	ui.label_Image_Right->SetImage(qimage);
}

void CParamterSetting::SwitchImageType(int index, bool checked)
{
	if (checked)
	{
		if (index < 4)
		{
			if (index == 1)
			{
				m_ImageType = "first";
			}
			else if (index == 2)
			{
				m_ImageType = "proceed";
			}
			else if (index == 3)
			{
				m_ImageType = "last";
			}
			printf("left image type:%s\n", m_ImageType.toStdString().c_str());
		}
		else
		{
			if (index == 4)
			{
				m_RightImageType = "first";
			}
			else if (index == 5)
			{
				m_RightImageType = "proceed";
			}
			else if (index == 6)
			{
				m_RightImageType = "last";
			}
			printf("Right image type:%s\n", m_RightImageType.toStdString().c_str());
		}
	}
}

void CParamterSetting::SetXOffset(int value)
{
	if (ui.radioButton_First->isChecked())
	{
		CParametersManager::GetInstance()->SetXOffset("first",value);
		printf("set first x offset:%d\n", value);
	}
	else if (ui.radioButton_Last->isChecked())
	{
		CParametersManager::GetInstance()->SetXOffset( "last", value);
		printf("set last x offset:%d\n", value);
	}
}

void CParamterSetting::SetYOffset(int value)
{
	if (ui.radioButton_First->isChecked())
	{
		CParametersManager::GetInstance()->SetYOffset("first", value);
		printf("set first y offset:%d\n", value);
	}
	else if (ui.radioButton_Last->isChecked())
	{
		CParametersManager::GetInstance()->SetYOffset("last", value);
		printf("set last y offset:%d\n", value);
	}
}

void CParamterSetting::SetThreshold(int value)
{
	CParametersManager::GetInstance()->SetGrayThreshold(value);
	printf("set threshold:%d\n",value);
}

void CParamterSetting::SetLength(int value)
{
	CParametersManager::GetInstance()->SetLength(value);
	printf("set length:%d\n", value);
}

void CParamterSetting::SetDistance(int value)
{
	CParametersManager::GetInstance()->SetDistance(value);
	printf("set distance:%d\n", value);
}

void CParamterSetting::ShowRender(bool checked)
{
	QImage qimage;
	if (checked)
	{
		qimage = MattoQImage(m_CameraInfo.RenderImage);
	}
	else
	{
		qimage = MattoQImage(m_CameraInfo.OriginalImage);
	}
	ui.label_Image->SetImage(qimage);
}

int FrameCount = 0;

void CParamterSetting::ReceiveCameraImage(cv::Mat &img)
{
	printf("CParamterSetting:ReceiveCameraImage :%d\n",FrameCount++);
	qDebug() << "LeftFrameIndex,frame index=" << m_LeftFrameIndex;
	if (m_SysType == 1)
	{
		QImage QImg = MattoQImage(img);
		ui.label_Image->SetImage(QImg);
	}
	else if (m_SysType == 0 && m_bStart)
	{
		if (m_LeftFrameIndex < CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT))
		{
			m_Algo->RunAlgo(img.clone(), m_LeftFrameIndex, CAMERA_LEFT);
		}
		else
		{
			//CTcpManager::GetInstance()->WritePLCData(2);
			printf("host panel,frame index=%d\n", m_LeftFrameIndex);
			qDebug() << "host panel,frame index=" << m_LeftFrameIndex;
			m_LeftFrameIndex = 0;
			m_Algo->RunAlgo(img.clone(), m_LeftFrameIndex, CAMERA_LEFT);
			
		}
		m_LeftFrameIndex++;

	}
}

void CParamterSetting::ReceiveRightCameraImage(cv::Mat &img)
{
	printf("CParamterSetting:ReceiveCameraImage :%d\n", FrameCount++);
	if (m_SysType == 1)
	{
		QImage QImg = MattoQImage(img);
		ui.label_Image_Right->SetImage(QImg);
	}
	else if (m_SysType == 0 && m_bStart)
	{
		if (m_RightFrameIndex < CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT))
		{
			m_RightAlgo->RunAlgo(img.clone(), m_RightFrameIndex, CAMERA_RIGHT);
		}
		else
		{
			//CTcpManager::GetInstance()->WritePLCData(2);
			printf("host panel,frame index=%d\n", m_RightFrameIndex);
			qDebug() << "host panel,frame index=" << m_RightFrameIndex;
			m_RightFrameIndex = 0;
			m_RightAlgo->RunAlgo(img.clone(), m_RightFrameIndex, CAMERA_RIGHT);

		}
		m_RightFrameIndex++;
	}
}

void CParamterSetting::SaveCameraImage(Mat Image, e_CameraType type)
{
	QString path = ui.lineEdit_SavePath->text();
	if (path.isEmpty())
	{
		qDebug() << "save camera image failed,save path is empty";
		printf("save camera image failed,save path is empty\n");
	}

	QString Type;
	s_ImageInfo ImageInfo;
	ImageInfo.SavePath = path;
	ImageInfo.FileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz") + ".bmp";;
	ImageInfo.image = Image.clone();
	m_SaveImage.SetImageInfo(ImageInfo);
}

void CParamterSetting::SaveAlgoImage(QString PartNumber, Mat OriginalImage, Mat RenderImage, int index, bool bok, e_CameraType type)
{
	QString path = ui.lineEdit_SavePath->text();
	if (path.isEmpty())
	{
		qDebug() << "save algo image failed,save path is empty";
		printf("save algo image failed,save path is empty\n");
	}

	QString CurDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	s_ImageInfo ImageInfo;
	ImageInfo.SavePath = path;
	ImageInfo.MiddleDir = CurDate + "/" + PartNumber;
	ImageInfo.FileName = QString::number(index) + ".jpg";
	ImageInfo.image = RenderImage.clone();
	m_SaveImage.SetImageInfo(ImageInfo);
	if (!bok)
	{
		ImageInfo.image = OriginalImage.clone();
		ImageInfo.FileName = QString::number(index) + ".bmp";
		m_SaveImage.SetImageInfo(ImageInfo);
	}
}

void CParamterSetting::ReceiveLeftAlgoImage(Mat OriginalImage, Mat RenderImage, int index, bool bOK)
{
	if (m_SysType == 0)
	{
		Mat original = OriginalImage.clone();
		Mat render = RenderImage.clone();
		printf("receive algo image ,index:%d\n", index);
		emit SendAlgoImage(render, CAMERA_LEFT,index, bOK);
		SaveAlgoImage(m_PartNumber, OriginalImage,RenderImage,index + 1,bOK, CAMERA_LEFT);
	}
}

void CParamterSetting::ReceiveRightAlgoImage(Mat OriginalImage, Mat RenderImage, int index, bool bOK)
{
	if (m_SysType == 0)
	{
		Mat original = OriginalImage.clone();
		Mat render = RenderImage.clone();
		printf("receive algo image ,index:%d\n", index);
		emit SendAlgoImage(render, CAMERA_RIGHT,index, bOK);
		SaveAlgoImage(m_PartNumber, OriginalImage, RenderImage, index + 1, bOK, CAMERA_RIGHT);
	}
}

bool CParamterSetting::CheckEnvironment(QString &Msg)
{
#ifdef SYSTEM_DEBUG
	return true;
#else
	if (!m_CameraInfo.bCameraOpened)
	{
		Msg = QString::fromLocal8Bit("相机未打开");
		return false;
	}

	if (!m_Algo->GetInitStatus())
	{
		Msg = QString::fromLocal8Bit("算法未初始化成功");
		return false;
	}
#endif
	if (!m_bConnectedServer)
	{
		Msg = QString::fromLocal8Bit("未连接服务器");
		return false;
	}
	return true;
}

void CParamterSetting::SetSystemStatus(bool bStart)
{
	m_bStart = bStart;
	if (bStart)
	{
		m_Algo->InitParameters();
	}
#ifdef SYSTEM_DEBUG
	for (int i = 0; i < 7; ++i)
	{
		Mat image = imread("D:/HSY/惠科面板检测/GlassEdgeDetection_CELL/test-image/Image-0000.bmp", 0);
		m_Algo->RunAlgo(image, i);
	}
#endif
}

void CParamterSetting::ResetFrameID()
{
	m_RightFrameIndex = 0;
	m_LeftFrameIndex = 0;
}

//0:运行模式,1:在线Debug模式 2:离线Debug模式
void CParamterSetting::SwitchSystemType(int type)
{
	qDebug() << "set system type:" << type;
	m_SysType = type;
	ui.pushButton_LoadImage->setEnabled(type == 2);
}

void CParamterSetting::SetSpeed(int speed)
{
	printf("set speed:%d mm/min\n",speed);
	int value = speed / 0.027;
	if (m_CameraInfo.bCameraOpened)
	{
		bool nRet = m_CameraInfo.IKapCameraHandle.setAcquisitionLineRate(36000);
		printf("Set camera frame rate:%d,result = %d\n", 36000, nRet);
		qDebug() << "set camera freq rate:" << 36000;
		if (nRet)
		{
			ui.spinBox_Freq->setValue(36000);
			ui.spinBox_Speed->setValue(speed);
		}
	}
}

void CParamterSetting::SetHeartBeat(int value)
{
	CParametersManager::GetInstance()->SetHeartBeat(value);
	printf("set heart beat : %ds\n",value);
}

void CParamterSetting::ReceiveTcpConnectStatus(bool status)
{
	if (status)
	{
		ui.label_Status->setStyleSheet("background-color: rgb(0, 170, 0)");
	}
	else
	{
		ui.label_Status->setStyleSheet("background-color: rgb(170, 0, 0)");
	}
	m_bConnectedServer = status;
}

void CParamterSetting::ReceivePartNumber(QString PartNumber)
{
	printf("receive Part Number:%s\n", PartNumber.toStdString().c_str());
	m_PartNumber = PartNumber;
	emit SendPartNumber(PartNumber);
}

void CParamterSetting::ReceiveSpeed(int Speed)
{
	printf("receive Speed:%d\n", Speed);
	if (Speed == 0)
	{
		return;
	}
	else if (Speed != m_iSpeed)
	{
		SetSpeed(Speed);
		m_iSpeed = Speed;
	}
}

bool CParamterSetting::SendDetectionResult(int result, QString &Msg)
{
	if (!m_bConnectedServer)
	{
		Msg = QString::fromLocal8Bit("服务器未连接");
		return false;
	}
	//CTcpManager::GetInstance()->WritePLCData(result);
	QString Path = ui.lineEdit_SavePath->text();
	if (result == 1)
	{
		CDataManager::GetInstance()->InsertData(m_PartNumber, true, Path, Msg);
	}
	else if (result == 0)
	{
		CDataManager::GetInstance()->InsertData(m_PartNumber, false, Path, Msg);
	}
	return true;
}

void CParamterSetting::ConnectToServer()
{
	QString ip = ui.lineEdit_IP->text();
	QString strPort = ui.lineEdit_Port->text();
	if (ip.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("IP地址不能为空"));
		return;
	}
	if (strPort.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("端口号不能为空"));
		return;
	}

	ushort port = strPort.toUShort();
	qDebug() << "ip:" << ip;
	qDebug() << "port:" << strPort;
	printf("ip:%s,port:%s\n",ip.toStdString().c_str(),strPort.toStdString().c_str());
	CTcpManager::GetInstance()->TcpConnect(ip, port, CParametersManager::GetInstance()->GetHeartBeat());
}

//保存配置
void CParamterSetting::SaveConfig()
{
	QString AppDir = QCoreApplication::applicationDirPath();
	QString IniPath = AppDir + "/parametercfg.ini";
	CConfig *cfg = new CConfig(IniPath);
#ifndef SYSTEM_DEBUG
	if (m_CameraInfo.bCameraOpened)
	{
		cfg->Write(CAMERA_SECTION, CAMERA_NAME, m_CameraInfo.CameraName);
		QString CameraCfg = AppDir + "/Camera.ccf";
		QByteArray ba = CameraCfg.toLocal8Bit();
		char *file = ba.data();
		bool rv = m_CameraInfo.IKapCameraHandle.saveCameraConfigFile(file);
		if (rv)
		{
			printf("save camera feature success: %s\n", file);
			qDebug() << "save camera feature success:" << file;
		}
		cfg->Write(CAMERA_SECTION, IMAGE_COUNT, ui.spinBox_ImageCount->value());
	}
#else
	cfg->Write(CAMERA_SECTION, IMAGE_COUNT, ui.spinBox_ImageCount->value());
	cfg->Write(CAMERA_SECTION, IMAGE_HEIGHT, ui.spinBox_Height->value());
#endif


	int Threshold = ui.spinBox_Threshold->value();
	cfg->Write(ALGO_SECTION, THRESHOLD, Threshold);

	QString path = ui.lineEdit_SavePath->text();
	if (!path.isEmpty())
	{
		cfg->Write(SYSTEM_SECTION, SAVE_PATH, path);
	}

	int Speed = ui.spinBox_Speed->value();
	int type = ui.comboBox_SysType->currentIndex();
	cfg->Write(SYSTEM_SECTION, SYSTEM_SPEED, Speed);
	cfg->Write(SYSTEM_SECTION, SYSTEM_TYPE, type);
	cfg->Write(COMMUNICATION, CONNECTSTATUS, m_bConnectedServer);
	if (m_bConnectedServer)
	{
		QString ip = ui.lineEdit_IP->text();
		QString port = ui.lineEdit_Port->text();
		int HeartBeat = ui.spinBox->value();

		cfg->Write(COMMUNICATION, SERVER_IP, ip);
		cfg->Write(COMMUNICATION, SERVER_PORT, port);
		cfg->Write(COMMUNICATION, HEART_BEAT, HeartBeat);
	}
}

void CParamterSetting::LoadConfig()
{
	QString AppDir = QCoreApplication::applicationDirPath();
	QString IniPath = AppDir + "/parametercfg.ini";
	QFileInfo info(IniPath);
	if (!info.exists(IniPath))
	{
		return;
	}

	CConfig *cfg = new CConfig(IniPath);
	QString CameraName = cfg->GetString(CAMERA_SECTION, CAMERA_NAME);
	int ImageCount = cfg->GetInt(CAMERA_SECTION, IMAGE_COUNT);
	ui.spinBox_ImageCount->setValue(ImageCount);
	CParametersManager::GetInstance()->SetImageCount(ImageCount, CAMERA_LEFT);
	int pos = ui.comboBox_CamNames->findText(CameraName);
	if (pos != -1)
	{
		ui.comboBox_CamNames->setCurrentText(CameraName);
		OpenCamera();
	}

	QString CameraNameRight = cfg->GetString(CAMERA_SECTION, CAMERA_NAME_RIGHT);
	int ImageCountRight = cfg->GetInt(CAMERA_SECTION, IMAGE_COUNT_RIGHT);
	ui.spinBox_ImageCount_Right->setValue(ImageCountRight);
	CParametersManager::GetInstance()->SetImageCount(ImageCountRight, CAMERA_RIGHT);
	 pos = ui.comboBox_CamNames_Right->findText(CameraName);
	if (pos != -1)
	{
		ui.comboBox_CamNames_Right->setCurrentText(CameraName);
		OpenCamera();
	}

	int Threhold = cfg->GetInt(ALGO_SECTION, THRESHOLD);
	ui.spinBox_Threshold->setValue(Threhold);
	CParametersManager::GetInstance()->SetGrayThreshold(Threhold);

	QString path = cfg->GetString(SYSTEM_SECTION, SAVE_PATH);
	if (!path.isEmpty())
	{
		ui.lineEdit_SavePath->setText(path);
		CParametersManager::GetInstance()->SetSavePath(path);
	}

	m_iSpeed = cfg->GetInt(SYSTEM_SECTION, SYSTEM_SPEED);
	SetSpeed(m_iSpeed);
	ui.spinBox_Speed->setValue(m_iSpeed);
	m_SysType = cfg->GetInt(SYSTEM_SECTION, SYSTEM_TYPE);
	ui.comboBox_SysType->setCurrentIndex(m_SysType);

	if (cfg->GetBool(COMMUNICATION, CONNECTSTATUS))
	{
		QString ip = cfg->GetString(COMMUNICATION, SERVER_IP);
		QString port = cfg->GetString(COMMUNICATION, SERVER_PORT);
		int beat = cfg->GetInt(COMMUNICATION, HEART_BEAT);
		if (!ip.isEmpty() && !port.isEmpty())
		{
			ui.lineEdit_IP->setText(ip);
			ui.lineEdit_Port->setText(port);
			ui.spinBox->setValue(beat);
			CTcpManager::GetInstance()->TcpConnect(ip, port.toUShort(), beat);
		}
	}
}