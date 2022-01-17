#include "TcpManager.h"
#include "windows.h"

CTcpManager *CTcpManager::m_Instace = NULL;

CTcpManager::CTcpManager(QObject *parent)
	:QObject(parent)
{
	m_bConnected = false;
	m_PartNumber = "123456789";
	connect(&m_ReadTimer, SIGNAL(timeout()), this, SLOT(SlotReadTimeOuter()));
}

CTcpManager::~CTcpManager()
{

}

CTcpManager *CTcpManager::GetInstance()
{
	if (m_Instace == NULL)
	{
		m_Instace = new CTcpManager();
	}
	return m_Instace;
}

void CTcpManager::TcpConnect(QString ip, quint16 port, int HeartBeat)
{
	printf("connect to server ip:%s,port:%d,heartbeat:%d\n",ip.toStdString().c_str(),port,HeartBeat);
	qDebug() << "TcpConnect ip:" << ip << ",port:" << port << ",heart beat:" << HeartBeat;
	QByteArray ba = ip.toLocal8Bit();
	char *strIp = ba.data();
	m_fd = mc_connect(strIp, port, 0, 0);
	m_Mutex.lock();
	m_bConnected = m_fd > 0;
	m_Mutex.unlock();
	if (m_bConnected)
	{
		m_ReadTimer.start(500);
	}
	emit SendConnectStatus(m_bConnected);
}

void CTcpManager::SlotReadTimeOuter()
{
	m_Mutex.lock();
	if (m_bConnected)
	{
		short s_val = 0;
		bool ret = mc_read_short(m_fd, "D700", &s_val);
		if ((m_Speed == 0 || m_Speed != s_val) && s_val != 0)
		{
			m_Speed = s_val;
			printf("Read Speed:  %d\n", m_Speed);
			emit SendSpeed(m_Speed);
		}

		char* str_val = NULL;
		ret = mc_read_string(m_fd, "D600", 14, &str_val);
		QString PartNumber = QString(str_val).left(12);
		if (m_PartNumber != PartNumber && !PartNumber.isEmpty())
		{
			m_PartNumber = PartNumber;
			printf("Read PartNumber %s\n", str_val);
			emit SendPartNumber(m_PartNumber);
		}
	}
	m_Mutex.unlock();
}
