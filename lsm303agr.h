/**
  ******************************************************************************
  * @file    lsm303agr.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the lsm303agr.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LSM303AGR_H
#define __LSM303AGR_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
 #include <stdint.h>
 #include "stm32f3xx_hal.h" //PAS_MAG

 #define ABS(x)         (x < 0) ? (-x) : x //PAS_MAG

/******************************************************************************/
/*************************** START REGISTER MAPPING  **************************/
/******************************************************************************/
/* Exported constant IO ------------------------------------------------------*/
#define MAG_I2C_ADDRESS                     0x3C
#define LSM303DLHC_WHO_AM_I_ADDR            0x0F  /* device identification register */

 /* Magnetometer */
#define LSM303AGR_X_REG_L_M                 0x45  /* Hard-iron X magnetic field */
#define LSM303AGR_X_REG_H_M                 0x46  /* Hard-iron X magnetic field */
#define LSM303AGR_Y_REG_L_M                 0x47  /* Hard-iron Y magnetic field */
#define LSM303AGR_Y_REG_H_M                 0x48  /* Hard-iron Y magnetic field */
#define LSM303AGR_Z_REG_L_M                 0x49  /* Hard-iron Z magnetic field */
#define LSM303AGR_Z_REH_H_M                 0x4A  /* Hard-iron Z magnetic field */

#define LSM303AGR_WHO_AM_I_M                0x4F  /* Who am i register magnetic field (0x40) */

#define LSM303AGR_CFG_REG_A_M               0x60  /* Configuration register A magnetic field */
#define LSM303AGR_CFG_REG_B_M               0x61  /* Configuration register B magnetic field */
#define LSM303AGR_CFG_REG_C_M               0x62  /* Configuration register C magnetic field */

#define LSM303AGR_INT_CTRL_REG_M            0x63  /* interrupt control register magnetic field */
#define LSM303AGR_INT_SOURCE_REG_M          0x64  /* interrupt source register magnetic field */
#define LSM303AGR_INT_THS_L_REG_M           0x65  /* interrupt threshold register magnetic field */
#define LSM303AGR_INT_THS_H_REG_M           0x66  /* interrupt threshold register magnetic field*/

#define LSM303AGR_STATUS_REG_M              0x67  /* Status Register magnetic field */

#define LSM303AGR_OUTX_L_REG_M              0x68  /* Output Register X magnetic field */
#define LSM303AGR_OUTX_H_REG_M              0x69  /* Output Register X magnetic field */
#define LSM303AGR_OUTY_L_REG_M              0x6A  /* Output Register Y magnetic field */
#define LSM303AGR_OUTY_H_REG_M              0x6B  /* Output Register Y magnetic field */
#define LSM303AGR_OUTZ_L_REG_M              0x6C  /* Output Register Z magnetic field */
#define LSM303AGR_OUTZ_H_REG_M              0x6D  /* Output Register Z magnetic field */

/******************************************************************************/
/**************************** END REGISTER MAPPING  ***************************/
/******************************************************************************/

#define I_AM_LSM303AGR                     ((uint8_t)0x33)
#define LSM303AGR_MAGNETO_ID               ((uint8_t)0x40)

/*Mag_Data_Rate*/
#define LSM303AGR_ODR_0_75_HZ              ((uint8_t) 0x00)  /*!< Output Data Rate = 0.75 Hz */
#define LSM303AGR_ODR_1_5_HZ               ((uint8_t) 0x04)  /*!< Output Data Rate = 1.5 Hz */
#define LSM303AGR_ODR_3_0_HZ               ((uint8_t) 0x08)  /*!< Output Data Rate = 3 Hz */
#define LSM303AGR_ODR_7_5_HZ               ((uint8_t) 0x0C)  /*!< Output Data Rate = 7.5 Hz */
#define LSM303AGR_ODR_15_HZ                ((uint8_t) 0x10)  /*!< Output Data Rate = 15 Hz */
#define LSM303AGR_ODR_30_HZ                ((uint8_t) 0x14)  /*!< Output Data Rate = 30 Hz */
#define LSM303AGR_ODR_75_HZ                ((uint8_t) 0x18)  /*!< Output Data Rate = 75 Hz */
#define LSM303AGR_ODR_220_HZ               ((uint8_t) 0x1C)  /*!< Output Data Rate = 220 Hz */
 
/*Mag_Full_Scale*/
#define  LSM303AGR_FS_1_3_GA               ((uint8_t) 0x20)  /*!< Full scale = �1.3 Gauss */
#define  LSM303AGR_FS_1_9_GA               ((uint8_t) 0x40)  /*!< Full scale = �1.9 Gauss */
#define  LSM303AGR_FS_2_5_GA               ((uint8_t) 0x60)  /*!< Full scale = �2.5 Gauss */
#define  LSM303AGR_FS_4_0_GA               ((uint8_t) 0x80)  /*!< Full scale = �4.0 Gauss */
#define  LSM303AGR_FS_4_7_GA               ((uint8_t) 0xA0)  /*!< Full scale = �4.7 Gauss */
#define  LSM303AGR_FS_5_6_GA               ((uint8_t) 0xC0)  /*!< Full scale = �5.6 Gauss */
#define  LSM303AGR_FS_8_1_GA               ((uint8_t) 0xE0)  /*!< Full scale = �8.1 Gauss */
 
/*Magnetometer_Sensitivity*/
#define LSM303AGR_M_SENSITIVITY_XY_1_3Ga     1100  /*!< magnetometer X Y axes sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_1_9Ga     855   /*!< magnetometer X Y axes sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_2_5Ga     670   /*!< magnetometer X Y axes sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_4Ga       450   /*!< magnetometer X Y axes sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_4_7Ga     400   /*!< magnetometer X Y axes sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_5_6Ga     330   /*!< magnetometer X Y axes sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_8_1Ga     230   /*!< magnetometer X Y axes sensitivity for 8.1 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_1_3Ga      980   /*!< magnetometer Z axis sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_1_9Ga      760   /*!< magnetometer Z axis sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_2_5Ga      600   /*!< magnetometer Z axis sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_4Ga        400   /*!< magnetometer Z axis sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_4_7Ga      355   /*!< magnetometer Z axis sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_5_6Ga      295   /*!< magnetometer Z axis sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_8_1Ga      205   /*!< magnetometer Z axis sensitivity for 8.1 Ga full scale [LSB/Ga] */

/*Mag_Working_Mode*/
#define LSM303AGR_CONTINUOS_CONVERSION      ((uint8_t) 0x00)   /*!< Continuous-Conversion Mode */
#define LSM303AGR_SINGLE_CONVERSION         ((uint8_t) 0x01)   /*!< Single-Conversion Mode */
#define LSM303AGR_SLEEP                     ((uint8_t) 0x02)   /*!< Sleep Mode */                       

/*Mag_Temperature_Sensor*/
#define LSM303AGR_TEMPSENSOR_ENABLE         ((uint8_t) 0x80)   /*!< Temp sensor Enable */
#define LSM303AGR_TEMPSENSOR_DISABLE        ((uint8_t) 0x00)   /*!< Temp sensor Disable */

#define LSM303AGR_BDU_ENABLE                ((uint8_t) 0x10)  //PAS: Включение бита BDU
  
 //void Mag_Ini(void);//PAS: https://narodstream.ru/urok-51-podkljuchaem-magnitometr-lis3mdl-chast-1/
 //void Mag_Read(void);//PAS: https://narodstream.ru/urok-51-podkljuchaem-magnitometr-lis3mdl-chast-1/


#ifdef __cplusplus
}
#endif

#endif /* __LSM303AGR_H */
