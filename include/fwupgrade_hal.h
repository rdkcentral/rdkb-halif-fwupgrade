/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
/**
* 
* @file fwupgrade_hal.h
* @brief fwupgrade_hal provides an interface to get/set firmware download, reboot control features.
*
*/

#ifndef __FWUPGRADE_HAL_H__
#define __FWUPGRADE_HAL_H__

/**
 * @defgroup FWUPGRADE_HAL FWUPGRADE HAL
 *
 * @defgroup FWUPGRADE_HAL_TYPES   FWUPGRADE HAL Data Types
 * @ingroup  FWUPGRADE_HAL
 * 
 * @defgroup FWUPGRADE_HAL_APIS   FWUPGRADE HAL APIs
 * @ingroup  FWUPGRADE_HAL
 *
 **/


/**
* @addtogroup FWUPGRADE_HAL_TYPES
* @{
*/
#include <sys/time.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  unsigned char
#endif

#ifndef USHORT
#define USHORT  unsigned short
#endif

#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef LONG
#define LONG	long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

/** 
* @} 
/*
 * @addtogroup FWUPGRADE_HAL_APIS
 * @{
 */

/**********************************************************************************
 *
 *  Subsystem level function prototypes
 *
**********************************************************************************/
/**
* @brief Set FW Download URL and Filename.
*
* @param[in] pUrl A pointer to a character array that will hold the firmware download URL.
*                 \n URL buffer size should be at least 1024 bytes.
*                 \n Example pUrl: http://dac15cdlserver.ae.ccp.xcal.tv:8080/Images

* @param[in] pfilename - A pointer to a character array that will hold the firmware filename.
*                      \n Filename buffer size should be at least 256 bytes.
*                      \n pfilename format: <MODEL_NUM>_<BRANCH_NAME>_PROD_sey.bin
*                      \n pfilename example: TG4482PC2_6.2p10s1_PROD_sey.bin
*                      \n Possible MODEL_NUM:
*                      \n CGM4140COM, TG3482G, CGM4981COM, CGM4331COM, CGA4332COM, SR300, SE501, WNXL11BWL, SR203, SR213, TG4482A
*
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if pUrl / pfilename string is NULL (or)
*         failed to open HTTP download config file '/tmp/httpDwnld.conf'.
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*/
INT fwupgrade_hal_set_download_url (char* pUrl, char* pfilename);


/**
* @brief Get FW Download URL and Filename.
* @param[out] pUrl A pointer to a character array that will hold the firmware download URL.
*                  \n The buffer size should be at least 1024 bytes.
*                  \n Example pUrl: http://dac15cdlserver.ae.ccp.xcal.tv:8080/Images
* @param[out] pfilename - A pointer to a character array that will hold the firmware filename.
*                       \n The buffer size should be at least 256 bytes.
*                       \n pfilename format: <MODEL_NUM>_<BRANCH_NAME>_PROD_sey.bin
*                       \n pfilename example: TG4482PC2_6.2p10s1_PROD_sey.bin
*                       \n Possible MODEL_NUM:
*                       \n CGM4140COM, TG3482G, CGM4981COM, CGM4331COM, CGA4332COM, SR300, SE501, WNXL11BWL, SR203, SR213, TG4482A
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if pUrl / pfilename string is NULL (or)
*         failed to open HTTP download config file '/tmp/httpDwnld.conf'.
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*/
INT fwupgrade_hal_get_download_url (char *pUrl, char* pfilename);


/**
* @brief Set the FW Download Interface.
* @param[in] interface The interface to be set.
*                      \n Use interface = 0 for wan0 and interface = 1 for erouter0.
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if interface > 1 (or)
*         failed to open HTTP download interface config file '/tmp/httpDwnldIf.conf'.
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT fwupgrade_hal_set_download_interface (unsigned int interface);


/**
* @brief Get the FW Download Interface.
* @param[out] pinterface A pointer to an unsigned integer that stores retrieved interface value.
*                        \n Interface value is represented as follows: 0 for wan0 and 1 for erouter0.
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if pinterface is NULL (or)
*         failed to open HTTP download interface config file '/tmp/httpDwnldIf.conf'.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT fwupgrade_hal_get_download_interface (unsigned int* pinterface);


/**
* @description Start FW Download.
* 
* @return the status of the operation.
* @retval RETURN_OK if Image flash is successful.
* @retval RETURN_ERR if failed to get HTTP download URL or filename (or)
*         \n failed download the image to CPE (or)
*         \n failed to execute OEM specific firmware flasher (or)
*         \n failed to set bootstate to new image.
* @retval 400 - Invalid URL (or) Failed on gethostbyname() call.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*/
INT fwupgrade_hal_download ();


/**
* @brief Get the FW Download Status.
*
* @return the status of the FW Download.
* @retval 0 - Download is not started.
* @retval 0-100 - Values of percent of download.
* @retval 200 - Download is completed and waiting for reboot.
* @retval 400 - Invalid Http server Url.
* @retval 401 - Cannot connect to Http server.
* @retval 402 - File is not found on Http server.
* @retval 403 - HW_Type_DL_Protection Failure.
* @retval 404 - HW Mask DL Protection Failure.
* @retval 405 - DL Rev Protection Failure.
* @retval 406 - DL Header Protection Failure.
* @retval 407 - DL CVC Failure.
* @retval 500 - General Download Failure.
*
*/
INT fwupgrade_hal_get_download_status ();


/**
* @brief Get the Reboot Ready Status.
* @param[out] pValue    Pointer to an unsigned long variable that will store the reboot ready status.
*                    \n Value 1 represents ready for reboot and 2 represents not ready for reboot.
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if pValue is NULL.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*/
INT fwupgrade_hal_reboot_ready (ULONG *pValue);


/**
* @brief FW Download Reboot Now.
* 
* @return the status of the reboot operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any reboot is in process.
*/
INT fwupgrade_hal_download_reboot_now ();


/**
* @brief Firmware update and factory reset the device.
* 
* @return the status of the Firmware update and factory reset operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if failed download the image to CPE (or)
*         \n if any reboot is in process.
*/
INT fwupgrade_hal_update_and_factoryreset ();


/**
* @brief Downloads and upgrades the firmware.
* @param[in] url URL from which to download the firmware.
*                \n The URL buffer size should be at least 1024 bytes.
*                \n Example pUrl: http://dac15cdlserver.ae.ccp.xcal.tv:8080/Images
* @return the status of the Firmware download and upgrade status.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR in case of remote server not reachable.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*/
INT fwupgrade_hal_download_install(const char *url);

#ifdef __cplusplus
}
#endif
#endif
/** 
 * @
 */ 

