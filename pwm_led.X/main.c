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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#define VDD (50000)                                    // Supply Voltage of 5 V is represented as 33000*10^-4 V
                                                       // to get the required ADC_RESOLUTION
#define ADC_STEPS (1024)                               // 10 bit ADC has 1024 Levels
#define ADC_RESOLUTION (VDD/ADC_STEPS) 
uint16_t adones, adtenth, adhundredth;
uint16_t adcVoltValue;

void ConvertADCVoltage ( unsigned int adc_conv_data )
{
    adcVoltValue = (ADC_RESOLUTION*adc_conv_data);  //3.225 milli volts one step per division

    adones = adcVoltValue/10000;        // units place

    adtenth = adcVoltValue/1000;
    adtenth = adtenth%10;           // one tenth decimal place

    adhundredth = adcVoltValue/100;
    adhundredth = adhundredth%10;         // one hundredth decimal place
}

 uint16_t convertedValue;
void main(void)
{
    // Initialize the device
   
    SYSTEM_Initialize();
 PWM2_LoadDutyValue(0);
 ADC_SelectChannel(channel_AN0);
  ADC_StartConversion();
    
   
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
       while(!ADC_IsConversionDone());
       convertedValue = ADC_GetConversion(channel_AN0);
		ConvertADCVoltage(convertedValue);
        PWM2_LoadDutyValue(adones*100);
        // Add your application code
    }
}
/**
 End of File
*/