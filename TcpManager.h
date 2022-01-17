#pragma once
#include <Qthread>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include "melsec_mc_bin.h"

class CTcpManager :public QObject
{
	Q_OBJECT
public:
	static CTcpManager *GetInstance();
	void TcpConnect(QString ip, quint16 port,int HeartBeat);
	bool GetConnectStatus() { return m_bConnected; }
	void WritePLCData(int result);
private:
	CTcpManager(QObject *parent = NULL);
	~CTcpManager();
	static CTcpManager *m_Instace;
	bool m_bConnected;
	QTimer m_ReadTimer;
	QMutex m_Mutex;
	QString m_PartNumber;
	int m_Speed;
	int m_fd;
private slots:
	void SlotReadTimeOuter();
signals:
	void SendConnectStatus(bool bConnected);
	void SendPartNumber(QString msg);
	void SendSpeed(int speed);
};