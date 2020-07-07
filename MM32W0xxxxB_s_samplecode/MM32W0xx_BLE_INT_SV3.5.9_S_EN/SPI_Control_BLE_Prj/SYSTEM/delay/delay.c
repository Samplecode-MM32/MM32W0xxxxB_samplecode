#include "delay.h"

/********************************************************************************************************
**function: delay_us
**@brief    Call this function for us delay
**          
**@param    nTime  :  Delay time  
**
**@return   None.
********************************************************************************************************/
void delay_us(__IO uint32_t nTime)
{
  u16 i = 0;
  while (nTime--)
  {
    i = 10;
    while (i--);
  }
}

/********************************************************************************************************
**function: delay_ms
**@brief    Call this function for ms delay
**          
**@param    nTime  :  Delay time  
**
**@return   None.
********************************************************************************************************/
void delay_ms(__IO uint32_t nTime)
{
  u16 i = 0;
  while (nTime--)
  {
    i = 750;
    while (i--);
  }
}









































