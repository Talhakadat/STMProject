/*
 * BMP280.h
 *
 *  Created on: Jul 10, 2024
 *      Author: kadat
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#include <math.h>

#define altitude(p)			(double)(44330 * (1 - pow((double)p / 101325.0 , 1/5255)))

#define dev_addr 						( 0x76 << 1 )
#define mem_Addr						(0xF4)
#define calib_addr						(0x88)
#define mem_addr2						(0xF5)
#define readingBit						(0xF7)
#define mem_size						(1)
#define sizeOfConfigRegister			(6)
#define timeOut							(100)
/*
 * Power mode definition
 * register 0xF4
 *
 */
#define mode_bit				(0)

#define sleep 					(0x0)
#define force					(0x1)
#define normal					(0x3)

/*****************************************************/


/*
 * t_standby definition
 * register 0xF5
 *
 */
#define t_sb_bit				(0x5)

#define t_sb_half 			    (0)
#define t_sb_62_half			(1)
#define t_sb_125				(2)
#define t_sb_250				(3)
#define t_sb_500				(4)
#define t_sb_1000				(5)
#define t_sb_2000				(6)
#define t_sb_4000				(7)

/******************************************************/


/*
 *pressure oversampling macro definition
 *register 0xF4
 */
#define oversampling_p_bit		(0x2)

#define oversampling_p_1  		(1)
#define oversampling_p_2		(2)
#define oversampling_p_4		(3)
#define oversampling_p_8		(4)
#define oversampling_p_16		(5)

/*******************************************************/


/*
 * temprature oversampling macro definition
 * register oxF4
 */
#define oversampling_t_bit		(0x5)

#define oversampling_t_1  		(1)
#define oversampling_t_2		(2)
#define oversampling_t_4		(3)
#define oversampling_t_8		(4)
#define oversampling_t_16		(5)

/*******************************************************/

typedef struct{
	volatile uint32_t adc_T;
	volatile uint32_t adc_P;
	double data_P;
	double data_T;
	double altitude;
	uint8_t *pData;
	uint8_t *rawData;
}BMP280_HandleTypedef_t;

HAL_StatusTypeDef readFromDeviceITBMP(BMP280_HandleTypedef_t *Handle,  uint8_t addr, uint8_t devAddr);
HAL_StatusTypeDef BMP280Init(uint8_t mode, uint8_t oversamole_t, uint8_t oversample_p, uint8_t t_sb );
uint8_t BMP280Ready(void);
void BMP280CalculateData(BMP280_HandleTypedef_t *Handle);
void BMP280CalibData(BMP280_HandleTypedef_t *Handle);


#endif /* INC_BMP280_H_ */
