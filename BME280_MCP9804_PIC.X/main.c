/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC16F1619
        Driver Version    :  2.00
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <stdio.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "./I2C_user.h"
#include "./BME280_User.h"
#include "./MCP9804.h"

//#define FORCED_MODE
#define MAINLOOP_DELAY_MS    2000   // mSec

void I2C_UserInit(void);


void user_delay_ms(uint32_t period);


#define LED_D4_ON()     {D4_LAT=1;}
#define LED_D4_OFF()    {D4_LAT=0;}


/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
//    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
//    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    
    printf("Program Start...\r\n");
    LED_D4_ON();
    
    I2C_UserInit();
    
    Bme280_UserInit();
 
    MCP9804_SetTupper();
    MCP9804_SetTlower();
    MCP9804_SetTcrit();
    MCP9804_ConfigRead();
        
    LED_D4_OFF();

    while (1)
    {
        user_delay_ms(MAINLOOP_DELAY_MS);

        BME280_Data();
        MCP9804_Temperature();
        
        D4_Toggle();
    }
}

void user_delay_ms(uint32_t period)
{
//    D7_LAT=1; // for check
    for(uint32_t i=0;i<period;i++){
        TMR1_Reload(); // 1msec value reload and start timer
        PIR1bits.TMR1IF = 0;
        TMR1_StartTimer();
        while(!TMR1_HasOverflowOccured());
        TMR1_StopTimer();
    }
//    D7_LAT=0; // for check    
}


void debug_error(void)
{
    while(1){
        LED_D4_ON();
        __delay_ms(100);
        LED_D4_OFF();
        __delay_ms(100);
    }
}

/**
 End of File
*/