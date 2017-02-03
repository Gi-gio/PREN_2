/*
 * Infrarot.h
 *
 *  Created on: 24.11.2016
 *      Author: Fabian
 */

#ifndef SOURCES_INFRAROT_H_
#define SOURCES_INFRAROT_H_


#include "FRTOS1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "AD1.h"

uint16_t getcmLF(void);
uint16_t getcmLB(void);

extern volatile bool AD_finished;

void createTaskInfrarot(void);

#endif /* SOURCES_INFRAROT_H_ */
