#include "CMainWindow.h"
#include <qdir.h>
#include <QDateTime>
#include <QTextStream>
#include "QDockWidget"
#include "ParametersManager.h"
#include "ResultDetails.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;
	mutex.lock();

	QString text;
	switch (type)
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString::fromLocal8Bit(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1          %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);
	QString LogPath = QCoreApplication::applicationDirPath();
	LogPath.append("/log");
	QDir dir(LogPath);
	if (!dir.exists(LogPath))
	{
		dir.mkdir(LogPath);
	}
	QString logFile = LogPath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
	logFile.append(".txt");
	QFile file(logFile);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << message << "\r\n";
	file.flush();
	file.close();

	mutex.unlock();
}

CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qInstallMessageHandler(outputMessage);
	InitVariables();
	InitConnections();
	InitResultDetials();
	InitRightResultDetials();
}

void CMainWindow::InitVariables()
{
	qDebug() << "InitVariables";
	//处理结果
	QDockWidget *ResultDock = new QDockWidget(QString::fromLocal8Bit("左相机识别结果"));
	ResultDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, ResultDock);

	QDockWidget *RightResultDock = new QDockWidget(QString::fromLocal8Bit("右相机识别结果"));
	RightResultDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, RightResultDock);

	QFont LabelFont("微软雅黑", 122);
	m_LeftResult = new QLabel("NA");
	m_LeftResult->setStyleSheet("color: rgb(0, 0, 170);background-color: rgb(255, 255, 150);");
	m_LeftResult->setFont(LabelFont);
	m_LeftResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ResultDock->setWidget(m_LeftResult);

	m_RightResult = new QLabel("NA");
	m_RightResult->setStyleSheet("color: rgb(0, 0, 170);background-color: rgb(255, 255, 150);");
	m_RightResult->setFont(LabelFont);
	m_RightResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	RightResultDock->setWidget(m_RightResult);

	//结果浮动窗口
	m_LeftResultDetials = new QDockWidget(QString::fromLocal8Bit("左相机结果明细"));
	m_LeftResultDetials->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, m_LeftResultDetials);

	m_RightResultDetials = new QDockWidget(QString::fromLocal8Bit("右相机结果明细"));
	m_RightResultDetials->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, m_RightResultDetials);

	//日志浮动窗口
	QFont font("微软雅黑", 12);
	m_ListView = new QListView();
	m_ListView->setFont(font);
	m_LogModel = new QStandardItemModel();
	m_ListView->setModel(m_LogModel);
	QDockWidget *LogDock = new QDockWidget(QString::fromLocal8Bit("日志"));
	LogDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, LogDock);
	LogDock->setWidget(m_ListView);
	m_bStart = false;
	ui.action_Start->setEnabled(true);
	ui.action_Stop->setEnabled(false);
	ui.action_Setting->setEnabled(true);
	m_PartNumber.clear();
	m_Label = new QLabel();
	ui.mainToolBar->addWidget(m_Label);
	m_Label->setFont(QFont("Microsoft YaHei", 20, 75));	
	m_Label->setStyleSheet("color:blue;");
	m_Label->setText(QString::fromLocal8Bit("检测次数:0,成功:0,失败:0"));
	m_TotalCount = 0;
	m_SuccessCount = 0;


	m_bLeftOK = true;
	m_bRightOK = true;
}

void CMainWindow::InitConnections()
{
	qDebug() << "InitConnections";
	connect(ui.action_Start, SIGNAL(triggered()), this, SLOT(StartDetection()));
	connect(ui.action_Stop, SIGNAL(triggered()), this, SLOT(StopDetection()));
	connect(ui.action_Setting, SIGNAL(triggered()), this, SLOT(OpenSetting()));
	connect(ui.action_DataManager, SIGNAL(triggered()), this, SLOT(OpenDataManager()));
	connect(&m_Parameter, SIGNAL(SendAlgoImage(Mat, e_CameraType,int, bool)), this, SLOT(ReceiveAlgoImage(Mat, e_CameraType ,int, bool)));
	connect(&m_Parameter, SIGNAL(SendCloseEvent()), this, SLOT(ReceiveParameterCloseEvent()));
	connect(&m_Parameter, SIGNAL(SendPartNumber(QString)), this, SLOT(ReceivePartNumber(QString)));
	connect(this, SIGNAL(SendPartNumber(QString)), this, SLOT(ReceivePartNumber(QString)));
}

