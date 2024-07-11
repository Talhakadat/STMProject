/*
 * MPU6050.h
 *
 *  Created on: Jul 10, 2024
 *      Author: kadat
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"



#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#define division(x,y)	(double)(x)/(double)(y)
#define tracking(x,y)	(x << 8) | (y)

#define dev_addr_AD0					(0x68 << 1)
#define dev_addr_AD1					(0x69 << 1)

#define configBit						(0x3)

#define FS_SEL_GyroAddr					(0x1B)
#define AFS_SEL_ACCAddr					(0x1C)

#define ReadingData_start				(0x3B)


#define sleepMode_bit					(6)
#define PWR_MGMT_1						(0x6B)

#define InterruptBit					(3)
#define InterruptBit1					(0)
#define InterruptRegister				(0x38)



#define ENABLE							(1)
#define DISABLE							(0)

typedef enum{
	Awake,
	Sleep

}StateOfDevice_t;



typedef enum{
	FS_SEL_250 = 0,
	FS_SEL_500,
	FS_SEL_1000,
	FS_SEL_2000

}FS_SEL_GYRO_t;


typedef enum{
	AFS_SEL_2 = 0,
	AFS_SEL_4,
	AFS_SEL_8,
	AFS_SEL_16,


}AFS_SEL_t;

typedef struct{

	double ACC_XOUTH;
	double ACC_YOUTH;
	double ACC_ZOUTH;


	double GYRO_XOUTH;
	double GYRO_YOUTH;
	double GYRO_ZOUTH;

}LastValuableOfAcc_Gyro_t;

typedef struct{

	uint16_t ACC_XOUTH_Raw;
	uint16_t ACC_YOUTH_Raw;
	uint16_t ACC_ZOUTH_Raw;


	uint16_t GYRO_XOUTH_Raw;
	uint16_t GYRO_YOUTH_Raw;
	uint16_t GYRO_ZOUTH_Raw;


}RawValuableOfAcc_Gyro_t;


typedef struct{
	RawValuableOfAcc_Gyro_t  Raw_Gyro_Acc;
	LastValuableOfAcc_Gyro_t Last_Gyro_Acc;
	uint8_t FS_SEL_Gyro;
	uint8_t AFS_SEL_Acc;
	int AFS_divide;
	int FS_divide;
	uint8_t Sleep;
}MPUHandleTypedef_t;



void MPUGenerateData(MPUHandleTypedef_t *MPUHandle, uint8_t *pBuffer);
HAL_StatusTypeDef MPUInitialize(MPUHandleTypedef_t *MPUHandle);

#endif /* INC_MPU6050_H_ */
