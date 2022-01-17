#pragma  once
#include "qsettings.h"

//相机相关
const QString CAMERA_SECTION = "Camera_Section";
//左相机
const QString CAMERA_NAME = "Camera_Name";
const QString IMAGE_COUNT = "Image_Count";
const QString IMAGE_HEIGHT = "Image_Height";
//右相机
const QString CAMERA_NAME_RIGHT = "Camera_Name_Right";
const QString IMAGE_COUNT_RIGHT = "Image_Count_Right";
const QString IMAGE_HEIGHT_RIGHT = "Image_Height_Right";

//系统参数
const QString SYSTEM_SECTION = "System_Section";
const QString SYSTEM_SPEED = "System_Speed";
const QString SYSTEM_TYPE = "System_Type";
const QString SAVE_PATH = "Save_Path";

//算法参数
const QString ALGO_SECTION = "Algo_Section";
const QString THRESHOLD = "Threshold";

//通讯
const QString COMMUNICATION = "Communication";
const QString CONNECTSTATUS = "Status";
const QString SERVER_IP = "Server_ip";
const QString SERVER_PORT = "Server_port";
const QString HEART_BEAT = "Heart_Beat";

const QString DATABASE = "Database";
const QString DATABASE_NAME = "DBName";
const QString USER_NAME = "UserName";
const QString PASSWORD = "Password";


typedef enum
{
	BARCODE_NORMAL = 0,   //一维码普通
	BARCODE_POL,       //一维码偏光
	QRCODE_NORMAL,     //二维码普通
	QRCODE_POL,        //二维码偏光
	QRCODE_APPEND      //二维码覆膜
}e_ProductType;

class CConfig
{
public:
	CConfig(QString IniPath);
	~CConfig();
	bool SectionExists(QString section);
	QStringList GetChildKeys(QString Section);
	int GetInt(QString Section,QString Key);
	double GetDouble(QString Section,QString Key);
	QString GetString(QString Section,QString Key);
	bool GetBool(QString Section,QString Key);
	void Write(QString Section,QString Key,QVariant Value);
	void RemoveKey(QString Section);
private:
	QString m_IniPath;
	QSettings *m_Settings;
};