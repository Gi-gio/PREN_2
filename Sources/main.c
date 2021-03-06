/* ###################################################################
**     Filename    : main.c
**     Project     : PI_Com_Shell
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-11-17, 18:19, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module. ADDED FOR TESTING
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "UTIL1.h"
#include "KSDK1.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "LED_GREEN.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED_BLUE.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "LED_RED.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "FRTOS1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "I2C1.h"
#include "PWM_Left.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "IN1.h"
#include "BitIoLdd4.h"
#include "IN2.h"
#include "BitIoLdd5.h"
#include "PWM_Right.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "IN3.h"
#include "BitIoLdd6.h"
#include "IN4.h"
#include "BitIoLdd7.h"
#include "MCUC1.h"
#include "XF1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Accel.h"
#include "LEDRTask.h"
#include "Shell.h"
#include "Infrarot.h"
#include "Motor.h"





/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */


	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */


  createTaskLED();
  createTaskInfrarot();
  createTaskAccel();
  createTaskMotor();
  createTaskSHELL();
  FRTOS1_vTaskStartScheduler();

  for(;;){}



  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
