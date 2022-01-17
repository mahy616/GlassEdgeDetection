#pragma once
#include "ui_ParameterSetting.h"
#include "QMessageBox"
#include "QDebug"
#include "QButtonGroup"
#include "TcpManager.h"
#include "SaveImage.h"
#include "IKapCamera.h"
#include "DetectionAlgo.h"

typedef struct
{
	IKapCamera IKapCameraHandle;
	QString CameraName;
	bool bCameraOpened;
	bool bCameraGrab;
	Mat OriginalImage;
	Mat RenderImage;
	int m_LeftFrameIndex;
	void init()
	{
		CameraName.clear();
		bCameraOpened = false;
		bCameraGrab = false;
		m_LeftFrameIndex = 0;
	}
}s_CameraInfo;

class CParamterSetting :public QDialog
{
	Q_OBJECT
public:
	CParamterSetting(QDialog *parent = NULL);
	~CParamterSetting();
	void LoadConfig();
	bool CheckEnvironment(QString &Msg);
	bool SendDetectionResult(int result,QString &Msg);
	void SetSystemStatus(bool bStart);
	void ResetFrameID();
private:
	Ui::DialogSettings ui;
	//���
	bool m_bStart;
	s_CameraInfo m_CameraInfo;
	s_CameraInfo m_RightCameraInfo;
	CDetectAlgo *m_Algo;
	CDetectAlgo *m_RightAlgo;
	QButtonGroup m_Group;
	int m_SysType;
	QButtonGroup m_IndexGroup;
	QString m_ImageType;
	QString m_RightImageType;
	bool m_bConnectedServer;
	QString m_PartNumber;
	CSaveImage m_SaveImage;
	int m_LeftFrameIndex;
	int m_RightFrameIndex;
	int m_iSpeed;
private:
	void InitVariables();
	void InitConnections();
	void InitCameraInfo();
	bool CloseDevice(e_CameraType type);
	QImage MattoQImage(Mat image);
	void SaveCameraImage(Mat Image, e_CameraType type);
	void SaveAlgoImage(QString PartNumber, Mat OriginalImage, Mat RenderImage,int index,bool bok, e_CameraType type);
	void InitControllers(bool enabled);
	void InitCameraParameter();

	void InitRightControllers(bool enabled);
	void InitRightCameraParameter();
protected:
	void closeEvent(QCloseEvent *event);
private slots: 
	//�����
	void OpenCamera();
	void CameraGrab();
	void SwitchCameraStatus(int index, bool checked);
	void SetCameraExposure(int value);
	void SetCameraGain(int value);
	void SetCameraFreq(int value);
	void SetCameraHeight(int value);
	void SetImageCount(int value);

	//�����
	void RightOpenCamera();
	void RightCameraGrab();
	void SwitchRightCameraStatus(int index, bool checked);
	void SetRightCameraExposure(int value);
	void SetRightCameraGain(int value);
	void SetRightCameraFreq(int value);
	void SetRightCameraHeight(int value);




	//���ݴ浵
	void BrowseSaveImagePath();
	//�������
	void LoadImage();
	void DetectOnce();

	void RightLoadImage();
	void RightDetectOnce();

	void SwitchImageType(int index, bool checked);

	void SetXOffset(int value);
	void SetYOffset(int value);
	void SetThreshold(int value);
	void SetLength(int value);
	void SetDistance(int value);
	void ShowRender(bool checked);
	//����ͼ��
	void ReceiveCameraImage(cv::Mat &img);
	void ReceiveRightCameraImage(cv::Mat &img);
	//�����㷨ͼ��
	void ReceiveLeftAlgoImage(Mat OriginalImage, Mat RenderImage, int index, bool bOK);
	void ReceiveRightAlgoImage(Mat OriginalImage, Mat RenderImage, int index, bool bOK);
	//�л�ϵͳ״̬  0:����ģʽ,1:����Debugģʽ 2:����Debugģʽ
	void SwitchSystemType(int type);
	//����ƽ̨�ٶ�
	void SetSpeed(int speed);
	void ConnectToServer();
	void SetHeartBeat(int value);
	void ReceiveTcpConnectStatus(bool status);
	void ReceivePartNumber(QString PartNumber);
	void ReceiveSpeed(int Speed);
	//��������
	void SaveConfig();
signals:
	void SendAlgoImage(Mat RenderImage, e_CameraType type, int index, bool bOK);
	void SendCloseEvent();
	void SendPartNumber(QString PartNumber);
};