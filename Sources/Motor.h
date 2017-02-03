/*
 * Motor.h
 *
 *  Created on: 22.12.2016
 *      Author: Fabian
 */

#ifndef SOURCES_MOTOR_H_
#define SOURCES_MOTOR_H_

#include "FRTOS1.h"
#include "WAIT1.h"
#include "CLS1.h"
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



void startPWM(void);

void setPWMLeft(int16_t speed);
void setPWMRight(int16_t speed);

void createTaskMotor(void);

#endif /* SOURCES_MOTOR_H_ */
