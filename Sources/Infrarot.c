/*
 * Infrarot.c
 *
 *  Created on: 24.11.2016
 *      Author: Fabian
 */


#include "Infrarot.h"
#include <math.h>

volatile bool AD_finished;
uint16_t value[AD1_CHANNEL_COUNT];
uint16_t cmValueLF,cmValueLB;
//float voltage;




static portTASK_FUNCTION(TaskInf, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
	AD_finished = FALSE;
	AD1_Measure(FALSE);
	while(!AD_finished){
		FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
	}
    AD1_GetValue16(&value[0]);
    //voltage=(((float)value/65535)*3.3);
    cmValueLF = 180000*pow(value[0],-0.952)-3;
    cmValueLB = 180000*pow(value[1],-0.952)-3;
    if(cmValueLF>27){
    	cmValueLF--;

    }
    if(cmValueLF<10){
    	cmValueLF++;
    }
    if(cmValueLF<4){
    	cmValueLF = 4;
    }
    if(cmValueLF<4){
       	cmValueLF = 4;
    }

    if(cmValueLB>27){
       	cmValueLB--;
     }
     if(cmValueLB<10){
        cmValueLB++;
     }

     if(cmValueLB<4){
        cmValueLB = 4;
     }
    FRTOS1_vTaskDelay(30/portTICK_RATE_MS);
  }
}

uint16_t getcmLF(void){
	return cmValueLF;
}

uint16_t getcmLB(void){
	return cmValueLB;
}



void createTaskInfrarot(void){
if(FRTOS1_xTaskCreate(TaskInf,"TaskInf", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL ) != pdPASS)
{
   for(;;){}; /* Out of heap memory? */
}
}

