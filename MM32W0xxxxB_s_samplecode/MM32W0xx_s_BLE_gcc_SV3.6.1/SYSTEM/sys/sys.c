#include "sys.h"
#include "mg_api.h"

/*static */unsigned int SysTick_Count = 0;

/********************************************************************************************************
 **function: GetSysTickCount
 **@brief    This function gets the SysTick_Count value
 **
 **@param    None
 **
 **@return   SysTick_Count.
 ********************************************************************************************************/
unsigned int GetSysTickCount(void) //porting api
{
	return SysTick_Count;
}

/********************************************************************************************************
 **function: SysTick_Handler
 **@brief    This function handles SysTick Handler.
 **
 **@param    None
 **
 **@return   None.
 ********************************************************************************************************/
void SysTick_Handler(void) {
	SysTick_Count++;
	ble_nMsRoutine();
}

/********************************************************************************************************
 **function: SysTick_Configuration
 **@brief    This function sets the system clock
 **
 **@param    None
 **
 **@return   None.
 ********************************************************************************************************/
void SysTick_Configuration(void) {
	SysTick_Config(48000);
}