void CMainWindow::InitResultDetials()
{
	qDebug() << "InitLeftResultDetials";
	for (int i = 0; i < m_LeftResults.size(); ++i)
	{
		delete m_LeftResults[i];
		m_LeftResults[i] = NULL;
	}
	m_LeftResults.clear();

	int count = CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT);
	printf("image count:%d\n", count);
	qDebug() << "image count:" << count;
	QGridLayout *Layout = new QGridLayout();
	for (int r = 0; r < count; ++r)
	{
		QLabel *label = new QLabel();
		label->installEventFilter(this);
		label->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
		int row = r / 5;
		int col = r % 5;
		Layout->addWidget(label, row, col);
		m_LeftResults.push_back(label);
	}
	
	QGroupBox *LeftBox = new QGroupBox(QString::fromLocal8Bit("结果明细"));
	LeftBox->setMouseTracking(true);
	LeftBox->setLayout(Layout);
	m_LeftResultDetials->setWidget(LeftBox);



}

void CMainWindow::InitRightResultDetials()
{
	qDebug() << "InitRightResultDetials";
	for (int i = 0; i < m_RightResults.size(); ++i)
	{
		delete m_RightResults[i];
		m_RightResults[i] = NULL;
	}
	m_RightResults.clear();

	int count = CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT);
	printf("image count:%d\n", count);
	qDebug() << "image count:" << count;
	QGridLayout *RightLayout = new QGridLayout();
	for (int r = 0; r < count; ++r)
	{
		QLabel *label = new QLabel();
		label->installEventFilter(this);
		label->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
		int row = r / 5;
		int col = r % 5;
		RightLayout->addWidget(label, row, col);
		m_RightResults.push_back(label);
	}

	QGroupBox *RightBox = new QGroupBox(QString::fromLocal8Bit("结果明细"));
	RightBox->setMouseTracking(true);
	RightBox->setLayout(RightLayout);
	m_RightResultDetials->setWidget(RightBox);
}

void CMainWindow::RefreshResultDetials()
{
	qDebug() << "Refresh Result Detials";
	for (int i = 0; i < m_LeftResults.size(); ++i)
	{
		m_LeftResults[i]->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
	}
	m_LeftResult->setStyleSheet("color: rgb(0, 0, 170);background-color: rgb(255, 255, 150);");
	m_LeftResult->setText("NA");
	for (int i = 0; i < m_RightResults.size(); ++i)
	{
		m_RightResults[i]->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
	}
	m_RightResult->setStyleSheet("color: rgb(0, 0, 170);background-color: rgb(255, 255, 150);");
	m_RightResult->setText("NA");
}

void CMainWindow::AddLog(QString log)
{
	int rows = m_LogModel->rowCount();
	if (rows > 1000)
	{
		m_LogModel->removeRows(0, rows);
	}
	m_LogModel->appendRow(new QStandardItem(log));
	m_ListView->scrollToBottom();
}

bool CMainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouseevent = static_cast<QMouseEvent *>(event);
		if (mouseevent->buttons() == Qt::LeftButton)
		{
			for (int i = 0; i < m_LeftResults.size(); ++i)
			{
				if (obj == m_LeftResults.at(i))
				{
					qDebug() << "left click at left details index = " << i + 1;
					Mat cvImage = m_LeftImages.at(i);
					QImage img = MattoQImage(cvImage);
					CResultDetials::GetInstance()->SetImage(img);
					CResultDetials::GetInstance()->exec();
					break;
				}
			}
		}
	}
	return QMainWindow::eventFilter(obj, event);
}

void CMainWindow::StartDetection()
{
	qDebug() << "StartDetection";
	m_bRightOK = true;
	m_bLeftOK = true;
	QString Msg;
	bool rv = m_Parameter.CheckEnvironment(Msg);
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), Msg);
		return;
	}
#ifndef SYSTEM_DEBUG
 	rv = CDataManager::GetInstance()->GetConnectStatus();
 	if (!rv)
 	{
 		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("数据库未连接"));
 		return;
 	}
#endif
	m_Parameter.SetSystemStatus(true);
	ui.action_Start->setEnabled(false);
	ui.action_Stop->setEnabled(true);
	ui.action_Setting->setEnabled(false);
	m_bStart = true;
}

void CMainWindow::StopDetection()
{
	qDebug() << "StopDetection";
	m_Parameter.SetSystemStatus(false);
	ui.action_Start->setEnabled(true);
	ui.action_Stop->setEnabled(false);
	ui.action_Setting->setEnabled(true);
	m_bStart = false;
}

void CMainWindow::OpenSetting()
{
	qDebug() << "OpenSetting";
	m_Parameter.exec();
}

void CMainWindow::OpenDataManager()
{
	CDataManager::GetInstance()->setWindowState(Qt::WindowMaximized);
	CDataManager::GetInstance()->exec();
}

