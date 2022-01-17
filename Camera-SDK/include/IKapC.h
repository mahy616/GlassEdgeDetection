/**
  *  @file    IKapC.h
  *  @brief   IKapC library main header file.
  *  @author  iTek OptoElectronics Ltd(Li Bochuan) 
  *  @par     Copyright (c) iTek OptoElectronics Ltd.
  *           All Rights Reserved
  *  @date    2017:06:19 
  *  @note    This file contains the defines necessary to use the IKapC "C" user interface.
  *  @version <1.3.12.1>
  */ 

#ifndef _IKAPC_H
#define _IKAPC_H

#include "IKapCDef.h"

IKAPC_DECLARE_HANDLE(ITKDEVICE);              ///<A handle for a camera object
IKAPC_DECLARE_HANDLE(ITKBOARD);               ///<A handle for a frame grabber object
IKAPC_DECLARE_HANDLE(ITKFEATURE);             ///<A handle for a feature object
IKAPC_DECLARE_HANDLE(ITKEVENTINFO);           ///<A handle for a event info object
IKAPC_DECLARE_HANDLE(ITKSTREAM);			  ///<A handle for a stream object
IKAPC_DECLARE_HANDLE(ITKBUFFER);			  ///<A handle for a buffer object
IKAPC_DECLARE_HANDLE(ITKVIEW);				  ///<A handle for a view object

/** \addtogroup IKapC IKapC Interface
* @{
*/

/** IKapC event info callback */
typedef void (IKAPC_CC *PITKEVENTINFOCALLBACK)(void* pContext, ITKEVENTINFO hEventInfo);
/** IKapC stream callback */
typedef void(IKAPC_CC *PITKSTREAMCALLBACK)(uint32_t eventType, void* pContext);
/** IKapC view callback */
typedef void(IKAPC_CC *PITKVIEWCALLBACK)(uint32_t eventType, void* pContext);

/** @brief Fixed string size for  members. */
#define ITKDEV_INFO_ENTRY_MAX_LENGTH  (64)

#define ITKGIGEDEV_INFO_LENGTH_32_BYTE (32)
#define ITKGIGEDEV_INFO_LENGTH_64_BYTE (64)
#define ITKGIGEDEV_INFO_LENGTH_128_BTYE (128)
#define ITKGIGEDEV_INFO_LENGTH_256_BYTE (256)


/**
  *  @name   Device Info
  *  @brief  This struct provides general information about the device gathered during enumeration.
 */
typedef struct tag_itk_dev_info
{
	char FullName[ITKDEV_INFO_ENTRY_MAX_LENGTH];			/**< Full unique device name for identification */
	char FriendlyName[ITKDEV_INFO_ENTRY_MAX_LENGTH];		/**< User friendly device name for display purpose */
	char VendorName[ITKDEV_INFO_ENTRY_MAX_LENGTH];			/**< Manufacturer of the device*/
	char ModelName[ITKDEV_INFO_ENTRY_MAX_LENGTH];			/**< Model name of the device*/
	char SerialNumber[ITKDEV_INFO_ENTRY_MAX_LENGTH];		/**< Serial number of the device */
	char DeviceClass[ITKDEV_INFO_ENTRY_MAX_LENGTH];			/**< The device class (transport layer) used by the device  */
	char DeviceVersion[ITKDEV_INFO_ENTRY_MAX_LENGTH];		/**< The device version as reported by the device */
	char UserDefinedName[ITKDEV_INFO_ENTRY_MAX_LENGTH];		/**< User defined name, if present, as reported by the device */
} ITKDEV_INFO, *PITKDEV_INFO;

