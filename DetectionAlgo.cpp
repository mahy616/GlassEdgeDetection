#include <windows.h>
#include "DetectionAlgo.h"
#include "QCoreApplication"
#include "config_setting.h"
//const int X_LENGTH = 2048;

CDetectAlgo::CDetectAlgo(QThread *parent /* = NULL */)
	:QThread(parent)
{
	m_bStop = false;
	m_bInitSuccess = false;
	m_ImageList.clear();
}

void CDetectAlgo::InitAlgo()
{	
	m_bInitSuccess = 1;
}

void CDetectAlgo::InitParameters()
{
	int ImageHeight = CParametersManager::GetInstance()->GetCameraHeight();
	int Threshold = CParametersManager::GetInstance()->GetGrayThreshold();
	//¿¨³ßÕÒÏßÅäÖÃ£¬ÕÒÉÏ±ßÔµÏß£¨²£Á§ÔÚ×ó±ß£©

	x_First_config = x_edge1_first_left_config;
	x_Last_config= x_edge2_last_left_config;

	y_First_config= y_edge1_first_left_config;
    y_Last_config= y_edge2_last_left_config;
	y_Middle_config = y_edge_proceed_left_config;

	x_First_config_Right = x_edge1_first_right_config;
	x_Last_config_Right = x_edge2_last_right_config;

	y_First_config_Right = y_edge1_first_right_config;
	y_Last_config_Right = y_edge2_last_right_config;
	y_Middle_config_Right = y_edge_proceed_right_config;

}

Mat CDetectAlgo::RunAlgoOffLine(Mat image, QString type, bool &bok)
{
	EdgeConfig *x_edge = NULL;
	EdgeConfig *y_edge = NULL;
	printf("offline run right camera algo------------------------------------\n");
	if (type == "first")
	{
		x_edge = &x_First_config;
		y_edge = &y_First_config;
	}
	else if (type == "last")
	{
		x_edge = &x_Last_config;
		y_edge = &y_Last_config;
	}
	else
	{
		x_edge = &x_First_config;
		y_edge = &y_Middle_config;
	}
	smartmore::InputConfig importconfig{ type.toStdString(), std::string("left"), x_edge, y_edge, X_LENGTH,CParametersManager::GetInstance()->GetCameraHeight() };

	//smartmore::InputConfig importconfig{ string("proceed"), string("left"), &x_edge1_first_left_config, &y_edge_proceed_left_config, X_LENGTH, 6500 };
	Mat renderImage;
	try
	{
		cv::Mat mask_head_or_tail;
	     algo.RunAlgo(mask_head_or_tail,100,image,importconfig, bok, true);
		 if (!algo.VisualizeDetectOk(image, mask_head_or_tail, renderImage))
			 std::cout << "visulizaiton is wrong!" << std::endl;
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		printf("RunAlgoOffLine exception:%s\n", err_msg);
	}
	return renderImage;
}

void CDetectAlgo::RunAlgo(Mat image,int index, e_CameraType type)
{
	m_Mutex.lock();
	s_AlgoImageInfo info;
	info.image = image.clone();
	info.index = index;
	info.type = type;
	m_ImageList.push_back(info);
	m_Mutex.unlock();
}

void CDetectAlgo::StopThread()
{
	m_bStop = true;
}

void CDetectAlgo::run()
{
	while (1)
	{
		if (m_bStop)
		{
			break;
		}
		if (m_ImageList.size() > 0)
		{
			m_Mutex.lock();
			s_AlgoImageInfo info = m_ImageList.dequeue();
			m_Mutex.unlock();
			qDebug() << "m_ImageList:" << info.index;
			int Threshold = CParametersManager::GetInstance()->GetGrayThreshold();
			int ImageHeight = CParametersManager::GetInstance()->GetCameraHeight();
			QString mode;
			EdgeConfig *x_edge = NULL;
			EdgeConfig *y_edge = NULL;
			if (info.index == 0)
			{
				mode = "first";
				if (info.type == CAMERA_LEFT)
				{
					x_edge = &x_First_config;
					y_edge = &y_First_config;
				}
				else
				{
					x_edge = &x_First_config_Right;
					y_edge = &y_First_config_Right;
				}
				
			}
			else if (info.index == CParametersManager::GetInstance()->GetImageCount(info.type)-1)
			{
				mode = "last";
				if (info.type == CAMERA_LEFT)
				{
					x_edge = &x_Last_config;
					y_edge = &y_Last_config;
				}
				else
				{
					x_edge = &x_Last_config_Right;
					y_edge = &y_Last_config_Right;
				}
			}
			else
			{
				mode = "proceed";
				if (info.type == CAMERA_LEFT)
				{
					x_edge = &x_First_config;
					y_edge = &y_Middle_config;
				}
				else
				{
					x_edge = &x_First_config_Right;
					y_edge = &y_Middle_config_Right;
				}	
			}
			//smartmore::InputConfig importconfig{ std::string("proceed") , std::string("left"), x_edge, y_edge, X_LENGTH,ImageHeight };		
			Mat renderImage;
			try
			{
				cv::Mat mask_head_or_tail;
				bool bok = false;
				if (info.type == CAMERA_RIGHT)
				{
					smartmore::InputConfig importconfig{ mode.toStdString(), std::string("right"), x_edge, y_edge, X_LENGTH,ImageHeight };
					algo.RunAlgo(mask_head_or_tail, 100, info.image, importconfig, bok, true);
				}
				else if (info.type == CAMERA_LEFT)
				{
					smartmore::InputConfig importconfig{ mode.toStdString(), std::string("left"), x_edge, y_edge, X_LENGTH,ImageHeight };
					algo.RunAlgo(mask_head_or_tail, 100, info.image, importconfig, bok, true);
				}
				//algo.RunAlgo(mask_head_or_tail, 100, info.image, importconfig, bok, true);
				cv::Mat result_mask;
				algo.VisualizeDetectOk(info.image, mask_head_or_tail, renderImage);
				emit SendAlgoResult(info.image, renderImage, info.index, bok);
			}
			catch (cv::Exception& e)
			{
				const char* err_msg = e.what();
				emit SendAlgoResult(info.image, info.image, info.index, false);
				qDebug() << "left auto run algo exception:" << err_msg;
				printf("left auto run algo exception:%s\n", err_msg);
			}
		}
		else
		{
			Sleep(10);
		}
	}
}