QImage CMainWindow::MattoQImage(Mat image)
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
void CMainWindow::ReceiveAlgoImage(Mat RenderImage, e_CameraType Type, int index, bool bOK)
{
	if (!m_bStart)
	{
		return;
	}
#ifdef SYSTEM_DEBUG
	m_PartNumber = "TEST-PART-NUMBER";
#else
	if (m_PartNumber.isEmpty())
	{
		printf("料号为空，不允许检测\n");
		qDebug() << QString::fromLocal8Bit("料号为空，不允许检测");
		AddLog(QString::fromLocal8Bit("料号为空，不允许检测"));
		//QString Msg;
		//m_Parameter.SendDetectionResult(2, Msg);
		return;
	}
#endif
	Mat TempImage = RenderImage.clone();
	QImage QImg = MattoQImage(TempImage);
	if (Type == CAMERA_LEFT)
	{
		qDebug() << "receive image index:" << index;
		printf("receive image index:%d\n", index);
		ui.label_Image->SetImage(QImg);
		m_LeftImages.push_back(RenderImage.clone());

		QLabel *Label = m_LeftResults.at(index);
		if (Label == NULL)
		{
			qDebug() << "left Label is NULL,index = " << index;
			return;
		}
		if (bOK)
		{
			Label->setStyleSheet("background-color: rgba(0, 170, 0, 255);");
		}
		else
		{
			Label->setStyleSheet("background-color: rgba(170, 0, 0, 255);");
			m_bLeftOK = false;
		}
		if (index == CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT) - 1)
		{
			if (m_bLeftOK)
			{
				m_LeftResult->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);");
				m_LeftResult->setText("OK");
			}
			else
			{
				m_LeftResult->setStyleSheet("color: rgb(170, 0, 0);background-color: rgb(255, 255, 150);");
				m_LeftResult->setText("NG");
			}
			m_Result.insert(CAMERA_LEFT, m_bLeftOK);
			if (m_Result.size() == 2)
			{
				ProcessDetectionResult(m_bLeftOK);

				InitResultDetials();
				RefreshResultDetials();
				m_Parameter.ResetFrameID();
				m_bLeftOK = true;
				m_bRightOK = true;
				m_Result.clear();
				m_LeftImages.clear();
				m_RightImages.clear();
			}
		

		}
	}
	if (Type == CAMERA_RIGHT)
	{
		qDebug() << "receive image index:" << index;
		printf("receive image index:%d\n", index);
		ui.label_Image_Right->SetImage(QImg);
		m_RightImages.push_back(RenderImage.clone());

		QLabel *Label = m_RightResults.at(index);
		if (Label == NULL)
		{
			qDebug() << "left Label is NULL,index = " << index;
			return;
		}
		if (bOK)
		{
			Label->setStyleSheet("background-color: rgba(0, 170, 0, 255);");
		}
		else
		{
			Label->setStyleSheet("background-color: rgba(170, 0, 0, 255);");
			m_bRightOK = false;
		}
		if (index == CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT) - 1)
		{
			if (m_bRightOK)
			{
				m_RightResult->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);");
				m_RightResult->setText("OK");
			}
			else
			{
				m_RightResult->setStyleSheet("color: rgb(170, 0, 0);background-color: rgb(255, 255, 150);");
				m_RightResult->setText("NG");
			}
			m_Result.insert(CAMERA_RIGHT, m_bRightOK);
			if (m_Result.size() == 2)
			{
				ProcessDetectionResult(m_bRightOK);
				InitRightResultDetials();
				RefreshResultDetials();
				m_Parameter.ResetFrameID();
				m_bLeftOK = true;
				m_bRightOK = true;
				m_Result.clear();
				m_LeftImages.clear();
				m_RightImages.clear();
			}

		}
	}



}

void CMainWindow::ProcessDetectionResult(bool bok)
{
	QString Msg;
	bool rv = true;
	if (bok)
	{
		rv = m_Parameter.SendDetectionResult(1, Msg);
		m_SuccessCount++;
	}
	else
	{
		rv = m_Parameter.SendDetectionResult(0, Msg);
	}
	m_TotalCount++;
	if (!rv)
	{
		AddLog(QString::fromLocal8Bit("发送结果失败:") + Msg);
	}
	else
	{
		AddLog(QString::fromLocal8Bit("发送结果:") + QString::number(bok));
	}
	//m_bOK = true;
	m_PartNumber.clear();
	QString message = QString::fromLocal8Bit("检测次数:") + QString::number(m_TotalCount) + QString::fromLocal8Bit(",成功:");
	message += QString::number(m_SuccessCount) + QString::fromLocal8Bit(",失败:") + QString::number(m_TotalCount - m_SuccessCount);
	m_Label->setText(message);
}

void CMainWindow::ReceiveParameterCloseEvent()
{
	InitResultDetials();
}

void CMainWindow::ReceivePartNumber(QString partNumber)
{
	AddLog(QString::fromLocal8Bit("料号:") + partNumber);
	m_PartNumber = partNumber;
	RefreshResultDetials();
	m_Parameter.ResetFrameID();
	m_LeftImages.clear();
	m_RightImages.clear();
	m_bLeftOK = true;
	m_bRightOK = true;
	m_Result.clear();
}