/*
 * FRTOS.c

 *
 *  Created on: 23.11.2016
 *      Author: Fabian
 */

#include "LEDRTask.h"


static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED_BLUE_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}


void createTaskLED(void){
if(FRTOS1_xTaskCreate(Task1,"Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL ) != pdPASS)
{
   for(;;){}; /* Out of heap memory? */
}
}
