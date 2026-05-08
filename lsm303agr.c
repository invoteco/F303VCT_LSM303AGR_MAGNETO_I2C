/**
  ******************************************************************************
  * @file    lsm303agr.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the lsm303agr
  *          MEMS accelerometer.
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
/* Includes ------------------------------------------------------------------*/
#include "lsm303agr.h"

/*LSM303AGR_Private_Variables*/
///ACCELERO_DrvTypeDef Lsm303agrDrv =
//{
 // LSM303AGR_AccInit,
 // LSM303AGR_AccDeInit,
 // LSM303AGR_AccReadID,
 // LSM303AGR_AccRebootCmd,
 // 0,
 // LSM303AGR_AccZClickITConfig,
 // 0,
 // 0,
//  0,
 // 0,
 // LSM303AGR_AccFilterConfig,
 // LSM303AGR_AccFilterCmd,
 // LSM303AGR_AccReadXYZ
//};

/**
  * @brief  Set LSM303AGR Mag Initialization.
  * @param  LSM303AGR_InitStruct: pointer to a LSM303AGR_MagInitTypeDef structure
  *         that contains the configuration setting for the LSM303AGR.
  * @retval None
  */
//void LSM303AGR_MagInit(LSM303AGRMag_InitTypeDef *LSM303AGR_InitStruct)
//{
//  uint8_t cra_regm = 0x00, crb_regm = 0x00, mr_regm = 0x00;
  
//  /* Configure MEMS: temp and Data rate */
//  cra_regm |= (uint8_t) (LSM303AGR_InitStruct->Temperature_Sensor | LSM303AGR_InitStruct->MagOutput_DataRate);
  
//  /* Configure MEMS: full Scale */
//  crb_regm |= (uint8_t) (LSM303AGR_InitStruct->MagFull_Scale);
  
//  /* Configure MEMS: working mode */
//  mr_regm |= (uint8_t) (LSM303AGR_InitStruct->Working_Mode);
  
//  /* Write value to Mag MEMS CRA_REG register */
//  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303AGR_CRA_REG_M, 1, &cra_regm);
  
//  /* Write value to Mag MEMS CRB_REG register */
//  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303AGR_CRB_REG_M, 1, &crb_regm);
  
//  /* Write value to Mag MEMS MR_REG register */
////  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303AGR_MR_REG_M, 1, &mr_regm);
//}





/**
  * @brief  Get status for Mag LSM303AGR data
  * @param  None
  * @retval Data status in a LSM303AGR Data register
  */
uint8_t LSM303AGR_MagGetDataStatus(void)
{
  uint8_t tmpreg = 0;
  
  /* Read Mag STATUS register */
  //COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303AGR_SR_REG_M, 1, &tmpreg);
  
  return tmpreg;
}

