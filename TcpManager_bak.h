#pragma once
#include <Qthread>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#include <QMutex>

class CTcpManager :public QObject
{
	Q_OBJECT
public:
	static CTcpManager *GetInstance();
	void TcpConnect(QString ip, quint16 port,int HeartBeat);
	void TcpDisconnect();
	bool GetConnectStatus() { return m_bConnected; }
	void WritePLCData(int result);
private:
	CTcpManager(QObject *parent = NULL);
	~CTcpManager();
	static CTcpManager *m_Instace;
	QTcpSocket *m_TcpClient;
	QString m_IP;
	quint16 m_Port;
	bool m_bConnected;
	QTimer m_Timer;
	QTimer m_ReadTimer;
	int m_HeartBeat;
	QMutex m_Mutex;
	QString m_PartNumber;
	int m_Speed;
	void ReadPLCPartNumber();
	void ReadPLCSpeed();
private slots:
	void TcpConnected();
	void TcpDisConnected();
	void ReadMessage();
	void SlotTimeOuter();
	void SlotReadTimeOuter();
signals:
	void SendConnectStatus(bool status);
	void SendPartNumber(QString msg);
	void SendSpeed(int speed);
};