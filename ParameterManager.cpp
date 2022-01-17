#include "ParametersManager.h"
#include "QDateTime"


CParametersManager *CParametersManager::m_Instance = NULL;

CParametersManager::CParametersManager(QObject *parent /* = NULL */)
	:QObject(parent)
{
	InitVariables();
}

CParametersManager *CParametersManager::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CParametersManager();
	}
	return m_Instance;
}

void CParametersManager::InitVariables()
{
	m_ImageCount = 1;
	m_ImageHeight = 6500;
	m_Speed = 3000;
	m_XOffset_First = 100;
	m_YOffset_First = 200;
	m_XOffset_Last = 100;
	m_YOffset_Last = 200;
	m_SavePath.clear();
	m_Threshold = 10;
	m_Length = 50;
	m_Distance = 20;
	m_HeartBeat = 3;
}

void CParametersManager::SetImageCount(int value,e_CameraType type)
{
	if (type == CAMERA_LEFT)
	{
		m_ImageCount = value;
	}
	else if (type == CAMERA_RIGHT)
	{
		m_RightImageCount = value;
	}
}

int CParametersManager::GetImageCount(e_CameraType type)
{
	return m_ImageCount;
}

void CParametersManager::SetCameraHeight(int value)
{
	m_ImageHeight = value;
}

int CParametersManager::GetCameraHeight()
{
	return m_ImageHeight;
}

void CParametersManager::SetXOffset(QString mode, int value)
{
	if (mode == "first")
	{
		m_XOffset_First = value;
	}
	else if (mode == "last")
	{
		m_XOffset_Last = value;
	}
}

int CParametersManager::GetXOffset(QString mode)
{
	if (mode == "first")
	{
		return m_XOffset_First;
	}
	else if (mode == "last")
	{
		return m_XOffset_Last;
	}
	return 200;
}

void CParametersManager::SetYOffset(QString mode, int value)
{
	if (mode == "first")
	{
		m_YOffset_First = value;
	}
	else if (mode == "last")
	{
		m_YOffset_Last = value;
	}
}

int CParametersManager::GetYOffset(QString mode)
{
	if (mode == "first")
	{
		return m_YOffset_First;
	}
	else if (mode == "last")
	{
		return m_YOffset_Last;
	}
	return 200;
}

void CParametersManager::SetGrayThreshold(int value)
{
	m_Threshold = value;
}
int CParametersManager::GetGrayThreshold()
{
	return m_Threshold;
}

void CParametersManager::SetLength(int value)
{
	m_Length = value;
}

int CParametersManager::GetLength()
{
	return m_Length;
}

void CParametersManager::SetDistance(int value)
{
	m_Distance = value;
}

int CParametersManager::GetDistance()
{
	return m_Distance;
}