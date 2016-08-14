/*  Breath_LED - Timer_A,Up Mode, DCO SMCLK
******************************************************************************
实现利用改变PWM的占空比来改变LED亮度
ACLK = na, SMCLK = MCLK = TACLK = default DCO
Board: MSP430G2553 Launchpad/
 在IAR Embedded Workbench for MSP430 5.30下编译测试通过   
*******************************************************************************/
#include "msp430g2553.h"
/*******************************************************************************
// 延时函数( __delay_cycles() would be better)
void delay_1us(void)
  {
    unsigned int i;
    for(i=0;i<100;i++);
  }
*******************************************************************************/
void main(void)
{
  unsigned const PWMPeriod = 600;
  unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
  P1DIR |= 0x40;              // Set P1.6 As output
  P1SEL |= 0x40;              // P1.6 TA0.1
  CCR0 = PWMPeriod;           
  CCTL1 = OUTMOD_7;           // Reset/set
                              // 
  TACTL = TASSEL_2 + MC_1;    // SMCLK, up_down mode
  while(1)
  {
    for(i=0;i<PWMPeriod;i+=1)
    {
      TACCR1=i;
      __delay_cycles(10000);          //变亮步进速度控制  1000->2ms
    }
    
    for(i=PWMPeriod;i>0;i-=1)
    {
      CCR1=i;
      __delay_cycles(10000);          //占空比变化的延时，调整延迟时间可改变呼吸灯变暗的速度
    }
    __delay_cycles(20000);
  }
}
