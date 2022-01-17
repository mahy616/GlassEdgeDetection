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
}

void CMainWindow::InitVariables()
{
	qDebug() << "InitVariables";
	//处理结果
	QDockWidget *ResultDock = new QDockWidget(QString::fromLocal8Bit("识别结果"));
	ResultDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, ResultDock);

	QFont LabelFont("微软雅黑", 122);
	m_LeftResult = new QLabel("OK");
	m_LeftResult->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);");
	m_LeftResult->setFont(LabelFont);
	m_LeftResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_RightResult = new QLabel("NG");
	m_RightResult->setStyleSheet("color: rgb(170, 0, 0);background-color: rgb(255, 255, 150);");
	m_RightResult->setFont(LabelFont);
	m_RightResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(m_LeftResult);
	layout->addWidget(m_RightResult);
	QWidget *widget = new QWidget();
	widget->setLayout(layout);
	ResultDock->setWidget(widget);

	//结果浮动窗口
	m_ResultDetials = new QDockWidget(QString::fromLocal8Bit("结果明细"));
	m_ResultDetials->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, m_ResultDetials);

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
	m_LeftIndex = 0;
	m_RightIndex = 0;
}

void CMainWindow::InitConnections()
{
	qDebug() << "InitConnections";
	connect(ui.action_Start, SIGNAL(triggered()), this, SLOT(StartDetection()));
	connect(ui.action_Stop, SIGNAL(triggered()), this, SLOT(StopDetection()));
	connect(ui.action_Setting, SIGNAL(triggered()), this, SLOT(OpenSetting()));
	connect(&m_Parameter, SIGNAL(SendCamreaImage(Mat, e_CameraType, bool)), this, SLOT(ReceiveCameraImage(Mat, e_CameraType, bool)));
	connect(&m_Parameter, SIGNAL(SendCloseEvent()), this, SLOT(ReceiveParameterCloseEvent()));
}

void CMainWindow::InitWindows()
{
	qDebug() << "InitWindows";
	for (int i = 0; i < m_LeftWindows.size(); ++i)
	{
		delete m_LeftWindows[i];
		m_LeftWindows[i] = NULL;
	}
	m_LeftWindows.clear();

	for (int i = 0; i < m_RightWindows.size(); ++i)
	{
		delete m_RightWindows[i];
		m_RightWindows[i] = NULL;
	}
	m_RightWindows.clear();
	//Mat image = imread("D:\\bg.jpg");
	//QImage qimg = MattoQImage(image);
	int row = CParametersManager::GetInstance()->GetWindowRow(CAMERA_LEFT);
	int col = CParametersManager::GetInstance()->GetWindowCol(CAMERA_LEFT);
	qDebug() << "Left windows row:" << row << "col:" << col;
	QGridLayout *LeftGrid = new QGridLayout();
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			MyLabel *label = new MyLabel();
			label->setStyleSheet("background-image: url(:/CMainWindow/Resources/background.png);");
			//label->SetImage(qimg);
			LeftGrid->addWidget(label, r, c);
			m_LeftWindows.push_back(label);
		}
	}

	row = CParametersManager::GetInstance()->GetWindowRow(CAMERA_RIGHT);
	col = CParametersManager::GetInstance()->GetWindowCol(CAMERA_RIGHT);
	qDebug() << "Right windows row:" << row << "col:" << col;
	QGridLayout *RightGrid = new QGridLayout();
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			MyLabel *label = new MyLabel();
			label->setStyleSheet("background-image: url(:/CMainWindow/Resources/background.png);");
			//label->SetImage(qimg);
			RightGrid->addWidget(label, r, c);
			m_RightWindows.push_back(label);
		}
	}
	QWidget *centerWindow = new QWidget;
	this->setCentralWidget(centerWindow);
	QGroupBox *LeftBox = new QGroupBox(QString::fromLocal8Bit("左相机"));
	LeftBox->setLayout(LeftGrid);
	QGroupBox *RightBox = new QGroupBox(QString::fromLocal8Bit("右相机"));
	RightBox->setLayout(RightGrid);
	QHBoxLayout *MainLayout = new QHBoxLayout();
	MainLayout->addWidget(LeftBox);
	MainLayout->addWidget(RightBox);
	centerWindow->setLayout(MainLayout);
}