/**
*  @name   GigEVision specific information
*  @brief  This struct provides GigEVision sepcific information about the device gathered during enumeration.
*/
typedef struct tag_itk_gige_dev_info
{
	char MAC[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                          /**< Device mac.                   */
	char Ip[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                           /**< Device ip.                    */
	char SubNetMask[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                   /**< Device subnet mask.           */
	char GateWay[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                      /**< Device default gateway.       */
	char NICMac[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                       /**< Host NIC mac.                 */
	char NICIp[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                        /**< Host NIC ip.                  */
	char NICSubNetMask[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                /**< Host NIC subnet mask.         */
	char NICGateWay[ITKGIGEDEV_INFO_LENGTH_32_BYTE];                                   /**< Host NIC gateway.             */
	char NICAdapterName[ITKGIGEDEV_INFO_LENGTH_256_BYTE + 4];                          /**< Host NIC adpater name.        */
	char NICDescription[ITKGIGEDEV_INFO_LENGTH_128_BTYE + 4];                          /**< Host NIC description.         */
	char reserved[128];                                                                /**< Reserved.                     */
} ITKGIGEDEV_INFO, *PITKGIGEDEV_INFO;

/**
*  @name   CameraLink specific information
*  @brief  This struct provides CameraLink sepcific information about the device gathered during enumeration.
*/
typedef struct tag_itk_cl_dev_info
{
	uint32_t HostInterface;                       /**< Host interface type, 1 : USB30; 2 - PCIex4.  */
	uint32_t BoardIndex;                          /**< Board index.                                 */
	char Reserved[256];                           /**< Reserved.                                    */
}ITK_CL_DEV_INFO, *PITK_CL_DEV_INFO;

/**
*  @name   CoaXPress specific information
*  @brief  This struct provides CoaXPress sepcific information about the device gathered during enumeration.
*/
typedef struct tag_itk_cxp_dev_info
{
	uint32_t BoardIndex;                          /**< Master connection board index.          */
	uint32_t MasterPort;                          /**< Master connection board port.           */
	uint32_t SlaveCount;                          /**< Slave connection count.                 */
	uint32_t SlavePort[7];                        /**< Slave connection port.                  */
    uint32_t CameraId;                            /**< Camera Id                               */
	char Reserved[252];                           /**< Reserved.                               */
}ITK_CXP_DEV_INFO, *PITK_CXP_DEV_INFO;

/**
*  @name   USB3Vision specific information
*  @brief  This struct provides USB3Vision sepcific information about the device gathered during enumeration.
*/
typedef struct tag_itk_u3v_dev_info
{
	uint32_t VID;                                 /**< Camera VID.                             */
	uint32_t PID;                                 /**< Camera PID.                             */
	uint32_t USBVersion;                          /**< USB connection version.                 */
	char Reserved[256];                           /**< Reserved.                               */
}ITK_U3V_DEV_INFO, *PITK_U3V_DEV_INFO;


/**
*  @name   Board infomation
*  @brief  This struct provides frame grabber information during enumeration.
*/
typedef struct tag_itk_board_info{
	char Name[ITKDEV_INFO_ENTRY_MAX_LENGTH];                 /**< Full unique device name for identification */
	char Reserved[256];                                      /**< Reserved.                                  */
}ITKBOARD_INFO, *PITKBOARD_INFO;

#ifdef __cplusplus
// avoid namespace ambiguities between std::_Bool (from yvals.h) and ::_Bool (from IKapCTypes.h)
#  if defined(_MSC_VER)
#    define _Bool ::_Bool
#    define IKAPC_BOOL_DEFINED
#  endif

extern "C" {
#endif // __cplusplus

/**
  *  @brief  Initialize IKapC standard API.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INSUFFICIENT_RESOURCES
  *
  *  @note   Initiates access to the standard C library. This must be the first call in an application program.
  *  @see    ItkManTerminate   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkManInitialize(void);

/**
  *  @brief  Terminate IKapC standard API.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INSUFFICIENT_RESOURCES
  *
  *  @note   Terminates all access to the standard C library. This must be the last call in an application program.
  *  @see    ItkManInitialize   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkManTerminate(void);

/**
  *  @brief  Get the number of available device.
  *  @param[out]  pCount : Number of available device
  *  @Return:    
  *	 - ITKSTATUS_OK
  *
  *  @note   Use the configuration program to obtain a list of all available devices in your system.
  *  @see    other functions   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetDeviceCount(uint32_t *pCount);

/**
*  @brief  Get the number of available board.
*  @param[out]  pCount : Number of available board
*  @Return:
*	 - ITKSTATUS_OK
*
*  @note   Use the configuration program to obtain a list of all available board in your system.
*  @see    other functions
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetBoardCount(uint32_t *pCount);

/**
*  @brief  Get the information of available board.
*  @param[in]  index : Board index
*  @param[out] pBI : Board information
*  @Return:
*	 - ITKSTATUS_OK
*
*  @note   Use the configuration program to obtain a list of all available board in your system.
*  @see    other functions
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetBoardInfo(uint32_t index, PITKBOARD_INFO pBI);

/**
  *  @brief  Get information about camera device identified by its index.
  *  @param[in]  index : Device index.
  *  @param[out] pDI : Pointer to camera device info struct to fill.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALID_ARG : Invalid input argument
  *  - ITKSTATUS_DEVICE_ID_OUTOF_RANGE : Device id is out of range
  *
  *  @note   Given a device index, this function returns information about the camera device in a ITKDEV_INFO struct pointed to by pDI. The index parameter must be lower than the pCount parameter returned from ItkManGetDeviceCount().
  *  @see    ItkManGetDeviceCount   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetDeviceInfo(uint32_t index, PITKDEV_INFO pDI);

/**
*  @brief  Get information about gigevision spcecific device identified by its index.
*  @param[in]  index : Device index.
*  @param[out] pDI : Pointer to camera device info struct to fill.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG : Invalid input argument
*  - ITKSTATUS_DEVICE_ID_OUTOF_RANGE : Device id is out of range
*
*  @note   Given a device index, this function returns specific GigEVision information about the camera device in a ITKDEV_INFO struct pointed to by pDI. The index parameter must be lower than the pCount parameter returned from ItkManGetDeviceCount().
*  @see    ItkManGetDeviceCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetGigEDeviceInfo(uint32_t index, PITKGIGEDEV_INFO pDI);

/**
*  @brief  Get information about cameralink spcecific device identified by its index.
*  @param[in]  index : Device index.
*  @param[out] pDI : Pointer to camera device info struct to fill.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG : Invalid input argument
*  - ITKSTATUS_DEVICE_ID_OUTOF_RANGE : Device id is out of range
*
*  @note   Given a device index, this function returns specific CameraLink information about the camera device in a ITKDEV_INFO struct pointed to by pDI. The index parameter must be lower than the pCount parameter returned from ItkManGetDeviceCount().
*  @see    ItkManGetDeviceCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetCLDeviceInfo(uint32_t index, PITK_CL_DEV_INFO pDI);

/**
*  @brief  Get information about coaxpress spcecific device identified by its index.
*  @param[in]  index : Device index.
*  @param[out] pDI : Pointer to camera device info struct to fill.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG : Invalid input argument
*  - ITKSTATUS_DEVICE_ID_OUTOF_RANGE : Device id is out of range
*
*  @note   Given a device index, this function returns specific GigEVision information about the camera device in a ITKDEV_INFO struct pointed to by pDI. The index parameter must be lower than the pCount parameter returned from ItkManGetDeviceCount().
*  @see    ItkManGetDeviceCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetCXPDeviceInfo(uint32_t index, PITK_CXP_DEV_INFO pDI);


/**
*  @brief  Get information about USB3Vision spcecific device identified by its index.
*  @param[in]  index : Device index.
*  @param[out] pDI : Pointer to camera device info struct to fill.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG : Invalid input argument
*  - ITKSTATUS_DEVICE_ID_OUTOF_RANGE : Device id is out of range
*
*  @note   Given a device index, this function returns specific USB3Vision information about the camera device in a ITKDEV_INFO struct pointed to by pDI. The index parameter must be lower than the pCount parameter returned from ItkManGetDeviceCount().
*  @see    ItkManGetDeviceCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetU3VDeviceInfo(uint32_t index, PITK_U3V_DEV_INFO pDI);


/**
*  @brief  Get text strings for all the fields of a given status value.
*  @param[in]  status : ״̬��
*  @param[out] idBuf : ���������Ϣ
*				idBufSize : Result string size on input and buffer size needed on output
*				levelBuf : ���󼶱���Ϣ
*				levelBufSize : Result string size on input and buffer size needed on output
*				moduleBuf : ����ģ����Ϣ
*				moduleBufSize : Result string size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK �����ɹ�
*  - ITKSTATUS_ARG_OUT_OF_RANGE �������Խ��
*	 - ITKSTATUS_BUFFER_TOO_SMALL ���뻺����̫С
*  @note   Gets text strings for all the fields (ID, Level, and Module) of a given status value
*  @see
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkManGetStatusText(ITKSTATUS status, char* idBuf, uint32_t* idBufSize, char* levelBuf, uint32_t* levelBufSize, char* moduleBuf, uint32_t* moduleBufSize);

/**
  *  @brief  Open a device.
  *  @param[in]  index : Index of device info object  
  *  @param[in]  accessMode : Intended access mode. You can pass one or more of the flags specified below.
  *  @param[out] phDev : Pointer to result device handle.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKTATUS_ARG_NULL
  *  - ITKSTATUS_ARG_OUT_OF_RANGE
  *  - ITKSTATUS_INVALID_HANDLE
  *  - ITKSTATUS_NOT_ACCESSIBLE
  *  - ITKSTATUS_RESOURCE_IN_USE
  *
  *  @note   This function opens a device. A device must be opened before any operations can be performed on it. The accessMode argument can be used to restrict the type of access allowed by the device. The following access modes are available:
			ITKDEV_VAL_ACCESS_MODE_CONTROL - Allows to read or write camera parameters to configure the camera.
			ITKDEV_VAL_ACCESS_MODE_STREAM - Allows to read image data from the camera's stream grabber object.
			ITKDEV_VAL_ACCESS_MODE_EVENT - Allows to read event data from the camera's stream grabber object.
			ITKDEV_VAL_ACCESS_MODE_EXCLUSIVE - Allows exclusive access. When this flag is specified no other application may access the camera.
			ITKDEV_VAL_ACCESS_MODE_MONITOR - Allows only read access. This flag cannot be combined with any other flags. It is typically used in Multicast/Broadcast applications with GigE cameras.
			You can pass one or more flags. If you pass more than one flag you can combine them using the 'or' operator.
  *  @see    ItkDevClose   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevOpen(uint32_t index, int accessMode, ITKDEVICE *phDev);

/**
  *  @brief  Close a device.
  *  @param[in]  hDev : Device handle  
  *  @Return:    
  *  - ITKSTATUS_OK
  *
  *  @note   This function closes a device. After closing, the device can no longer be accessed.
  *  @see    ItkDevOpen
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevClose(ITKDEVICE hDev);

/**
*  @brief  Import the device configuration file
*  @param[in]  hDev : Device handle
*  @param[in]  lpFileName : configuration file name
*  @Return:
*  - ITKSTATUS_OK
*
*  @note   Import the device configuration file.
*  @see    ItkDevSaveConfigurationToFile
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevLoadConfigurationFromFile(ITKDEVICE hDev, char* lpFileName);

/**
*  @brief  Save the device configuration file
*  @param[in]  hDev : Device handle
*  @param[in]  lpFileName : configuration file name
*  @Return:
*  - ITKSTATUS_OK
*
*  @note   Save the device configuration file.
*  @see    ItkDevLoadConfigurationFromFile
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSaveConfigurationToFile(ITKDEVICE hDev, char* lpFileName);

/**
  *  @brief  Get the number of features supported by the device.
  *  @param[in]  hDev : Device handle
  *  @param[out] pCount : Number of features
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *  - Otherwise the return value will be any of error codes described in the section Error Codes.
  *
  *  @note   Returns the count of features supported by the device. Devices do not necessarily support the same feature set. For instance you can use this function to retrieve the number of features and then get information about those features using ItkDevGetFeatureInfo, using a feature index which can be any value in the range [0...count-1].
  *  @see    ItkDevGetFeatureInfo   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetFeatureCount(ITKDEVICE hDev, uint32_t* pCount);

/**
  *  @brief  Get the name of a feature associated with a specified index.
  *  @param[in]  hDev : Device Handle
  *  @param[in]  index : Index of the feature. All indices in the range [0 ... value returned by ItkDevGetFeatureCount �C 1] are valid.
  *  @param[out] name : Name of the feature associated with the specified index
  *  @param[in,out]  nameSize : Result buffer size on input and buffer size needed on output
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Get the number of features supported by the device.
  *  @see    ItkDevGetFeatureCount   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetFeatureName(ITKDEVICE hDev, uint32_t index, char* name, uint32_t* pNameSize);

/**
  *  @brief  Creates an feature object with a specific name.
  *  @param[in]  hDev : Device handle
  *  @param[in]  name : Feature name
  *  @param[out] phFeature : Feature resource handle to set/get feature information.
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Returns information on a feature associated with a specified name. All the information about the feature is stored in a ITKFEATURE object. The ITKFEATURE object contains the attributes of the feature such as name, type, range, and so forth.
  *  @see    ItkDevGetFeatureName ItkDevFreeFeature
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevAllocFeature(ITKDEVICE hDev, const char* name, ITKFEATURE* phFeature);

/**
  *  @brief  Destroys a feature object.
  *  @param[in]  hFeature : Feature handle.
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Destroys a feature object.
  *  @see    ItkDevAllocFeature   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevFreeFeature(ITKFEATURE hFeature);

/**
*  @brief  Get the number of streams supported by the device.
*  @param[in]  hDev : Device handle
*  @param[out] pCount : Number of streams
*  @Return:
*  - ITKSTATUS_OK if successful.
*  - Otherwise the return value will be any of error codes described in the section Error Codes.
*
*  @note   Returns the count of streams supported by the device. For GigeVision camera,there are must one stream channel at least, for CamerLink camera, there are should not have stream channel.
*  @see    ItkDevAllocStream
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetStreamCount(ITKDEVICE hDev, uint32_t* pCount);

/**
*  @brief  Creates an stream object with a specific index and buffer.
*  @param[in]  hDev : Device handle
*  @param[in]  index : Index of stream. All indices in the range [0 ... value returned by ItkDevGetStreamCount �C 1] are valid.
*  @param[in]  hBuffer : Buffer handle, default stream destination.
*  @param[out] phStream : Stream handle, control the whole life of streaming.
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return the handle of stream, a stream handle will transfer data from device specific channel to default buffer.
*  @see    ItkDevFreeStream
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevAllocStream(ITKDEVICE hDev, uint32_t index, ITKBUFFER hBuffer, ITKSTREAM* phStream);

/**
*  @brief  Destroys a stream object.
*  @param[in]  hStream : Stream handle.
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Destroys a stream object.
*  @see    ItkDevAllocStream
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevFreeStream(ITKSTREAM hStream);

/**
  *  @brief  Returns the number of events supported by the device.
  *  @param[in]  hDev : Device handle
  *  @param[out] pCount : Number of events
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Returns the number of events supported by the device. Devices do not necessarily support the same event set. For instance you can use this function to retrieve the number of events and then get the name of those event using ItkDevGetEventName, using an event index which can be any value in the range [0...pCount-1].
  *  @see    ItkDevGetEventName   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetEventCount(ITKDEVICE hDev, uint32_t* pCount);

/**
  *  @brief  Returns the name of an event associated with a specified index.
  *  @param[in]  hDev : Device handle
  *  @param[in]  index : Index of the event. All indices in the range [0 ... value returned by ItkDevGetEventCount �C 1] are valid.
  *  @param[out]  pEventName : Name of the event associated with the specified index
  *  @param[in,out] pNameSize : Result buffer size on input and buffer size needed on output
  *  @Return:
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Returns the name of an event associated with a specified index. The typical usage is converting an event index (retrieved from your callback information) to the corresponding name. You can then sort the events by name in order to call the appropriate event handling code.
  *  @see    ItkDevGetEventCount   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetEventName(ITKDEVICE hDev, uint32_t index, char* pEventName, uint32_t* pNameSize);

/**
*  @brief  Returns whether or not an event is supported by the device.
*  @param[in]  hDev : Device handle
*  @param[int]  pEventName : Name of the event associated with the specified index
*  @param[out] bAvailable : true if the event is supported by the device. false otherwise
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns whether or not an event is supported by the device.
*  @see    ItkDevGetEventCount,ItkDevGetEventName
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevIsEventAvailable(ITKDEVICE hDev, const char* pEventName, _Bool* bAvailable);

/**
*  @brief  Registers a callback function on the event associated with a specified name.
*  @param[in]  hDev : Device handle
*  @param[in]  pEventName : Name of the event associated with the specified index
*  @param[in]  callback : Address of a user callback function of the following form:
			   void IKAPC_CC MyCallback(void *context, ITKEVENTINFO hEventInfo)
			   {
			   }
*  @param[in] pContext : Pointer to a user storage (that is, variable, structure, buffer, etc). Can be NULL.
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   This function is not valid for read-only handles.
*  @see    ItkDevUnregisterCallback
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevRegisterCallback(ITKDEVICE hDev, const char* pEventName, PITKEVENTINFOCALLBACK callback, void *pContext);

/**
*  @brief  Unregisters a callback function on the event associated with a specified name.
*  @param[in]  hDev : Device handle
*  @param[in]  pEventName : Name of the event associated with the specified index
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   This function is not valid for read-only handles.
*  @see    ItkDevRegisterCallback
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevUnregisterCallback(ITKDEVICE hDev, const char* pEventName);

/**
*  @brief  Get device parameter value from a device object.
*  @param[in]  hDev : Device handle
*  @param[in]  prm : Device parameter requested
*  @param[out] pValue : Current value of the parameter
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Gets device parameter value from a device object
*  @see    ItkDevSetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetPrm(ITKDEVICE hDev, uint32_t prm, void* pValue);

/**
*  @brief  Set device parameter value from a device object.
*  @param[in]  hDev : Device handle
*  @param[in]  prm : Device parameter requested
*  @param[out] value : New value of the parameter
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Sets device parameter value from a device object
*  @see    ItkDevGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSetPrm(ITKDEVICE hDev, uint32_t prm, const void* value);

/**
*  @brief  Perform a raw read on the standard "Device"-node port.
*  @param[in]  hDev : Device handle.
*  @param[in]  pBuffer : Points to the buffer to copy the data to.
*  @param[in]  address : Address to start reading data from.
*  @param[in]  length : Number of bytes to read starting at Address.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Reads raw data from the "Device" port. Specify the address from where to read data. The count of data bytes passed in Length is read. 
           The data read will be written to the buffer passed in pBuffer. Make sure the buffer has at least a size of Length-bytes. 
*  @see    ItkDevPortWrite
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevPortRead(ITKDEVICE hDev, void* pBuffer, uint64_t address, uint32_t length);

/**
*  @brief  Perform a raw write on the standard "Device"-node port.
*  @param[in]  hDev : Device handle.
*  @param[in]  pBuffer : Points to the buffer to copy the data to.
*  @param[in]  address : Address to start writing data from.
*  @param[in]  length : Number of bytes to write starting at Address.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Write raw data from the "Device" port. Specify the address from where to read data. The count of data bytes passed in Length is read.
The data read will be written to the buffer passed in pBuffer. Make sure the buffer has at least a size of Length-bytes.
*  @see    ItkDevPortWrite
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevPortWrite(ITKDEVICE hDev, const void* pBuffer, uint64_t address, uint32_t length);

/**
*  @brief  Perform a raw read on the standard "Device"-node serial port.
*  @param[in]  hDev : Device handle.
*  @param[out]  pBuffer : Points to the buffer to copy the data to.
*  @param[out]  length : Number of bytes to read starting at Address.
*  @param[in]  timeout : read timeout.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Reads raw data from the "Device" serial port. Specify the address from where to read data. The count of data bytes passed in Length is read.
           The data read will be written to the buffer passed in pBuffer. Make sure the buffer has at least a size of Length-bytes.
*  @see    ItkDevPortWrite
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSerialPortRead(ITKDEVICE hDev, void* pBuffer, uint32_t* length,uint32_t timeout);

/**
*  @brief  Perform a raw write on the standard "Device"-node serial port.
*  @param[in]  hDev : Device handle.
*  @param[in]  pBuffer : Points to the buffer to copy the data to.
*  @param[in]  length : Number of bytes to write starting at Address.
*  @param[in]  timeout : write timeout.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Write raw data from the "Device" port. Specify the address from where to read data. The count of data bytes passed in Length is read.
           The data read will be written to the buffer passed in pBuffer. Make sure the buffer has at least a size of Length-bytes.
*  @see    ItkDevPortWrite
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSerialPortWrite(ITKDEVICE hDev, const void* pBuffer, uint32_t length, uint32_t timeout);

/**
*  @brief  'Force' a static IP address configuration into a device identified by its MAC Address.
*  @param[in]  pMacAddress : MAC address as a string, "- notation". e.g., 00-30-53-06-1a-58
*  @param[in]  pIpAddress :  Temporary IP address, "dot notation", e.g., 192.168.1.2
*  @param[in]  pSubnetMask  :  Temporary SubnetMask, "dot notation", eg. 255.255.255.0
*  @param[in]  pDefaultGateway : Temporary DefaultGateway, "dot notation", e.g., 192.168.1.1
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note  When calling this function, there must be no opened camera object for the device to reconfigure! 
*         ItkManGetGigEDeviceInfo can be used to retrieve the MAC Address.
*  @see    ItkDevGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkGigEDevForceIp(const char* pMacAddress, const char* pIpAddress, const char* pSubnetMask, const char* pDefaultGateway);

/**
*  @brief  Reads the persistent IP address from the device.
*  @param[in]     hDev : Device handle.
*  @param[in]     pIpAddress :  Persistent IP address, "dot notation", e.g., 192.168.1.2
*  @param[in,out] pIpAddressLen : Pointer to buffer length
*  @param[in]     pSubnetMask  :  Persistent SubnetMask, "dot notation", eg. 255.255.255.0
*  @param[in,out] pSubnetMaskLen  : Pointer to buffer length
*  @param[in]     pDefaultGateway : Persistent DefaultGateway, "dot notation", e.g., 192.168.1.1
*  @param[in,out] pDefaultGatewayLen  : Pointer to buffer length
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note  Reads the persistent IP address from the device.
*  @see   ItkGigEDevSetPersistentIpAddress
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkGigEDevGetPersistentIpAddress(ITKDEVICE hDev, char* pIpAddress, uint32_t* pIpAddressLen, char* pSubnetMask, uint32_t* pSubnetMaskLen, char* pDefaultGateway, uint32_t* pDefaultGatewayLen);

/**
*  @brief  Writes the persistent IP address to the device.
*  @param[in]     hDev : Device handle.
*  @param[in]     pIpAddress :  Persistent IP address, "dot notation", e.g., 192.168.1.2
*  @param[in]     pSubnetMask  :  Persistent SubnetMask, "dot notation", eg. 255.255.255.0
*  @param[in]     pDefaultGateway : Persistent DefaultGateway, "dot notation", e.g., 192.168.1.1
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Writes the persistent IP address from the device.
*  @see    ItkGigEDevGetPersistentIpAddress
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkGigEDevSetPersistentIpAddress(ITKDEVICE hDev, const char* pIpAddress, const char* pSubnetMask, const char* pDefaultGateway);

/**
*  @brief  Get parameter from an event info.
*  @param[in]  hEventInfo : Event info handle
*  @param[in]  prm : Event info parameter requested
*  @param[out] value : Value of the parameter
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Sets device parameter value from a device object
*  @see    ItkDevGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkEventInfoGetPrm(ITKEVENTINFO hEventInfo, uint32_t prm, void* value);

/**
  *  @brief  Query feature for allowed access modes
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] pAccessMode : Pointer to variable receiving access mode 
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   The value returned in the variable pointed to by pAccessMode indicates what kinds of access are allowed for the node referred to by hFeature.
  *  @see    ItkDevAllocFeature  
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetAccessMode(ITKFEATURE hFeature, uint32_t* pAccessMode);

/**
*  @brief  Query feature for allowed access modes
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pAccessMode : Pointer to variable receiving access mode
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   The value returned in the variable pointed to by pAccessMode indicates what kinds of access are allowed for the node referred to by hFeature.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetAccessMode(ITKDEVICE hDev, const char* featureName, uint32_t* pAccessMode);

/**
  *  @brief  Represents the category of features the current feature belongs to. All the features are divided into categories to simplify the presentation of features coming from a large feature set.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out]  pCategory : 
  *  @param[out]  pBufferSize : Result buffer size on input and buffer size needed on output
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   
  *  @see    ItkFeatureGetAccessMode  
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetCategory(ITKFEATURE hFeature, char* pCategory, uint32_t* pBufferSize);

/**
*  @brief  Represents the category of features the current feature belongs to. All the features are divided into categories to simplify the presentation of features coming from a large feature set.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out]  pCategory :
*  @param[out]  pBufferSize : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetCategory(ITKDEVICE hDev, const char* featureName, char* pCategory, uint32_t* pBufferSize);

/**
  *  @brief  Get feature type.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] pType : Result pointer
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Query the feature represented by hFeature for its type.
  *  @see    ItkFeatureGetAccessMode   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetType(ITKFEATURE hFeature, uint32_t* pType);

/**
*  @brief  Get feature type.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pType : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its type.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetType(ITKDEVICE hDev, const char* featureName, uint32_t* pType);

/**
  *  @brief  Get feature display name.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] name : Feature display name
  *  @param[in,out]  nameSize : Result buffer size on input and buffer size needed on output
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Get feature display name.
  *  @see    ItkFeatureGetAccessMode 
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDisplayName(ITKFEATURE hFeature, char* featureName, uint32_t* pNameSize);

/**
*  @brief  Get feature display name.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] featureDisplayName : Feature display name
*  @param[in,out]  nameSize : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Get feature display name.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDisplayName(ITKDEVICE hDev, const char* featureName, char* featureDisplayName, uint32_t* pNameSize);

/**
*  @brief  Return a feature's tool tip  text.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pBuff : Buffer to receive result
*  @param[in,out]  pBufLen : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its associated 'tool tip' text. This is a text string briefly describing the node and its purpose, suitable for being displayed as a pop-up by interactive programs that offer access to the node. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
*  @see    ItkFeatureGetDescription
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetTooltip(ITKFEATURE hFeature, char* pBuff, uint32_t* pBufLen);

/**
*  @brief  Return a feature's tool tip  text.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pBuff : Buffer to receive result
*  @param[in,out]  pBufLen : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its associated 'tool tip' text. This is a text string briefly describing the node and its purpose, suitable for being displayed as a pop-up by interactive programs that offer access to the node. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetTooltip(ITKDEVICE hDev, const char* featureName, char* pBuff, uint32_t* pBufLen);

/**
  *  @brief  Return a feature's description text.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] pBuff : Buffer to receive result 
  *  @param[in,out]  pBufLen : Result buffer size on input and buffer size needed on output  
  *  @Return:
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Query the feature represented by hFeature for its associated 'description' text. This is a text string describing the node and its purpose in some more detail than ItkFeatureGetTooltip(), suitable for being displayed as an on-line help by interactive programs that offer access to the node. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
  *  @see    ItkFeatureGetTooltip   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDescription(ITKFEATURE hFeature, char* pBuff, uint32_t* pBufLen);

/**
*  @brief  Return a feature's description text.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pBuff : Buffer to receive result
*  @param[in,out]  pBufLen : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its associated 'description' text. This is a text string describing the node and its purpose in some more detail than ItkFeatureGetTooltip(), suitable for being displayed as an on-line help by interactive programs that offer access to the node. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDescription(ITKDEVICE hDev, const char* featureName, char* pBuff, uint32_t* pBufLen);

/**
  *  @brief  Return a feature's name space.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] pNameSpace : Pointer to variable receiving name space
  *  @Return:
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Query the feature represented by hFeature for the name space (custom or standard) it belongs to.
  *  @see    ItkDevGetFeatureCount   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetNameSpace(ITKFEATURE hFeature, uint32_t* pNameSpace);

/**
*  @brief  Return a feature's name space.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pNameSpace : Pointer to variable receiving name space
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for the name space (custom or standard) it belongs to.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetNameSpace(ITKDEVICE hDev, const char* featureName, uint32_t* pNameSpace);

/**
*  @brief  Get feature visibility.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pVis : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its visibility.
*  @see    ItkFeatureGetAccessMode
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetVisibility(ITKFEATURE hFeature, uint32_t* pVis);

/**
*  @brief  Get feature visibility.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pVis : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its visibility.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetVisibility(ITKDEVICE hDev, const char* featureName, uint32_t* pVis);

/**
*  @brief  Get feature representation.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pRep : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its representation.
*  @see    ItkFeatureGetAccessMode
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetRepresentation(ITKFEATURE hFeature, uint32_t* pRep);

/**
*  @brief  Get feature representation.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pRep : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Query the feature represented by hFeature for its representation.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetRepresentation(ITKDEVICE hDev, const char* featureName, uint32_t* pRep);

/**
  *  @brief  Return an integer feature's minimum value.
  *  @param[in]  hFeature : Feature handle to operate on
  *  @param[out] pValue : Result pointer 
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Return its minimum value in the variable pointed to by pValue
  *  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt32Min(ITKFEATURE hFeature, int32_t* pValue);

/**
*  @brief  Return an integer feature's minimum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its minimum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt32Min(ITKDEVICE hDev, const char* featureName, int32_t* pValue);

/**
*  @brief  Return an integer feature's maximum value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt32Max(ITKFEATURE hFeature, int32_t* pValue);

/**
*  @brief  Return an integer feature's maximum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt32Max(ITKDEVICE hDev, const char* featureName, int32_t* pValue);

/**
*  @brief  Return an integer feature's increment value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt32Inc(ITKFEATURE hFeature, int32_t* pValue);

/**
*  @brief  Return an integer feature's increment value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt32Inc(ITKDEVICE hDev, const char* featureName, int32_t* pValue);

/**
*  @brief  Return an integer feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt32(ITKFEATURE hFeature, int32_t* pValue);

/**
*  @brief  Return an integer feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt32(ITKDEVICE hDev, const char* featureName, int32_t* pValue);

/**
*  @brief  Set an integer feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetInt32Min()..ItkFeatureGetInt32Max(). The value must also be ItkFeatureGetInt32Min() + N * ItkFeatureGetInt32Inc() with N = 0,1,2,3,...
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureSetInt32(ITKFEATURE hFeature, int32_t value);

/**
*  @brief  Set an integer feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetInt32Min()..ItkFeatureGetInt32Max(). The value must also be ItkFeatureGetInt32Min() + N * ItkFeatureGetInt32Inc() with N = 0,1,2,3,...
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSetInt32(ITKDEVICE hDev, const char* featureName, int32_t value);

/**
*  @brief  Return an integer feature's minimum value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its minimum value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt64Min(ITKFEATURE hFeature, int64_t* pValue);

/**
*  @brief  Return an integer feature's minimum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its minimum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt64Min(ITKDEVICE hDev, const char* featureName, int64_t* pValue);

/**
*  @brief  Return an integer feature's maximum value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt64Max(ITKFEATURE hFeature, int64_t* pValue);

/**
*  @brief  Return an integer feature's maximum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt64Max(ITKDEVICE hDev, const char* featureName, int64_t* pValue);

/**
*  @brief  Return an integer feature's increment value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt64Inc(ITKFEATURE hFeature, int64_t* pValue);

/**
*  @brief  Return an integer feature's increment value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt64Inc(ITKDEVICE hDev, const char* featureName, int64_t* pValue);

/**
*  @brief  Return an integer feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetInt64(ITKFEATURE hFeature, int64_t* pValue);

/**
*  @brief  Return an integer feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetInt64(ITKDEVICE hDev, const char* featureName, int64_t* pValue);

/**
*  @brief  Set an integer feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetInt64Min()..ItkFeatureGetInt64Max(). The value must also be ItkFeatureGetInt64Min() + N * ItkFeatureGetInt64Inc() with N = 0,1,2,3,...
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureSetInt64(ITKFEATURE hFeature, int64_t value);

/**
*  @brief  Set an integer feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetInt64Min()..ItkFeatureGetInt64Max(). The value must also be ItkFeatureGetInt64Min() + N * ItkFeatureGetInt64Inc() with N = 0,1,2,3,...
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSetInt64(ITKDEVICE hDev, const char* featureName, int64_t value);

/**
*  @brief  Return an 64bit floating feature's minimum value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its minimum value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDoubleMin(ITKFEATURE hFeature, double* pValue);

/**
*  @brief  Return an 64bit floating feature's minimum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its minimum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDoubleMin(ITKDEVICE hDev, const char* featureName, double* pValue);

/**
*  @brief  Return a 64bit floating feature's maximum value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDoubleMax(ITKFEATURE hFeature, double* pValue);

/**
*  @brief  Return a 64bit floating feature's maximum value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its maximum value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDoubleMax(ITKDEVICE hDev, const char* featureName, double* pValue);

/**
*  @brief  Return a 64bit floating feature's increment value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDoubleInc(ITKFEATURE hFeature, double* pValue);

/**
*  @brief  Return a 64bit floating feature's increment value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its increment value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDoubleInc(ITKDEVICE hDev, const char* featureName, double* pValue);

/**
*  @brief  Return a 64bit floating feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetDouble(ITKFEATURE hFeature, double* pValue);

/**
*  @brief  Return a 64bit floating feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetDouble(ITKDEVICE hDev, const char* featureName, double* pValue);

/**
*  @brief  Set a 64bit floating feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] value : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetFloatMin()..ItkFeatureGetFloatMax(). 
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureSetDouble(ITKFEATURE hFeature, double value);

/**
*  @brief  Set a 64bit floating feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] value : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must obey certain rules which may vary from feature to feature. The value must be in the range ItkFeatureGetFloatMin()..ItkFeatureGetFloatMax().
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSetDouble(ITKDEVICE hDev, const char* featureName, double value);

/**
*  @brief  Return a bool feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetBool(ITKFEATURE hFeature, _Bool* pValue);

/**
*  @brief  Return a bool feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value in the variable pointed to by pValue
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetBool(ITKDEVICE hDev, const char* featureName, _Bool* pValue);

/**
*  @brief  Set a bool feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must be true or false.
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureSetBool(ITKFEATURE hFeature, _Bool value);

/**
*  @brief  Set a bool feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Result pointer
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from argument value. The value must be true or false.
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevSetBool(ITKDEVICE hDev, const char* featureName, _Bool value);

/**
*  @brief  Set a bool feature's value.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pBuff : Pointer to string buffer receiving result 
*  @param[in,out]  pBuffLen : Result buffer size on input and buffer size needed on output 
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value as string. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureToString(ITKFEATURE hFeature, char* pBuff, uint32_t* pBuffLen);

/**
*  @brief  Set a bool feature's value.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pBuff : Pointer to string buffer receiving result
*  @param[in,out]  pBuffLen : Result buffer size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Return its value as string. The buffer passed to this function must be large enough to hold the entire string, including a terminating zero. If the function is called with pBuf set to NULL, the variable pointed to by pBufLen is set to the required buffer size.
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevToString(ITKDEVICE hDev, const char* featureName, char* pBuff, uint32_t* pBuffLen);

/**
*  @brief  Set a feature's value from a string.
*  @param[in]  hFeature : Feature handle to operate on
*  @param[out] pValue : Pointer to string argument
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from the argument string value.
*  @see    ItkFeatureGetAccessMode,ItkFeatureGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureFromString(ITKFEATURE hFeature, const char* pValue);

/**
*  @brief  Set a feature's value from a string.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Pointer to string argument
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Set its value from the argument string value.
*  @see    ItkDevGetAccessMode,ItkDevGetType
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevFromString(ITKDEVICE hDev, const char* featureName, const char* pValue);

/**
  *  @brief  Returns the number of items in an enumeration.
  *  @param[in]  hFeature : Feature handle
  *  @param[out] count : Number of items in the enumeration
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Returns the number of items in an enumeration. Use this function along with ItkFeatureGetEnumString to enumerate all the items contained within an enumeration feature.
  *  @see    ItkFeatureGetEnumString   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetEnumCount(ITKFEATURE hFeature, uint32_t* pValue);

/**
*  @brief  Returns the number of items in an enumeration.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] count : Number of items in the enumeration
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns the number of items in an enumeration. Use this function along with ItkFeatureGetEnumString to enumerate all the items contained within an enumeration feature.
*  @see    ItkDevGetEnumString
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetEnumCount(ITKDEVICE hDev, const char* featureName, uint32_t* pValue);

/**
*  @brief  Returns the enumeration string corresponding to a specified index.
*  @param[in]  hFeature : Feature handle
*  @param[in]  index : Index of the enumeration item. Ranges from 0 to ItkFeatureGetEnumCount - 1
*  @param[out]  enumString : String associated with the item specified by index
*  @param[in,out] stringSize : Result string size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns the enumeration string corresponding to a specified index.
*  @see    ItkFeatureGetEnumCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetEnumString(ITKFEATURE hFeature, uint32_t index, char* enumString, uint32_t* pStringSize);

/**
*  @brief  Returns the enumeration string corresponding to a specified index.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[in]  index : Index of the enumeration item. Ranges from 0 to ItkFeatureGetEnumCount - 1
*  @param[out]  enumString : String associated with the item specified by index
*  @param[in,out] stringSize : Result string size on input and buffer size needed on output
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns the enumeration string corresponding to a specified index.
*  @see    ItkDevGetEnumCount
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetEnumString(ITKDEVICE hDev, const char* featureName, uint32_t index, char* enumString, uint32_t* pStringSize);

/**
*  @brief  Returns whether or not the enumeration item corresponding to a specified index is available.
*  @param[in]  hFeature : Feature handle
*  @param[in]  enumString : String to look for in the enumeration items
*  @param[out] bAvailable : true if the item is available, false otherwise.
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns the number of items in an enumeration. Use this function along with ItkFeatureGetEnumString to enumerate all the items contained within an enumeration feature.
*  @see    ItkFeatureGetEnumString
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetEnumIsAvailable(ITKFEATURE hFeature, const char* enumString, _Bool* bAvailable);

/**
*  @brief  Returns whether or not the enumeration item corresponding to a specified index is available.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[in]  enumString : String to look for in the enumeration items
*  @param[out] bAvailable : true if the item is available, false otherwise.
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Returns the number of items in an enumeration. Use this function along with ItkFeatureGetEnumString to enumerate all the items contained within an enumeration feature.
*  @see    ItkDevGetEnumString
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetEnumIsAvailable(ITKDEVICE hDev, const char* featureName, const char* enumString, _Bool* bAvailable);

/**
*  @brief  Execute a command.
*  @param[in]  hFeature : Feature handle
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Try to execute feature's command.
*  @see    
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureExecuteCommand(ITKFEATURE hFeature);

/**
*  @brief  Execute a command.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Try to execute feature's command.
*  @see
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevExecuteCommand(ITKDEVICE hDev, const char* featureName);

/**
  *  @brief  Indicates if that node is a selector
  *  @param[in]  hFeature : Feature handle
  *  @param[out] bSelector : true or false 
  *  @Return:    
  *	 - ITKSTATUS_OK �����ɹ�
  *  - ITKSTATUS_INVALID_HANDLE Invalid handle
  *
  *
  *  @note   Indicates if that node is a selector, when a selector node changes value, the selected node should 
   *		 refresh its value
  *  @see    ItkFeatureGetSelectedFeatureCounts  
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureIsSelector(ITKFEATURE hFeature, _Bool* bSelector);

/**
*  @brief  Indicates if that node is a selector
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] bSelector : true or false
*  @Return:
*	 - ITKSTATUS_OK �����ɹ�
*  - ITKSTATUS_INVALID_HANDLE Invalid handle
*
*
*  @note   Indicates if that node is a selector, when a selector node changes value, the selected node should
*		 refresh its value
*  @see    ItkDevGetSelectedFeatureCounts
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevIsSelector(ITKDEVICE hDev, const char* featureName, _Bool* bSelector);

/**
  *  @brief  Return the number of selected nodes.
  *  @param[in]  hFeature : Feature handle
  *  @param[out] pValue : Selected feature counts
  *  @Return:    
  *	 - ITKSTATUS_OK �����ɹ�
  *  - ITKSTATUS_INVALID_HANDLE Invalid handle
  *
  *  @note   Returns the number of nodes selected by this feature.
  *  @see    ItkFeatureIsSelector  
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetSelectedFeatureCounts(ITKFEATURE hFeature, uint32_t* pValue);

/**
*  @brief  Return the number of selected nodes.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pValue : Selected feature counts
*  @Return:
*	 - ITKSTATUS_OK �����ɹ�
*  - ITKSTATUS_INVALID_HANDLE Invalid handle
*
*  @note   Returns the number of nodes selected by this feature.
*  @see    ItkDevIsSelector
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetSelectedFeatureCounts(ITKDEVICE hDev, const char* featureName, uint32_t* pValue);

/**
  *  @brief  Get a selected feature name by its index.
  *  @param[in]  hFeature : Feature handle
  *  @param[in]  index : Selected feature index
  *  @param[out] pBuf : Selected feature name specified by index
  *  @param[out] pBufLen :
  *  @Return:    
  *	 - ITKSTATUS_OK �����ɹ�
  *  - ITKSTATUS_INVALID_HANDLE Invalid handle
  *
  *  @note   Get a selected feature name by its index
  *  @see    ItkFeatureIsSelector   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetSelectedFeatureName(ITKFEATURE hFeature, uint32_t index, char* pBuf, uint32_t* pBufLen);

/**
*  @brief  Get a selected feature name by its index.
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[in]  index : Selected feature index
*  @param[out] pBuf : Selected feature name specified by index
*  @param[out] pBufLen :
*  @Return:
*	 - ITKSTATUS_OK �����ɹ�
*  - ITKSTATUS_INVALID_HANDLE Invalid handle
*
*  @note   Get a selected feature name by its index
*  @see    ItkDevIsSelector
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetSelectedFeatureName(ITKDEVICE hDev, const char* featureName, uint32_t index, char* pBuf, uint32_t* pBufLen);

/**
  *  @brief  Get the interval of time between two consecutive feature updates
  *  @param[in]  hFeature : Feature handle
  *  @param[out] pPollingTime : Point to the interval of polling time
  *  @Return:    
  *  - ITKSTATUS_OK if successful.
  *
  *  @note   Get the interval of time between two consecutive feature updates. Some read-only features such as ��Sensor Temperature" for instance must be read from the device at a certain frequency in order to refresh to feature module.
  *  @see    ItkFeatureAlloc  
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkFeatureGetPollingTime(ITKFEATURE hFeature, uint32_t* pPollingTime);

/**
*  @brief  Get the interval of time between two consecutive feature updates
*  @param[in]  hDev : Device handle
*  @param[in]  featureName : Feature name
*  @param[out] pPollingTime : Point to the interval of polling time
*  @Return:
*  - ITKSTATUS_OK if successful.
*
*  @note   Get the interval of time between two consecutive feature updates. Some read-only features such as ��Sensor Temperature" for instance must be read from the device at a certain frequency in order to refresh to feature module.
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkDevGetPollingTime(ITKDEVICE hDev, const char* featureName, uint32_t* pPollingTime);

/**
  *  @brief  Stop stream transfer asynchronously for a stream resource.
  *  @param[in]  hStream : Stream handle
  *  @param[out] None.
  *  @Return:    
  *  ITKSTATUS_OK 
  *	 ITKSTATUS_INVALID_HANDLE
  *
  *  @note   Stops stream asynchronously for a stream resource.On return, transfer is finished but part of the last transferred frame may be corrupted.
  *  @see    ItkStreamStop   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamAbort(ITKSTREAM hStream);

/**
  *  @brief  Append buffer to the tail of stream destination.
  *  @param[in]	hStream : Stream handle. 
  *  @param[in] hBuffer : Buffer handle to append.
  *  @Return:    
  *  ITKSTATUS_OK  
  *
  *  @note   ��Stream�����ӻ���������ӵĻ���������ӵ�ĩβλ�á�
  *  @see    ItkStreamRemoveBuffer   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamAddBuffer(ITKSTREAM hStream, ITKBUFFER hBuffer);

/**
*  @brief  Remove buffer from stream buffer list.
*  @param[in] hStream : Stream handle.
*  @param[in] hBuffer : Buffer handle to remove.
*  @Return:
*  ITKSTATUS_OK
*
*  @note   ɾ��Stream�������б��е�ָ�����塣
*  @see    ItkStreamAddBuffer
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamRemoveBuffer(ITKSTREAM hStream, ITKBUFFER hBuffer);

/**
*  @brief  Clear buffer status.
*  @param[in] hStream : Stream handle.
*  @param[in] hBuffer : Buffer handle to remove.
*  @Return:
*  ITKSTATUS_OK
*
*  @note   �����������������״̬�����������Զ���ջ��ƽ��õ������
*  @see    ItkStreamAddBuffer
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamClearBuffer(ITKSTREAM hStream, ITKBUFFER hBuffer);

/**
  *  @brief  Get stream parameter value from a stream resource.
  *  @param[in]  hStream : Stream handle
  *  @param[in]  prm : Stream parameter requested
  *  @param[out] pValue : Current value of the parameter
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_ARG_INVALID
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   Gets stream parameter value from a stream resource
  *  @see    ItkStreamSetPrm
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamGetPrm(ITKSTREAM hStream, uint32_t prm, void* pValue);

/**
*  @brief  Set stream parameter value from a stream resource.
*  @param[in]  hStream : Stream handle
*  @param[in]  prm : Stream parameter requested
*  @param[out] value : New value of the parameter
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_ARG_INVALID
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Sets stream parameter value from a stream resource
*  @see    ItkStreamGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamSetPrm(ITKSTREAM hStream, uint32_t prm, const void* value);

/**
  *  @brief  Start stream image for a transfer resource.
  *  @param[in]  hStream : Stream object handle
  *  @param[in]  count : Numerical value within [1...] or ITKSTREAM_CONTINUOUS
  *  @param[out] None
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   For stopping a transfer started in continuous mode, ItkStreamStop must first be called to flag the end of the transfer.
  *  @see    ItkStreamStop   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamStart(ITKSTREAM hStream, uint32_t count);

/**
*  @brief  Stop stream image for a transfer resource.
*  @param[in]  hStream : Stream object handle
*  @param[out] None
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Stops transfer synchronously for a transfer resource. Transfer will be stopped at the end of the current frame; therefore, last transferred frame is valid.
*  @see	   ItkStreamAbort
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamStop(ITKSTREAM hStream);

/**
*  @brief  Wait stream image for a transfer resource.
*  @param[in]  hStream : Stream object handle
*  @param[out] None
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Wait transfer synchronously for a transfer resource.
*  @see	   ItkStreamStart
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamWait(ITKSTREAM hStream);

/**
  *  @brief  Register callback function for a stream resource.
  *  @param[in]  hStream : Stream resource handle
  *  @param[in]  eventType : Type of event to register. The callback function will be called when the specified event(s) occur. 
  *  @param[in]  callback : Callback function must be defined as follow:
						void IKAPC_CC callback (UINT32 eventType, void *context);
  *  @param[in]  context : Context pointer to be passed to the callback function when called
  *  @param[out] None.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   The values may be ORed if more than one event is desired. When used, ITKSTREAM_VAL_EVENT_TYPE_END_OF_LINE must be ORed with an unsigned integer representing the line on which the callback function has to be called, while ITKSTREAM_VAL_EVENT_TYPE_END_OF_NLINES must be ORed with an unsigned integer representing the number of lines after which the callback function has to be called.
  *  @see    ItkStreamUnregisterCallback   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamRegisterCallback(ITKSTREAM hStream, uint32_t eventType, PITKSTREAMCALLBACK callback, void* context);

/**
  *  @brief  Unregister callback function for a stream resource.
  *  @param[in]  hStream : Stream resource handle
  *  @param[in]  eventType : Type of event to unregister.
  *  @param[out] None.
  *  @Return:    
  *  - ITKSTATUS_OK 
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   Unregister callback function for a stream resource
  *  @see    ItkStreamRegisterCallback   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkStreamUnregisterCallback(ITKSTREAM hStream, uint32_t eventType);

/**
  *  @brief  Create a new buffer resource.
  *  @param[in]  width : Width of new buffer in pixels 
  *  @param[in]  height : Height of new buffer in pixels
  *  @param[in]  format : See Data Formats for detailed format descriptions.
  *  @param[out] phBuffer : Buffer resource handle
  *  @Return:    
  *  - ITKSTATUS_OK 
  *  - ITKSTATUS_INVALID_ARG
  *  - ITKSTATUS_NO_MEMORY
  *
  *  @note   
  *  @see    ItkBufferFree   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferNew(int64_t width, int64_t height, uint32_t format, ITKBUFFER* phBuffer);

/**
  *  @brief  Free a buffer resource.
  *  @param[in] hBuffer : Buffer resource handle
  *  @param[out] None
  *  @Return:
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   
  *  @see    ItkBufferNew
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferFree(ITKBUFFER hBuffer);

/**
  *  @brief  Gets buffer parameter value from a buffer resource.
  *  @param[in]  hBuffer : Buffer resource handle
  *  @param[in]  prm : Buffer parameter requested
  *  @param[out] pValue : Current value of the parameter.
  *  @Return:    
  *  - ITKSTATUS_OK 
  *  - ITKSTATUS_IVNALID_ARG
  *
  *  @note   Get the buffer parameter value from a buffer resource. See the section Parameters for a descriptive list of all buffer parameters
  *  @see    ItkBufferSetPrm   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferGetPrm(ITKBUFFER hBuffer, uint32_t prm, void* pValue);

/**
  *  @brief  Set a simple buffer parameter of a buffer resource.
  *  @param[in]  hBuffer : Buffer resource handle
  *  @param[in]  prm : Buffer parameter to set
  *  @param[out] None.
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALID_HANDLE
  *
  *  @note   Set the buffer parameter value to a buffer resource.
  *  @see    ItkBufferGetPrm   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferSetPrm(ITKBUFFER hBuffer, uint32_t prm, const void* value);

/**
  *  @brief  Read a series of elements from a buffer resource.
  *  @param[in]  hBuffer : Buffer resource handle
  *  @param[in]  offset : Offset to seek within the buffer prior to read (in pixels)
  *  @param[in]  size : Size of transfer.
  *  @param[out] data : Array which can accommodate the requested size (number of elements �� ITKBUFFER_PRM_DATASIZE).
  *  @Return:    
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALD_ARG
  *
  *  @note   Reading elements from video memory buffers may be very slow.
  *  @see    ItkBufferWrite   
  */
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferRead(ITKBUFFER hBuffer, uint32_t offset, void* data, uint32_t size);

/**
*  @brief  Read an element from a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  posX : Horizontal position of the element in the buffer.
*  @param[in]  posY : Vertical position of the element in the buffer.
*  @param[in]  element : Value of the specified position.
*  @param[in]  size : Size of transfer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALD_ARG
*  - ITKSTATUS_IVNALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Reading elements from video memory buffers may be very slow.
*  @see    ItkBufferWriteElement
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferReadElement(ITKBUFFER hBuffer, uint32_t posX, uint32_t posY, void* element, uint32_t size);

/**
*  @brief  Read a set of linearly positioned elements from a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  startX : Horizontal position of first element to read.
*  @param[in]  startY : Vertical position of first element to read.
*  @param[in]  endX : Horizontal position of last element to read.
*  @param[in]  endY : Vertical position of last element to read.
*  @param[in]  array : Array which can accommodate the requested number of elements.
*  @param[in]  uElements : Number of elements read.
*  @param[in]  size : Size of transfer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALD_ARG
*  - ITKSTATUS_IVNALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Reading elements from video memory buffers may be very slow.
*  @see    ItkBufferWriteLine
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferReadLine(ITKBUFFER hBuffer, uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY, uint32_t* uElements, void* data, uint32_t size);

/**
*  @brief  Read a set of elements forming a rectangular area from a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  offsetX : Horizontal position of first element to read.
*  @param[in]  offsetY : Vertical position of first element to read.
*  @param[in]  width : Horizontal length of the rectangle.
*  @param[in]  height : Vertical length of the rectangle.
*  @param[in]  data : Array which can accommodate the requested number of elements.
*  @param[in]  size : Size of transfer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALD_ARG
*  - ITKSTATUS_IVNALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Reading elements from video memory buffers may be very slow.
*  @see    ItkBufferWriteRect
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferReadRect(ITKBUFFER hBuffer, uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height, void* data, uint32_t size);

/**
  *  @brief  Write a series of elements to a buffer resource.
  *  @param[in]  hBuffer : Buffer resource handle
  *  @param[in]  offset : Offset to seek within the buffer prior to read (in pixels)
  *  @param[in]  size : Size of transfer.
  *  @param[in] data : Array which can accommodate the requested size (number of elements �� ITKBUFFER_PRM_DATASIZE).
  *  @Return:
  *  - ITKSTATUS_OK
  *  - ITKSTATUS_INVALD_ARG
  *
  *  @note   Writing elements from video memory buffers may be very slow.
  *  @see    ItkBufferRead
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferWrite(ITKBUFFER hBuffer, uint32_t offset, const void* data, uint32_t size);

/**
*  @brief  Write an element to a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  posX : Horizontal position of the element in the buffer.
*  @param[in]  posY : Vertical position of the element in the buffer.
*  @param[in]  element : Value of the specified position.
*  @param[in]  size : Size of transfer.

*  @Return :
*  -ITKSTATUS_OK
*  -ITKSTATUS_INVALD_ARG
*  -ITKSTATUS_IVNALID_HANDLE
*  -ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Writing elements from video memory buffers may be very slow.
*  @see    ItkBufferReadElement
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferWriteElement(ITKBUFFER hBuffer, uint32_t posX, uint32_t posY, const void* element, uint32_t size);

/**
*  @brief  Write a set of linearly positioned elements to a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  startX : Horizontal position of first element to read.
*  @param[in]  startY : Vertical position of first element to read.
*  @param[in]  endX : Horizontal position of last element to read.
*  @param[in]  endY : Vertical position of last element to read.
*  @param[in]  array : Array which can accommodate the requested number of elements.
*  @param[in]  uElements : Number of elements written.
*  @param[in]  size : Size of transfer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALD_ARG
*  - ITKSTATUS_IVNALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   writing elements from video memory buffers may be very slow.
*  @see    ItkBufferReadLine
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferWriteLine(ITKBUFFER hBuffer, uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY, uint32_t* uElements, const void* data, uint32_t size);

/**
*  @brief  Write a set of elements forming a rectangular area to a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[in]  offsetX : Horizontal position of first element to read.
*  @param[in]  offsetY : Vertical position of first element to read.
*  @param[in]  width : Horizontal length of the rectangle.
*  @param[in]  height : Vertical length of the rectangle.
*  @param[in]  data : Array which can accommodate the requested number of elements.
*  @param[in]  size : Size of transfer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALD_ARG
*  - ITKSTATUS_IVNALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Writing elements from video memory buffers may be very slow.
*  @see    ItkBufferReadRect
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferWriteRect(ITKBUFFER hBuffer, uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height, const void* data, uint32_t size);

/**
*  @brief  Converts a Bayer-encoded image to an RGB image.
*  @param[in]  hSrc : Input buffer handle. The input buffer format must be one of the following: ITKBUFFER_VAL_FORMAT_UINT8.
*  @param[in]  hDst : Output buffer handle. The output buffer format can be one of the following: ITKBUFFER_VAL_FORMAT_RGB888 or ITKBUFFER_VAL_FORMAT_BGR888.
*  @param[in]  options : This value must contain one of the alignment option : ITKBUFFER_VAL_BAYER_BGGR, ITKBUFFER_VAL_BAYER_RGGB, ITKBUFFER_VAL_BAYER_GBRG, ITKBUFFER_VAL_BAYER_GRBG
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Converts a Bayer-encoded image to an RGB image.
*  @see    ItkBufferNew
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferBayerConvert(ITKBUFFER hSrc, ITKBUFFER hDst, uint32_t options);

/**
*  @brief  Clears contents of a buffer resource by writing a color value to all buffer elements.
*  @param[in]  hBuffer : Buffer resource handle.
*  @param[in]  pValue : Color value to set.
*  @param[in]  size : data bit of single buffer element.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_ARG
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Writes a color value to all buffer elements.
*  @see    ItkBufferClearBlack
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferClear(ITKBUFFER hBuffer, const void* pValue, uint32_t size);

/**
*  @brief  Clears buffer resource contents to the corresponding black color.
*  @param[in]  hBuffer : Buffer resource handle.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Calls this function with a value of 0, guarantees that the buffer will appear black.
*  @see    ItkBufferClear
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferClearBlack(ITKBUFFER hBuffer);

/**
*  @brief  Copies the source buffer to location (dstOffsetX, dstOffsetY) of the destination buffer.
*  @param[in]  hSrc : Input buffer handle.
*  @param[in]  dstOffsetX : Horizontal offset in destination buffer.
*  @param[in]  dstOffsetY : Vertical offset in destination buffer.
*  @param[in]  hDst : Output buffer handle. 

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Pays attention to the image depth, size, format of the two buffers.
*  @see    ItkBufferCopyRect
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferCopy(ITKBUFFER hSrc, uint32_t dstOffsetX, uint32_t dstOffsetY, ITKBUFFER hDst);

/**
*  @brief  Copies a rectangular area of the source buffer, defined by (srcOffsetX, srcOffsetY, width, height), to the location (dstOffsetX, dstOffsetY) in the destination buffer.
*  @param[in]  hSrc : Input buffer handle.
*  @param[in]  srcOffsetX : Horizontal offset in source buffer.
*  @param[in]  srcOffsetY : Vertical offset in source buffer.
*  @param[in]  width : Horizontal length of the rectangle.
*  @param[in]  height : Vertical length of the rectangle.
*  @param[in]  hDst : Output buffer handle.
*  @param[in]  dstOffsetX : Horizontal offset in destination buffer.
*  @param[in]  dstOffsetY : Vertical offset in destination buffer.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_ARG_OUT_OF_RANGE
*  @note   Pays attention to the image depth, size, format of the two buffers.
*  @see    ItkBufferCopy
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferCopyRect(ITKBUFFER hSrc, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t width, uint32_t height, ITKBUFFER hDst, uint32_t dstOffsetX, uint32_t dstOffsetY);

/**
*  @brief  Saves the content of a buffer resource to a file.
*  @param[in]  hBuffer : Buffer resource handle.
*  @param[in]  filename : The name of file saved buffer data.
*  @param[in]  options : This value must contain one of the alignment option : ITKBUFFER_VAL_BMP, ITKBUFFER_VAL_TIFF, ITKBUFFER_VAL_RAW.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_INVALID_ARG
*  @note   Saves data from a buffer to a file.
*  @see    ItkBufferLoad
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferSave(ITKBUFFER hBuffer, const char* filename, uint32_t options);

/**
*  @brief  Load an image from a file into a buffer resource.
*  @param[in]  hBuffer : Buffer resource handle.
*  @param[in]  filename : The name of file saved buffer data.
*  @param[in]  options : This value must contain one of the alignment option : ITKBUFFER_VAL_BMP, ITKBUFFER_VAL_TIFF, ITKBUFFER_VAL_RAW.

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_INVALID_ARG
*  @note   Load an image into a buffer.
*  @see    ItkBufferSave
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferLoad(ITKBUFFER hBuffer, const char* filename, uint32_t options);

/**
*  @brief  Denoise a image by GIMP algothrim
*  @param[in]  hSrc : Source buffer to denoise
*  @param[out] hDst : Destination buffer, dst could be the same as src.
*  @param[in]  threshold : a valid threshold from 0 to ;

*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_INVALID_ARG
*  @note   Denoise a buffer
*  @see    ItkBufferDenoise
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkBufferDenoise(ITKBUFFER hSrc, ITKBUFFER hDst, int threshold);

/**
*  @brief  Create a view handle.
*  @param[in]  hBuffer : Buffer resource handle
*  @param[int] hParentWnd : show buffer parent hwnd.
*  @param[out] hView : View resource handle
@  Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*  - ITKSTATUS_INVALD_ARG
*
*  @note   Create a view handle to display image.
*  @see    ItkViewFree
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewNew(ITKBUFFER hBuffer, const void *hParentWnd, ITKVIEW* hView);

/**
*  @brief  Release handle to a view resource.
*  @param[in] hView : View resource handle
@  Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   The hView handle is invalid after a call to this function.
Only after the view has been destroyed when using this function can the buffer be destroyed.
*  @see    ItkViewFree
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewFree(ITKVIEW hView);

/**
*  @brief Append buffer to the tail of view destination.
*  @param[in] hView : View resource handle
*  @param[in] hBuffer : Buffer resource handle
@  Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   New buffer resource must have the same size and format as the buffer resource
that has been specified when creating the view resource.
*  @see    ItkViewRemoveBuffer
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewAddBuffer(ITKVIEW hView, ITKBUFFER hBuffer);

/**
*  @brief Remove buffer from the tail of view destination.
*  @param[in] hView : View resource handle
*  @param[in] hBuffer : Buffer resource handle
@  Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   None.
*  @see    ItkViewRemoveBuffer
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewRemoveBuffer(ITKVIEW hView, ITKBUFFER hBuffer);

/**
*  @brief Remove All buffer from the tail of view destination.
*  @param[in] hView : View resource handle
@  Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   None.
*  @see    ItkViewRemoveAllBuffer
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewRemoveAllBuffer(ITKVIEW hView);

/**
*  @brief  Set a simple view parameter of a view resource.
*  @param[in]  hView : View resource handle
*  @param[in]  prm : View parameter to set
*  @param[out] None.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Set the view parameter value to a view resource.
*  @see    ItkViewGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewSetPrm(ITKVIEW hView, uint32_t prm, const void* value);

/**
*  @brief  Get a simple view parameter of a view resource.
*  @param[in]  hView : View resource handle
*  @param[in]  prm : View parameter to set
*  @param[out] None.
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Get the view parameter value from a view resource.
*  @see    ItkViewGetPrm
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewGetPrm(ITKVIEW hView, uint32_t prm, void* value);

/**
*  @brief  Stops displaying a view resource.
*  @param[in]  hView : View resource handle
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Stops displaying a view resource.
*  @see    ItkViewShow
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewHide(ITKVIEW hView);

/**
*  @brief  Displays a view resource.
*  @param[in]  hView : View resource handle
*  @param[in]  hBuffer : Buffer resource handle
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Displays a view resource with specified buffer handle.
*  @see    ItkViewHide
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewShow(ITKVIEW hView);

/**
*  @brief  Displays a view resource.
*  @param[in]  hView : View resource handle
*  @Return:
*  - ITKSTATUS_OK
*  - ITKSTATUS_INVALID_HANDLE
*
*  @note   Displays a view resource with next buffer handle.
*  @see    ItkViewHide
*/
IKAPC_API ITKSTATUS IKAPC_CC
ItkViewShowNext(ITKVIEW hView);

/**
* @}
*/
#ifdef __cplusplus
}
	#ifdef IKAPC_BOOL_DEFINED
		#undef _Bool
		#undef IKAPC_BOOL_DEFINED
	#endif
#endif /* __cplusplus */

#endif /* _IKAPC_H */