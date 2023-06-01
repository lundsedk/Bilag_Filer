    /* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "readADC.h"

CY_ISR_PROTO(UART_Handler);
void handleByteReceived(uint8_t byteReceived);
uint16_t signal = 0;

bool dataReqFlag = false;
bool motorReqFlag = false;
bool pump = false;





CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_PC_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_PC_ReadRxData();
        UART_PC_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

CY_ISR(ISR_ESP_Handler)
{
    char readChar = UART_ESP_GetChar();
    //UART_PC_PutChar(readChar);
//    switch(readChar)
//    {
//        case 'P':
//            motorReqFlag = true;
//            break;
//        case 'R':
//            dataReqFlag = true;
//            break;
//        default:
//            //UART_PC_PutChar(readChar);
//            break;
//    }
    
    
    
    
    if (readChar == 'R')
    {
        dataReqFlag = true;
    }
    
}



int main(void)
{
   
    CyGlobalIntEnable; /* Enable global interrupts. */
    char uartBuffer[8];
    char uartDebugBuffer[255];
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //isr_uart_rx_StartEx(UART_Handler);
    UART_PC_Start();
    UART_ESP_Start();
    isr_ESP_StartEx(ISR_ESP_Handler);
    isr_PC_StartEx(ISR_UART_rx_handler);
    ADC_DelSig_Start();
    
    UART_PC_PutString("Programmet er startet\r\n");

    for(;;)
    {
        uint16_t weight = readWater();
        //weight = 0.2599*weight-465.08;
        snprintf(uartDebugBuffer, sizeof(uartDebugBuffer), "%d\r\n",weight);
        UART_PC_PutString(uartDebugBuffer);
        CyDelay(100);

        if (dataReqFlag)
        {
            uint16_t light = readLight();
            uint16_t humid = readHumid();
            uint16_t weight = readWeight();
            uint16_t water = readWater();

            UART_PC_PutString(uartBuffer);
            snprintf(uartBuffer, sizeof(uartBuffer), "%c%c%c%c%c%c%c%c", 
                water>>8,water,
                humid>>8,humid,
                light>>8,light,
                weight>>8,weight);

            
            for (int i = 0; i<8 ;i++)
            {
                UART_ESP_PutChar(uartBuffer[i]);
                UART_PC_PutChar(uartBuffer[i]);
            }
            
            if (humid > 17900)//value to be determined
            {
                PWM_Start();
                PWM_WriteCompare(255);
                //CyDelay(10000);
                CyDelay(1000);
                PWM_Stop();
            }

            snprintf(uartDebugBuffer, sizeof(uartDebugBuffer), "%d %d %d %d\n",water, humid, light, weight);
            
            UART_PC_PutString(uartDebugBuffer);
            dataReqFlag = false;
            
        }
        
        
        
        
//        /* Place your application code here. */
//        signal = readLight();
//        snprintf(uartBuffer, sizeof(uartBuffer), "ADC weight: %d \r\n", signal);
//        UART_PC_PutString(uartBuffer);
//        CyDelay(100);
    }
}


