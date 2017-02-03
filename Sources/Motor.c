/*
 * Motor.c
 *
 *  Created on: 22.12.2016
 *      Author: Fabian
 */

#include "Motor.h"


void startPWM(void){
	PWM_Left_Enable();
	PWM_Left_Enable();

	//Stop
	setPWMLeft(0);
	setPWMRight(0);
}

void setPWMLeft(int16_t speed){

	if(speed == 0)
	{
		//stop
		IN1_SetDir(true); //output
		IN1_ClrVal();
		IN2_SetDir(true); //output
		IN2_ClrVal();
		PWM_Left_SetRatio8(255); // ~0v
	}
	if(speed > 0)
	{
		//Forward
		IN1_SetDir(false); //input
		IN2_SetDir(true); //output
		IN2_SetVal();

		PWM_Left_SetRatio8((uint8_t)speed);
	}
	if(speed < 0)
	{
		//Backward
		IN1_SetDir(true); //output
		IN1_SetVal();
		IN2_SetDir(false); //input

		PWM_Left_SetRatio8((uint8_t)((-1) * speed));
	}
}

void setPWMRight(int16_t speed){

	if(speed == 0)
	{
		//stop
		IN3_SetDir(true); //output
		IN3_ClrVal();
		IN4_SetDir(true); //output
		IN4_ClrVal();
		PWM_Right_SetRatio8(255); // ~0v
	}
	if(speed > 0)
	{
		//Forward
		IN3_SetDir(false); //input
		IN4_SetDir(true); //output
		IN4_SetVal();

		PWM_Right_SetRatio8((uint8_t)speed);
	}
	if(speed < 0)
	{
		//Backward
		IN3_SetDir(true); //output
		IN3_SetVal();
		IN4_SetDir(false); //input

		PWM_Right_SetRatio8((uint8_t)((-1) * speed));
	}
}

static portTASK_FUNCTION(MotorTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  startPWM();
  for(;;) {
    //LED_RED_Neg();
    FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
  }
  //Error
  IN1_SetDir(false); //input
  IN2_SetDir(false); //input
  IN3_SetDir(false); //input
  IN4_SetDir(false); //input
  PWM_Left_Disable();
  PWM_Right_Disable();
  }


void createTaskMotor(void){
if(FRTOS1_xTaskCreate(MotorTask,"MotorTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL ) != pdPASS)
{
   for(;;){}; /* Out of heap memory? */
}
}
