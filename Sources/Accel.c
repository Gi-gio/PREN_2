/*
 * Accel.c
 *
 *  Created on: 02.12.2016
 *      Author: Fabian
 */


#include "Accel.h"


/* External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A
/* MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02

/* External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

static MMA8451_TDataState deviceData;
static int8_t xyz[3];
uint8_t res;

uint8_t MMA8451_ReadReg(uint8_t addr, uint8_t *data, short dataSize) {

  /* Send I2C address plus register address to the I2C bus *without* a stop condition */
  res = I2C1_MasterSendBlock(deviceData.handle, &addr, 1U, LDD_I2C_NO_SEND_STOP);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  while (!deviceData.dataTransmittedFlg) {} /* Wait until data is sent */
  deviceData.dataTransmittedFlg = FALSE;

  /* Receive InpData (1 byte) from the I2C bus and generates a stop condition to end transmission */
  res = I2C1_MasterReceiveBlock(deviceData.handle, data, dataSize, LDD_I2C_SEND_STOP);
  if (res!=ERR_OK) {
	  return ERR_FAILED;
  }
  while (!deviceData.dataReceivedFlg) {} /* Wait until data is received received */
  deviceData.dataReceivedFlg = FALSE;
  return ERR_OK;
}

uint8_t MMA8451_WriteReg(uint8_t addr, uint8_t val) {
  uint8_t buf[2];

  buf[0] = addr;
  buf[1] = val;
	res = I2C1_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP); /* Send OutData (3 bytes with address) on the I2C bus and generates not a stop condition to end transmission */
	if (res!=ERR_OK) {
	  return ERR_FAILED;
	}
  while (!deviceData.dataTransmittedFlg) {}  /* Wait until date is sent */
	deviceData.dataTransmittedFlg = FALSE;
	return ERR_OK;
}

static portTASK_FUNCTION(TaskAccel, pvParameters) {
  (void)pvParameters; /* parameter not used */

  deviceData.handle = I2C1_Init(&deviceData);
    /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
     * ACTIVE: Full scale selection
     */
  res = MMA8451_WriteReg(MMA8451_CTRL_REG_1,  MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK);
    if (res==ERR_OK) {
  for(;;) {
	res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xyz, 3);
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  	  }
    }
    //I2C1_Deinit(deviceData.handle); //Error
}


void createTaskAccel(void){
if(FRTOS1_xTaskCreate(TaskAccel,"TaskAccel", configMINIMAL_STACK_SIZE +200, NULL, tskIDLE_PRIORITY +1, (xTaskHandle*)NULL ) != pdPASS)
	{
   for(;;){}; /* Out of heap memory? */
	}
}

int8_t getAccelX(void){
	return xyz[0];
}

int8_t getAccelY(void){
	return xyz[1];
}

int8_t getAccelZ(void){
	return xyz[2];
}