void CMainWindow::InitResultDetials()
{
	qDebug() << "InitResultDetials";
	for (int i = 0; i < m_LeftResults.size(); ++i)
	{
		delete m_LeftResults[i];
		m_LeftResults[i] = NULL;
	}
	m_LeftResults.clear();

	for (int i = 0; i < m_RightResults.size(); ++i)
	{
		delete m_RightResults[i];
		m_RightResults[i] = NULL;
	}
	m_RightResults.clear();
	int row = CParametersManager::GetInstance()->GetWindowRow(CAMERA_LEFT);
	int col = CParametersManager::GetInstance()->GetWindowCol(CAMERA_LEFT);
	qDebug() << "Left windows row:" << row << "col:" << col;
	QGridLayout *LeftGrid = new QGridLayout();
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			QLabel *label = new QLabel();
			label->installEventFilter(this);
			label->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
			LeftGrid->addWidget(label, r, c);
			m_LeftResults.push_back(label);
		}
	}
	row = CParametersManager::GetInstance()->GetWindowRow(CAMERA_RIGHT);
	col = CParametersManager::GetInstance()->GetWindowCol(CAMERA_RIGHT);
	qDebug() << "Right windows row:" << row << "col:" << col;
	QGridLayout *RightGrid = new QGridLayout();
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			QLabel *label = new QLabel();
			label->installEventFilter(this);
			label->setStyleSheet("background-color: rgba(255, 255, 0, 255);");
			RightGrid->addWidget(label, r, c);
			m_RightResults.push_back(label);
		}
	}
	QGroupBox *LeftBox = new QGroupBox(QString::fromLocal8Bit("左相机"));
	LeftBox->setMouseTracking(true);
	LeftBox->setLayout(LeftGrid);
	QGroupBox *RightBox = new QGroupBox(QString::fromLocal8Bit("右相机"));
	RightBox->setMouseTracking(true);
	RightBox->setLayout(RightGrid);
	QHBoxLayout *HLayout = new QHBoxLayout();
	HLayout->addWidget(LeftBox);
	HLayout->addWidget(RightBox);
	QWidget *widget = new QWidget();
	widget->setLayout(HLayout);
	m_ResultDetials->setWidget(widget);
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
					QImage img = m_LeftWindows.at(i)->GetImage();
					CResultDetials::GetInstance()->SetImage(img);
					CResultDetials::GetInstance()->exec();
					break;
				}
			}

			for (int i = 0; i < m_RightResults.size(); ++i)
			{
				if (obj == m_RightResults.at(i))
				{
					qDebug() << "left click at right details index = " << i + 1;
					QImage img = m_RightWindows.at(i)->GetImage();
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
	m_bLeftOK = true;
	m_LeftIndex = 0;
	m_bRightOK = true;
	m_RightIndex = 0;
#if 0  
	InitWindows();
	InitResultDetials();
	

	//拼图
	Mat image = imread("D:\\bg.jpg");
	int type = image.type();
	m_LeftImage = Mat::zeros(10000, image.cols, CV_8UC3);
 	image.copyTo(m_LeftImage(Rect(0, 0, image.cols, image.rows)));
 	image.copyTo(m_LeftImage(Rect(0, image.rows, image.cols, image.rows)));
 	image.copyTo(m_LeftImage(Rect(0, image.rows*2, image.cols, image.rows)));
	QImage qimg = MattoQImage(m_LeftImage);
	ui.label_Left->SetImage(qimg);

	m_RightImage = Mat::zeros(10000, image.cols, CV_8UC3);
	image.copyTo(m_RightImage(Rect(0, 0, image.cols, image.rows)));
	image.copyTo(m_RightImage(Rect(0, image.rows, image.cols, image.rows)));
	image.copyTo(m_RightImage(Rect(0, image.rows * 2, image.cols, image.rows)));
	qimg = MattoQImage(m_RightImage);
	ui.label_Right->SetImage(qimg);
#endif
	QString Msg;
	bool rv = m_Parameter.CheckEnvironment(Msg);
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), Msg);
		return;
	}
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

