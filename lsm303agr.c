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

