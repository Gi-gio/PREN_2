/*
 * Shell.c
 *
 *  Created on: 23.11.2016
 *      Author: Fabian
 */

#include "Shell.h"


int LED_Val;
int app_value;


static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  //CLS1_ParseCommand, /* default shell parser */
  ParseCommand, //parser
  NULL /* Sentinel, must be last */
};


uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {

	uint8_t res = ERR_OK;
	int32_t tmp;
	const uint8_t *p;
	uint8_t buf[32];

	//Print Help
	if(UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "help")==0){
		CLS1_SendHelpStr((unsigned char*)"SetLED 0-4", (const unsigned char*)"Set LED Color [Off,On,Red,Green,Blue]\r\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"GetLED", (const unsigned char*)"Returns the value of LED\r\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"GetINFCM", (const unsigned char*)"Returns the distance of Infrared Sensors in Cm\r\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"GetACCEL", (const unsigned char*)"Returns the xyz-axis values of the Acceleration sensor\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"SetMotorLeft x", (const unsigned char*)"Set Speed -255 < x < 255 ", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"SetMotorRight x", (const unsigned char*)"Set Speed -255 < x < 255 ", io->stdOut);
		*handled = TRUE;

	//Commands LED
	}else if (UTIL1_strncmp((char*)cmd, "SetLED", sizeof("SetLED")-1)==0) {
	    p = cmd+sizeof("SetLED")-1;
	    res = UTIL1_xatoi(&p, &tmp);
	    if (res==ERR_OK) {
	      if(tmp==0){
	    	  //LEDS off
	    	  LED_GREEN_Off();
	    	  LED_BLUE_Off();
	    	  LED_RED_Off();

	      }else if(tmp==1){
	    	  //LEDS on
	    	  LED_GREEN_On();
	    	  LED_BLUE_On();
	    	  LED_RED_On();

	      }else if(tmp==2){
	    	  //LED RED
	    	  LED_GREEN_Off();
	    	  LED_BLUE_Off();
	    	  LED_RED_On();

	      }else if(tmp==3){
	    	  //LED GREEN
	    	  LED_GREEN_On();
	    	  LED_BLUE_Off();
	    	  LED_RED_Off();

	      }else if(tmp==4){
	    	  //LED BLUE
	    	  LED_GREEN_Off();
	    	  LED_BLUE_On();
	    	  LED_RED_Off();

	      }else{
	    	  //Unknown Command
	    	  CLS1_SendStr("Unknown Command\n", io->stdOut);
	      }
	      LED_Val = tmp;
	      *handled = TRUE;
	    }
	  }
	else if(UTIL1_strncmp((char*)cmd, "GetLED", sizeof("GetLED")-1)==0){

		UTIL1_Num32sToStr(buf, sizeof(buf), LED_Val);
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("LED_Val", buf, io->stdOut);
		*handled = TRUE;
	 }

	//Commands Infrarot
	else if(UTIL1_strncmp((char*)cmd, "GetINFCM", sizeof("GetINFCM")-1)==0){

		UTIL1_Num32sToStr(buf, sizeof(buf), getcmLF());
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("CMLF", buf, io->stdOut);
		buf[0] = '\0';
		UTIL1_Num32sToStr(buf, sizeof(buf), getcmLB());
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("CMLB", buf, io->stdOut);
		*handled = TRUE;
	}

	//Commands Acceleration
	else if(UTIL1_strncmp((char*)cmd, "GetACCEL", sizeof("GetACCEL")-1)==0){

		UTIL1_Num16sToStr(buf, sizeof(buf), getAccelX());
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("X", buf, io->stdOut);
		buf[0] = '\0';

		UTIL1_Num16sToStr(buf, sizeof(buf), getAccelY());
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("Y", buf, io->stdOut);
		buf[0] = '\0';

		UTIL1_Num16sToStr(buf, sizeof(buf), getAccelZ());
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS1_SendStatusStr("Z", buf, io->stdOut);
		buf[0] = '\0';

		*handled = TRUE;

	}

	//Commands Motor
	else if(UTIL1_strncmp((char*)cmd, "SetMotorLeft", sizeof("SetMotorLeft")-1)==0){
		p = cmd+sizeof("SetMotorLeft")-1;
		res = UTIL1_xatoi(&p, &tmp);
		if (res==ERR_OK) {
			if(tmp > 255){
				setPWMLeft(255);
			}
			if(tmp < -255){
				setPWMLeft(-255);
			}
			else{
				setPWMLeft(tmp);
			}
		}
		*handled = TRUE;

	}
	else if(UTIL1_strncmp((char*)cmd, "SetMotorRight", sizeof("SetMotorRight")-1)==0){
		p = cmd+sizeof("SetMotorRight")-1;
		res = UTIL1_xatoi(&p, &tmp);
		if (res==ERR_OK) {
			if(tmp > 255){
				setPWMRight(255);
			}
			if(tmp < -255){
				setPWMRight(-255);
			}
			else{
				setPWMRight(tmp);
			}
		}
		*handled = TRUE;
	}

	 return res;
}




static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[64];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  //(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}

void createTaskSHELL(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "ShellTask", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


