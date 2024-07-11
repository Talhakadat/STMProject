/*
 * BMP280.c
 *
 *  Created on: Jul 10, 2024
 *      Author: kadat
 */


#include "BMP280.h"

#include "math.h"
extern I2C_HandleTypeDef hi2c1;


HAL_StatusTypeDef BMP280Init(uint8_t mode, uint8_t oversamole_t, uint8_t oversample_p, uint8_t t_sb)
{
	uint8_t tempValue = 0, value = 0;
	uint8_t status1, status2;
	tempValue |= ((oversample_p << oversampling_p_bit) | (oversamole_t << oversampling_t_bit) | (mode << mode_bit));
	value |= (t_sb << (t_sb_bit));
	status1 = HAL_I2C_Mem_Write(&hi2c1,(0x76 << 1) + 0, mem_Addr, 1, &tempValue, 1, 100);
	status2 = HAL_I2C_Mem_Write(&hi2c1, dev_addr, mem_addr2, 1, &value, 1,100);
	if( (HAL_OK != status1) && (HAL_OK != status2) )
	{
		return HAL_ERROR;
	}
	else
	{
		return HAL_OK;
	}
}
void BMP280CalculateData(BMP280_HandleTypedef_t *Handle){

		uint32_t adc_P = 0;
		uint32_t adc_T = 0;
		adc_P = (Handle->rawData[0] << 12U | Handle->rawData[1] << 4U | Handle->rawData[2] >> 4U);
		adc_T = (Handle->rawData[3] << 12U | Handle->rawData[4] << 4U | Handle->rawData[5] >> 4U);

		Handle->adc_P = adc_P;
		Handle->adc_T = adc_T;

}

unsigned short dig_T1;
signed short   dig_T2;
signed short   dig_T3;
unsigned short dig_P1;
signed short   dig_P2;
signed short   dig_P3;
signed short   dig_P4;
signed short   dig_P5;
signed short   dig_P6;
signed short   dig_P7;
signed short   dig_P8;
signed short   dig_P9;


void BMP280CalibData(BMP280_HandleTypedef_t *Handle){
	 uint32_t adc_T = 0;
	 uint32_t adc_P = 0;

	uint8_t calibData[24] = {0};
	adc_T = Handle->adc_T;
	adc_P = Handle->adc_P;
	HAL_I2C_Mem_Read(&hi2c1, dev_addr, 0x88, 1, calibData, 24,100);
	//0x88

	dig_T1 = ((calibData[1]  << 8)  | calibData[0]) ;
	dig_T2 = ((calibData[3]  << 8)  | calibData[2]) ;
	dig_T3 = ((calibData[5]  << 8)  | calibData[4]) ;
	dig_P1 = ((calibData[7]  << 8)  | calibData[6]) ;
	dig_P2 = ((calibData[9]  << 8)  | calibData[8]) ;
	dig_P3 = ((calibData[11] << 8)  | calibData[10]);
	dig_P4 = ((calibData[13] << 8)  | calibData[12]);
	dig_P5 = ((calibData[15] << 8)  | calibData[14]);
	dig_P6 = ((calibData[17] << 8)  | calibData[16]);
	dig_P7 = ((calibData[19] << 8)  | calibData[18]);
	dig_P8 = ((calibData[21] << 8)  | calibData[20]);
	dig_P9 = ((calibData[23] << 8)  | calibData[22]);

	double var1, var2;
	double T1 = 0;
	double P1 = 0;
	int t_fine = 0;
	var1  	   = ((((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0)*((double)dig_T2));
	var2   	   = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0)) * ((double)dig_T3);
	t_fine 	   = (int)(var1+ var2);
	T1    	   = ((var1 + var2)/5120.0);
	Handle->data_T = T1;



	var1 = (((double)t_fine/2.0) - 64000.0);
	var2 = (var1 * var1 * ((double)dig_P6) / 32768.0);
	var2 = (var2 + var1 * ((double)dig_P5) * 2.0);
	var2 = (var2/4.0) + (((double)dig_P4) * 65536.0);
	var1 = ((((double)dig_P3) * var1 * var1/524288.0 + ((double)dig_P2) * var1)/524288.0);
	var1 = (1.0 + var1/32768.0) * ((double)dig_P1);
	P1   = (1048576.0 - (double)adc_P);
	P1   = ((P1 - (var2/4096)) * 6250.0/var1);
	var1 = (((double)dig_P9) * P1 * P1/2147483648.0);
	var2 = (P1 * ((double)dig_P8)/32768.0);
	P1   = (P1 + (var1 + var2 + ((double)dig_P7)) / 16.0);
	Handle->data_P = P1;
	Handle->altitude = (double)(44330 * (1 - pow(Handle->data_P / 101325.0 , (float)1.0/5.255)));

}