void CMainWindow::SaveLeftImage(Mat image, bool bOK)
{
	qDebug() << "SaveLeftImage bOK = " << bOK;
	bool rv = CParametersManager::GetInstance()->GetSaveAll(CAMERA_LEFT);
	if (rv)
	{
		QString path = CParametersManager::GetInstance()->GetSaveAllPath(CAMERA_LEFT);
		if (!path.isEmpty())
		{
			QString FileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
			CParametersManager::GetInstance()->SaveAllImage(FileName, image, CAMERA_LEFT);
		}
		else
		{
			qDebug() << "save left all path is empty";
			printf("save left all path is empty\n");
		}
	}
	rv = CParametersManager::GetInstance()->GetSaveNG(CAMERA_LEFT);
	if (rv && !bOK)
	{
		QString path = CParametersManager::GetInstance()->GetSaveNGPath(CAMERA_LEFT);
		if (!path.isEmpty())
		{
			QString FileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
			CParametersManager::GetInstance()->SaveNGImage(FileName, image, CAMERA_LEFT);
		}
		else
		{
			qDebug() << "save left NG path is empty";
			printf("save left NG path is empty\n");
		}
	}
}

void CMainWindow::SaveRightImage(Mat image,bool bOK)
{
	bool rv = CParametersManager::GetInstance()->GetSaveAll(CAMERA_RIGHT);
	if (rv)
	{
		QString path = CParametersManager::GetInstance()->GetSaveAllPath(CAMERA_RIGHT);
		if (!path.isEmpty())
		{
			QString FileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
			CParametersManager::GetInstance()->SaveAllImage(FileName, image, CAMERA_RIGHT);
		}
		else
		{
			printf("save right all path is empty\n");
		}
	}
	rv = CParametersManager::GetInstance()->GetSaveNG(CAMERA_RIGHT);
	if (rv && !bOK)
	{
		QString path = CParametersManager::GetInstance()->GetSaveNGPath(CAMERA_RIGHT);
		if (!path.isEmpty())
		{
			QString FileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
			CParametersManager::GetInstance()->SaveNGImage(FileName, image, CAMERA_RIGHT);
		}
		else
		{
			printf("save left all path is empty\n");
		}
	}
}

void CMainWindow::ReceiveCameraImage(Mat img, e_CameraType type, bool bOK)
{
	if (!m_bStart)
	{
		return;
	}
	Mat TempImage = img.clone();
	QImage QImg = MattoQImage(TempImage);
	QPixmap pixmap = QPixmap::fromImage(QImg);
	
	if (type == CAMERA_LEFT)
	{
		printf("receive left camera image index:%d,width:%d,height:%d\n", m_LeftIndex, TempImage.cols, TempImage.rows);
		MyLabel *mylabel = m_LeftWindows[m_LeftIndex];
		if (mylabel == NULL)
		{
			qDebug() << "mylabel is NULL,index = " << m_LeftIndex;
			return;
		}
		printf("mylabel width:%d,height:%d\n", mylabel->width(), mylabel->height());
		QPixmap fitpixmap = pixmap.scaled(mylabel->width(), mylabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	 	//mylabel->setPixmap(fitpixmap);
		MyLabel *ldd = new MyLabel();
		ldd->SetImage(QImg);
		QLabel *Label = m_LeftResults.at(m_LeftIndex);
		if (Label == NULL)
		{
			qDebug() << "Label is NULL,index = " << m_LeftIndex;
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
		SaveLeftImage(img, bOK);
		m_LeftIndex++;
		if (m_LeftIndex == CParametersManager::GetInstance()->GetImageCount(CAMERA_LEFT))
		{
			m_LeftIndex = 0;
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
		}
	}
	else if (type == CAMERA_RIGHT)
	{
		printf("receive right camera image index:%d,width:%d,height:%d\n", m_RightIndex, TempImage.cols, TempImage.rows);
		MyLabel *mylabel = m_RightWindows.at(m_RightIndex);
		QLabel *Label = m_RightResults.at(m_RightIndex);
		mylabel->SetImage(QImg);
		if (bOK)
		{
			Label->setStyleSheet("background-color: rgba(0, 170, 0, 255);");
		}
		else
		{
			Label->setStyleSheet("background-color: rgba(170, 0, 0, 255);");
			m_bRightOK = false;
		}
		SaveRightImage(img,bOK);
		m_RightIndex++;
		if (m_RightIndex == CParametersManager::GetInstance()->GetImageCount(CAMERA_RIGHT))
		{
			m_RightIndex = 0;
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
		}
	}
}

void CMainWindow::ReceiveParameterCloseEvent()
{
	InitWindows();
	InitResultDetials();
}