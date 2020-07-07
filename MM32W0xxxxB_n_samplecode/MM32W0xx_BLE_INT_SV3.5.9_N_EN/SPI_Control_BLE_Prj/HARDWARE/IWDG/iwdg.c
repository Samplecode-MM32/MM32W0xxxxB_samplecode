#include "HAL_rcc.h"
#include "HAL_iwdg.h"
#include "iwdg.h"

/********************************************************************************************************
**function: PVU_CheckStatus
**@brief    Check the status bits
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void PVU_CheckStatus(void)
{
  while (1)
  {
    if (IWDG_GetFlagStatus(IWDG_FLAG_PVU) == RESET)
    {
      break;
    }
  }
}

/********************************************************************************************************
**function: RVU_CheckStatus
**@brief    Check the status bits
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void RVU_CheckStatus(void)
{
  while (1)
  {
    if (IWDG_GetFlagStatus(IWDG_FLAG_RVU) == RESET)
    {
      break;
    }
  }
}

/********************************************************************************************************
**function: Write_Iwdg_ON
**@brief    Turn on watchdog
**                   
**@param    IWDG_Prescaler 
**
**@param    Reload  
**
**@return   None.
********************************************************************************************************/
void Write_Iwdg_ON(unsigned short int IWDG_Prescaler, unsigned short int Reload)
{
  RCC_LSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

  IWDG_WriteAccessCmd(0x5555);
  IWDG_SetPrescaler(IWDG_Prescaler);
  PVU_CheckStatus();

  IWDG_WriteAccessCmd(0x5555);
  IWDG_SetReload(Reload & 0xfff);
  RVU_CheckStatus();

  IWDG_ReloadCounter();
  IWDG_Enable();
}

/********************************************************************************************************
**function: Write_Iwdg_RL
**@brief    Feeding dog function
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void Write_Iwdg_RL(void)
{
  IWDG_ReloadCounter();
}

