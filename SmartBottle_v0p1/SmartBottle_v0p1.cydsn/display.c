/******************************************************************************
* File Name: display.c
*
* Version: 1.00
*
* Description: This file contains the functions that initialize the E-INK display
*              and show the instructions to use this code example at startup
*
* Related Document: CE218135_BLE_Proximity.pdf
*
* Hardware Dependency: CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit
*
******************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation.
******************************************************************************
* This software, including source code, documentation and related materials
* ("Software") is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress source code and derivative works for the sole purpose of creating 
* custom software in support of licensee product, such licensee product to be
* used only in conjunction with Cypress's integrated circuit as specified in the
* applicable agreement. Any reproduction, modification, translation, compilation,
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use
* of Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use as critical components in any products 
* where a malfunction or failure may reasonably be expected to result in 
* significant injury or death ("ACTIVE Risk Product"). By including Cypress's 
* product in a ACTIVE Risk Product, the manufacturer of such system or application
* assumes all risk of such use and in doing so indemnifies Cypress against all
* liability. Use of this Software may be limited by and subject to the applicable
* Cypress software license agreement.
*****************************************************************************/
/*******************************************************************************
* This file contains the functions that initialize the E-INK display and show the
* instructions to use this code example at startup
*
* For the details of the E-INK display and library functions, see the code example 
* CE218133 - PSoC 6 MCU E-INK Display with CapSense
*******************************************************************************/

/* Header file includes */
#include "cy_eink_library.h"
#include "screen_contents.h"

/* Definition of ambient temperature at 25 degree C */
#define AMBIENT_TEMPERATURE         (int8_t) (25)

/* Definition of the coordinates of a full image frame */
#define IMAGE_COORDINATES           {0, 33, 0, 176}

/* Origin of the text coordinates */
#define TEXT_ORIGIN                 {0x00u, 0x02u}

/* Flag that indicates if the E-INK display has been detected */
bool static displayDetected = false;

/* Frame buffer used for display operations */
cy_eink_frame_t frameBuffer[CY_EINK_FRAME_SIZE];

/*******************************************************************************
* Function Name: void InitDisplay(void)
********************************************************************************
* Summary:
*  Initializes the E-INK display hardware and clears the display
*
* Parameters:
*  None
*
* Return:
*  void
*
*******************************************************************************/
void InitDisplay(void)
{ 
    /* Initialize the E-INK display hardware with the given ambient temperature */
    Cy_EINK_Start(AMBIENT_TEMPERATURE);
    
    /* Power on the display and check if the operation is successful */
    if ( Cy_EINK_Power(CY_EINK_ON)== CY_EINK_OPERATION_SUCCESS)
    {
        /* Clear the display to white background */
        Cy_EINK_Clear(CY_EINK_WHITE_BACKGROUND, CY_EINK_POWER_MANUAL);
        Cy_EINK_Power(CY_EINK_OFF);
        
        /* Set the flag that indicates if the E-INK display has been detected */
        displayDetected = true;
    }
}

/*******************************************************************************
* Function Name: void DisplayInstructions(void)
********************************************************************************
* Summary:
*  Combines text and logo/heading images in an internal frame buffer and then
*  writes the frame buffer to the E-INK display to show the instructions to use
*  this code example
*
* Parameters:
*  None
*
* Return:
*  void
*
*******************************************************************************/
void DisplayInstructions(void)
{
    /* Coordinates of a full-image and text origin */
    const uint8_t   imageCoordinates[]  = IMAGE_COORDINATES;
    const uint8_t   textOrigin[]        = TEXT_ORIGIN;
    
    /* Do this only if the E-INK display has been detected */
    if (displayDetected)
    {
        /* Load the image that has the logo and the heading to the frame buffer */
        Cy_EINK_ImageToFrameBuffer(frameBuffer, (cy_eink_frame_t*)logoAndHeading,
                                (uint8_t*) imageCoordinates);
        /* Load the text that stores instructions to the frame buffer */
        Cy_EINK_TextToFrameBuffer(frameBuffer, (char*)instructions,
                           CY_EINK_FONT_8X12BLACK, (uint8_t*) textOrigin);
        
        /* Write the frame buffer to the E-INK display. Automatic power control is
           enabled so that the display gets powered on before the write process 
           and turned off afterwards */
        Cy_EINK_ShowFrame(CY_EINK_WHITE_FRAME, frameBuffer,
                   CY_EINK_FULL_2STAGE, CY_EINK_POWER_AUTO);
    }
}

/* [] END OF FILE */
