/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
 */

/*
? [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include "mcc_generated_files/system/system.h"


// 1. Toggle the LED

void turn_led_on()
{
    LED_SetLow();
}

void turn_led_off()
{
    LED_SetHigh();
}


// 2. Breathing the LED

register16_t tca0Cmp0DutyCycle95 = 0x2EE;
register16_t tca0Cmp0DutyCycle10 = 0x53;
register16_t difference5 = 0x2A;
bool tca0Cmp0GoUp = true;

void update_tca0_cmp0(void)
{
    if (TCA0.SINGLE.CMP0 >= tca0Cmp0DutyCycle95)
    {
        tca0Cmp0GoUp = false;
    }
    if (TCA0.SINGLE.CMP0 <= tca0Cmp0DutyCycle10)
    {
        tca0Cmp0GoUp = true;
    }
    if (tca0Cmp0GoUp)
    {
        TCA0.SINGLE.CMP0 += difference5;
    }
    else
    {
        TCA0.SINGLE.CMP0 -= difference5;
    }
}


// 3. Switch Breathing Speed

register16_t tca1Timeout80ms = 0x8234;
register16_t tca1Timeout20ms = 0x208C;

void switch_tca1_period(void)
{
    TCA1.SINGLE.PER = TCA1.SINGLE.PER == tca1Timeout80ms ? tca1Timeout20ms : tca1Timeout80ms;
}

/*
    Main application
 */

int main(void)
{
    SYSTEM_Initialize();

    TCA0_OverflowCallbackRegister((TCA0_cb_t) turn_led_on); // 1. Toggle the LED
    TCA0_Compare0CallbackRegister((TCA0_cb_t) turn_led_off); // 1. Toggle the LED
    TCA1_OverflowCallbackRegister((TCA1_cb_t) update_tca0_cmp0); // 2. Breathing the LED
    Switch_SetInterruptHandler(switch_tca1_period); // 3. Switch Breathing Speed

    while (1)
    {
    }
}