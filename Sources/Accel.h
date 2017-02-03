/*
 * Accel.h
 *
 *  Created on: 02.12.2016
 *      Author: Fabian
 */

#ifndef ACCEL_H_
#define ACCEL_H_


#include "FRTOS1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "I2C1.h"
#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
  volatile bool dataReceivedFlg; /* set to TRUE by the interrupt if we have received data */
  volatile bool dataTransmittedFlg; /* set to TRUE by the interrupt if we have set data */
  LDD_TDeviceData *handle; /* pointer to the device handle */
} MMA8451_TDataState;

uint8_t MMA8451_ReadReg(uint8_t addr, uint8_t *data, short dataSize);

uint8_t MMA8451_WriteReg(uint8_t addr, uint8_t val);

int8_t getAccelX(void);
int8_t getAccelY(void);
int8_t getAccelZ(void);


void createTaskAccel(void);

#endif /* ACCEL_H_ */
