/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */
uint8_t report[20];
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
  0x06, 0x00, 0xff,		// Usage Page (Vendor-defined)
	0x09, 0x00,					// Usage (Undefined)
	0xa1, 0x01,					// Collection (Application)
		0x09, 0x00,					// Usage (Undefined)
		0x15, 0x00,					// Logical Minimun (0)
		0x26, 0xff, 0x00,		// Logical Maximun (255)
		0x75, 0x08,					// Report Size (8)
		0x95, 0x01,					// Report Count(1)
		0x81, 0x06,					// Input (Data,Var,Abs)
	
		0x09, 0x00,					// Usage (Undefined)
		0x15, 0x00,					// Logical Minimun (0)
		0x26, 0xff, 0x00,		// Logical Maximun (255)
		0x75, 0x08,					// Report Size (8)
		0x95, 0x10,					// Report Count (10)
		0x91, 0x06,					// Output (Data,Var,Abs)
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

// Mouse
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[USBD_MOUSE_HID_REPORT_DESC_SIZE]  __ALIGN_END =
{
	//Mouse
	0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)     
	0x09, 0x02,                         // USAGE (Mouse)                    
	0xa1, 0x01,                         // COLLECTION (Application)
		0x09, 0x01,                         //   USAGE (Pointer)                
		0xa1, 0x00,                         //   COLLECTION (Physical)          
		0x05, 0x09,                         //     USAGE_PAGE (Button)          
		0x19, 0x01,                         //     USAGE_MINIMUM (Button 1)     
		0x29, 0x03,                         //     USAGE_MAXIMUM (Button 2)     
		0x25, 0x01,                         //     LOGICAL_MAXIMUM (1)          
		0x75, 0x01,                         //     REPORT_SIZE (1)              
		0x95, 0x03,                         //     REPORT_COUNT (2)             
		0x81, 0x02,                         //     INPUT (Data,Var,Abs)         
		0x95, 0x05,                         //     REPORT_COUNT (6)             
		0x81, 0x03,                         //     INPUT (Cnst,Var,Abs)         
		0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop) 
		0x09, 0x30,                         //     USAGE (X)                    
		0x09, 0x31,                         //     USAGE (Y)                    
		0x75, 0x08,                         //     REPORT_SIZE (8)             
		0x95, 0x02,                         //     REPORT_COUNT (2)    
		0x15, 0x80,  												//		LOGICAL_MINIMUM (10)
		0x25, 0x7f,                         //    LOGICAL_MAXIMUM (10)      
		0x81, 0x06,                         //     INPUT (Data,Var,Rel)         
		0xc0,                               //   END_COLLECTION  
	0xc0,                               //END_COLLECTION
}; 


// KeyBoard
__ALIGN_BEGIN static uint8_t HID_KEYBOARD_ReportDesc[USBD_KEYBOARD_HID_REPORT_DESC_SIZE]  __ALIGN_END =
{
	//Keyboard
	0x05, 0x01,			// Usage Page (Generic Desktop Ctrls)
	0x09, 0x06,			// Usage (Keyboard)
	0xA1, 0x01,			// Collection (Application)
	0x85, USBD_KEYBOARD_REPORT_ID,// Report ID (2)
	
	0x09, 0x06,			// Usage (Keyboard)
	0xa1, 0x00,			//  COLLECTION (Physical)  
	0x05, 0x07,			//  Usage Page (Kbrd/Keypad)
	0x19, 0xE0,			//  Usage Minimum (0xE0)
	0x29, 0xE7,			//  Usage Maximum (0xE7)
	0x15, 0x00,			//  Logical Minimum (0)
	0x25, 0x01,			//  Logical Maximum (1)
	0x75, 0x01,			//  Report Size (1)
	0x95, 0x08,			//  Report Count (8)
	0x81, 0x02,			//  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
//	0x95, 0x01,			//  Report Count (1)
//	0x75, 0x08,			//  Report Size (8)
//	0x81, 0x01,			//  Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x08,			//  Report Size (8)
	0x95, 0x06,			//  Report Count (6)
	0x15, 0x00,			//  Logical Minimum (0)
	0x25, 0xff,//0x65, //  Logical Maximum (101)
	0x05, 0x07,			//  Usage Page (Kbrd/Keypad)
	0x19, 0x00,			//  Usage Minimum (0x00)
	0x29, 0x65,			//  Usage Maximum (0x65)
	0x81, 0x00,			//  Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

//	0x05, 0x08,			//  Usage Page (LEDs)
//	0x19, 0x01,			//  Usage Minimum (Num Lock)
//	0x29, 0x05,			//  Usage Maximum (Kana)
//	0x15, 0x00,			//  Logical Minimum (0)
//	0x25, 0x01,			//  Logical Maximum (1)
//	0x75, 0x01,			//  Report Size (1)
//	0x95, 0x05,			//  Report Count (5)
//	0x91, 0x02,			//  Output (Data,Var,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
//	0x95, 0x01,			//  Report Count (1)
//	0x75, 0x03,			//  Report Size (3)
//	0x91, 0x01,			//  Output (Cnst,Ary,Abs,NWrp,Lin,Pref,NNul,NVol,Bit) 
	0xC0,
	0xC0,

	//System Control
	0x05, 0x01,			// Usage Page (Generic Desktop)
	0x09, 0x80,			// Usage (System Control)
	0xA1, 0x01,			// Collection (Application)
	0x85, USBD_System_Control_REPORT_ID, // Report ID (3)
	0x09, 0x80,			//  Usage (System Control)
	0xA1, 0x00,			//  Collection (Physical)
	0x19, 0x81,			//  Usage Minimum (System Power Down)
	0x29, 0x83,			//  Usage Maximum (System Wake Up)
	0x75, 0x01,			//  Report Size (1)
	0x95, 0x03,			//  Report Count (3)
	0x81, 0x06,			//  Input (Data,Var,Rel,NWrp,Lin,Pref,NNul,Bit)
	0x95, 0x05,			//  Report Count (5)
	0x81, 0x01,			// Input (Cnst,Ary,Abs)
	0xC0, 
	0xC0
};





/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* pbuf);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS, HID_MOUSE_ReportDesc, HID_KEYBOARD_ReportDesc,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t *pbuf)
{
  /* USER CODE BEGIN 6 */	
	if (((uint32_t *) report)[0] != ((uint32_t *) pbuf)[0]){
		((uint32_t *) report)[0] = ((uint32_t *) pbuf)[0];
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, 0x82, pbuf, 3);
	}
	
	if ((((uint32_t *) report)[1] != ((uint32_t *) pbuf)[1]) || \
		(((uint32_t *) report)[2] != ((uint32_t *) pbuf)[2])){
			((uint32_t *) report)[1] = ((uint32_t *) pbuf)[1];
			((uint32_t *) report)[2] = ((uint32_t *) pbuf)[2];
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, 0x83, pbuf + 4, 8);
	}
		
	if (((uint32_t *) report)[3] != ((uint32_t *) pbuf)[3]){
		((uint32_t *) report)[3] = ((uint32_t *) pbuf)[3];
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, 0x83, pbuf + 12, 2);
	}
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

