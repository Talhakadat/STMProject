/*
 * MPU6050.c
 *
 *  Created on: Jul 10, 2024
 *      Author: kadat
 */

#include "MPU6050.h"
#include "main.h"
#include <stdio.h>
#include <math.h>
extern I2C_HandleTypeDef hi2c1;


HAL_StatusTypeDef MPU_sleep_Mode(StateOfDevice_t StateOfDevice){
	uint8_t status = 0;
	uint8_t addr = 0;
	if(StateOfDevice == Awake){
		CLEAR_BIT(addr, 1 << sleepMode_bit);
	}
	else{
		SET_BIT(addr, 1 << sleepMode_bit);
	}
	status = HAL_I2C_Mem_Write(&hi2c1, dev_addr_AD0 ,(107 << 1) + 0, 1, &addr, 1, 100);
	if(HAL_OK != status){
		return HAL_ERROR;
	}
	else{
		return HAL_OK;
	}
}

HAL_StatusTypeDef MPUInitialize(MPUHandleTypedef_t *MPUHandle){
	HAL_StatusTypeDef status1, status2, status3;
	uint8_t addr_gyro = 0, addr_acc = 0;

	status1 = MPU_sleep_Mode(MPUHandle->Sleep);

	if(HAL_OK == status1){
		SET_BIT(addr_gyro, MPUHandle->AFS_SEL_Acc  << configBit);
		SET_BIT(addr_acc , MPUHandle->FS_SEL_Gyro  << configBit);
		status2 = HAL_I2C_Mem_Write(&hi2c1, dev_addr_AD0, FS_SEL_GyroAddr, 1, &addr_gyro, 1, 100);
		status3 = HAL_I2C_Mem_Write(&hi2c1, dev_addr_AD0, AFS_SEL_ACCAddr, 1, &addr_acc, 1, 100);

		if(HAL_OK == status2 && HAL_OK == status3)
		{
			switch(MPUHandle->FS_SEL_Gyro)
			{
			case 0 : MPUHandle->FS_divide = 131  ; break;
			case 1 : MPUHandle->FS_divide = 65.5 ; break;
			case 2 : MPUHandle->FS_divide = 32.8 ; break;
			case 3 : MPUHandle->FS_divide = 16.4 ;

			}

			switch(MPUHandle->AFS_SEL_Acc)
			{
			case 0 : MPUHandle->AFS_divide = 16318; break;
			case 1 : MPUHandle->AFS_divide = 8192 ; break;
			case 2 : MPUHandle->AFS_divide = 4096 ; break;
			case 3 : MPUHandle->AFS_divide = 2048 ;

			}
			return HAL_OK;

		}
		else
		{
			return HAL_ERROR;
		}
	}
	else
	{
		return HAL_ERROR;

	}


}

void MPUGenerateData(MPUHandleTypedef_t *MPUHandle, uint8_t *pBuffer){

		MPUHandle->Raw_Gyro_Acc.ACC_XOUTH_Raw  = (uint16_t) tracking(pBuffer[0] , pBuffer[1]) ;
		MPUHandle->Raw_Gyro_Acc.ACC_YOUTH_Raw  = (uint16_t) tracking(pBuffer[2] , pBuffer[3]) ;
		MPUHandle->Raw_Gyro_Acc.ACC_ZOUTH_Raw  = (uint16_t) tracking(pBuffer[4] , pBuffer[5]) ;
		MPUHandle->Raw_Gyro_Acc.GYRO_XOUTH_Raw = (uint16_t) tracking(pBuffer[8] , pBuffer[9]) ;
		MPUHandle->Raw_Gyro_Acc.GYRO_YOUTH_Raw = (uint16_t) tracking(pBuffer[10], pBuffer[11]);
		MPUHandle->Raw_Gyro_Acc.GYRO_ZOUTH_Raw = (uint16_t) tracking(pBuffer[12], pBuffer[13]);


		MPUHandle->Last_Gyro_Acc.ACC_XOUTH  = MPUHandle->Raw_Gyro_Acc.ACC_XOUTH_Raw  / 8192;
		MPUHandle->Last_Gyro_Acc.ACC_YOUTH  = MPUHandle->Raw_Gyro_Acc.ACC_YOUTH_Raw  / 8192;
		MPUHandle->Last_Gyro_Acc.ACC_ZOUTH  = MPUHandle->Raw_Gyro_Acc.ACC_ZOUTH_Raw  / 8192;
		MPUHandle->Last_Gyro_Acc.GYRO_XOUTH = MPUHandle->Raw_Gyro_Acc.GYRO_XOUTH_Raw / 32.8 ;
		MPUHandle->Last_Gyro_Acc.GYRO_YOUTH = MPUHandle->Raw_Gyro_Acc.GYRO_YOUTH_Raw / 32.8 ;
		MPUHandle->Last_Gyro_Acc.GYRO_ZOUTH = MPUHandle->Raw_Gyro_Acc.GYRO_ZOUTH_Raw / 32.8 ;

}

