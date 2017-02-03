/*
 * Shell.h
 *
 *  Created on: 23.11.2016
 *      Author: Fabian
 */

#ifndef SOURCES_SHELL_H_
#define SOURCES_SHELL_H_


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

#include "Infrarot.h"
#include "Accel.h"
#include "Motor.h"





uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void createTaskSHELL(void);




#endif /* SOURCES_SHELL_H_ */
