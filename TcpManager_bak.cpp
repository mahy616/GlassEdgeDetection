#include "TcpManager.h"
#include "windows.h"


CTcpManager *CTcpManager::m_Instace = NULL;

CTcpManager::CTcpManager(QObject *parent)
	:QObject(parent)
{
	m_TcpClient = new QTcpSocket(); 
	m_IP = "";
	m_Port = 0;
	m_bConnected = false;
	m_HeartBeat = 3;
	m_PartNumber.clear();
	connect(m_TcpClient, SIGNAL(connected()), this, SLOT(TcpConnected()));
	connect(m_TcpClient, SIGNAL(disconnected()), this, SLOT(TcpDisConnected()));
	connect(m_TcpClient, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(SlotTimeOuter()));
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
	m_Timer.stop();
	m_IP = ip;
	m_Port = port;
	QAbstractSocket::SocketState status = m_TcpClient->state();
	if (status == QAbstractSocket::ConnectedState)
	{
		m_TcpClient->abort();
		Sleep(100);
	}
	m_TcpClient->connectToHost(m_IP, m_Port);
	m_TcpClient->waitForConnected(500);
	m_IP = ip;
	m_Port = port;
	m_HeartBeat = HeartBeat;
	m_Timer.start(m_HeartBeat*1000);
	m_ReadTimer.start(50);
	//emit SendConnectStatus(m_bConnected);
}

void CTcpManager::TcpDisconnect()
{
	qDebug() << "TcpDisconnect";
	QAbstractSocket::SocketState status = m_TcpClient->state();
	if (m_bConnected)
	{
		m_TcpClient->disconnectFromHost();
		m_bConnected = false;
		m_TcpClient->waitForDisconnected(1000);	
		m_IP.clear();
		m_Port = 0;
	}
}

void CTcpManager::WritePLCData(int result)
{
	//D701  1-OK,0-NG,2-卡料
	if (m_bConnected)
	{
		QString WriteData = "50 00 00 FF FF 03 00 0E 00 10 00 01 14 00 00 2B 0D 00 A8 01 00";
		if (result == 0)
		{
			WriteData += "00 00";
		}
		else if(result == 1)
		{
			WriteData += "01 00";
		}
		else if (result == 2)
		{
			WriteData += "02 00";
		}
		QByteArray arrayHex = QByteArray::fromHex(WriteData.toLatin1());

		m_TcpClient->write(arrayHex);
		m_TcpClient->waitForBytesWritten(50);
		m_TcpClient->flush();
		m_TcpClient->waitForReadyRead(50);
	}
}

void CTcpManager::ReadPLCPartNumber()
{
	//printf("ReadPLCPartNumber\n");
	//D600 读10个字
	QString ReadData("50 00 00 FF FF 03 00 0C 00 10 00 01 04 00 00 08 25 00 A8 0A 00");
	QByteArray arrayHex = QByteArray::fromHex(ReadData.toLatin1());
	m_TcpClient->write(arrayHex);
	m_TcpClient->waitForBytesWritten(50);
	m_TcpClient->flush();
	m_TcpClient->waitForReadyRead(50);
}

void CTcpManager::ReadPLCSpeed()
{
	//printf("ReadPLCSpeed\n");
	//D700 读1个字
	QString ReadData("50 00 00 FF FF 03 00 0C 00 10 00 01 04 00 00 0C 2B 00 A8 01 00");
	QByteArray arrayHex = QByteArray::fromHex(ReadData.toLatin1());
	m_TcpClient->write(arrayHex);
	m_TcpClient->waitForBytesWritten(50);
	m_TcpClient->flush();
	m_TcpClient->waitForReadyRead(50);
}

void CTcpManager::TcpConnected()
{
	qDebug() << "TcpConnected";
	m_Mutex.lock();
	m_bConnected = true;
	m_Mutex.unlock();
	emit SendConnectStatus(true);
}

void CTcpManager::TcpDisConnected()
{
	qDebug() << "TcpDisConnected";
	m_Mutex.lock();
	m_bConnected = false;
	m_Mutex.unlock();
	emit SendConnectStatus(false);
}

void CTcpManager::ReadMessage()
{
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QByteArray ba = m_TcpClient->readAll();
		if (ba.size() > 0)
		{
			QString data = ba.toHex().toUpper();
			if (data == "D00000FFFF030002000000")
			{
				//写PLC返回码，不用关注
				printf("write plc data success\n");
				return;
			}

			//速度:D00000FFFF030004000000C05D
			//CO5D 高低位交换 5DC0 = 24000
			int pos = data.indexOf("D00000FFFF030004000000");
			if (pos != -1)
			{
				QString strSpeed = data.right(4);
				QString High = strSpeed.right(2);
				QString Low = strSpeed.left(2);
				strSpeed = High + Low;
				bool bOK = false;
				int Speed = strSpeed.toInt(&bOK, 16);
				if (m_Speed == 0 || m_Speed != Speed)
				{
					m_Speed = Speed;
					qDebug() << "receive plc speed:" << m_Speed;
					printf("receive plc speed:%d\n", m_Speed);
					emit SendSpeed(m_Speed);
				}
				return;
			}
			pos = data.indexOf("D00000FFFF030016000000");
			if (pos != -1)
			{
				//解析料号 D00000FFFF0300160000004635313546303038303420202020202020202020
				//D00000FFFF030016000000  PLC返回码
				//4635313546303038303420202020202020202020 料号
				QString PLCHexData = data.right(data.length() - 22);
				QString PLCString;
				for (int i = 0; i < PLCHexData.length() / 2; ++i)
				{
					QString OneData = PLCHexData.left(2);
					bool bOK = false;
					char chData = OneData.toInt(&bOK, 16);
					PLCString += chData;
					PLCHexData = PLCHexData.right(PLCHexData.length() - 2);
				}
				if (m_PartNumber.isEmpty() || m_PartNumber != PLCString)
				{
					qDebug() << "receive plc part number:" << PLCString;
					printf("receive plc part number:%s\n", PLCString.toStdString().c_str());
					m_PartNumber = PLCString;
					emit SendPartNumber(PLCString);
				}
			}
		}
	}
}

void CTcpManager::SlotTimeOuter()
{
	if (!m_bConnected)
	{
		if (!m_IP.isEmpty())
		{
			//重连
			qDebug() << "reconnect ip:" << m_IP << ",port:" << m_Port;
			m_TcpClient->connectToHost(m_IP, m_Port);
			m_bConnected = m_TcpClient->waitForConnected(50);
			emit SendConnectStatus(m_bConnected);
		}
	}
// 	else
// 	{
// 		//写心跳包
// 		m_TcpClient->write("TP1E");
// 		m_TcpClient->flush();
// 		printf("send heartbeat cmd:TP1E\n");
// 	}
}

void CTcpManager::SlotReadTimeOuter()
{
	m_Mutex.lock();
	if (m_bConnected)
	{
		ReadPLCPartNumber();
		ReadPLCSpeed();
	}
	m_Mutex.unlock();
}
