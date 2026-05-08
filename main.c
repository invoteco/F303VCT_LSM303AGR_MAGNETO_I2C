/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  *https://narodstream.ru/urok-51-podkljuchaem-magnitometr-lis3mdl-chast-1/
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lsm303agr.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
uint32_t I2cxTimeout = 0x10000;    /*<! Value of Timeout when I2C communication fails */
uint8_t MagnetoID = 0;
uint8_t InspectionVar = 0;
uint16_t pData[3] = {0};

int16_t mx = 0;
int16_t my = 0;
int16_t mz = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE BEGIN PFP */
static void     I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_ReadData(uint16_t Addr, uint8_t Reg);
static void     I2Cx_Error (void);
uint8_t         Mag_ReadID(void);
void            Mag_Set_ODR_75(void);
void            Mag_Set_ODR_10(void);//Установка ODR в функции инициализации Mag_Init() позволяет инициализировать датчик 1 раз, а данные получать в цикле или Callback-е
void            Mag_Disable(void); //Выключаем
void            Mag_Enable_And_Set_Mode (uint8_t mode);
void            Mag_Enable_BDU(void);
void            Mag_Init(void);
void            Mag_ReadData (void);
void            Mag_GetXYZ(uint16_t* pData);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);

  Mag_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00201D2B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 328; //С этим значением устойчиво работает
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;  //С этим значением устойчиво работает
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : DRDY_Pin */
  GPIO_InitStruct.Pin = DRDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DRDY_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Mag_Init(void)
{
	MagnetoID = Mag_ReadID();
	if (MagnetoID == LSM303AGR_MAGNETO_ID){
		//Mag_Disable(); //Выключаем
		//HAL_Delay(1000);//Типа для стабилизации
		Mag_Enable_And_Set_Mode(1);//Включено единичное измерение
		//HAL_Delay(1000);//Типа для стабилизации
		Mag_Set_ODR_10();
		Mag_Enable_BDU();
		//Mag_Set_ODR_75();
	}
	else{
	    Error_Handler();
	}
}

//PAS: Read identificator from
uint8_t Mag_ReadID(void){
	uint8_t ctrl = 0x00;
	ctrl = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_WHO_AM_I_M);
	return ctrl;
}

//PAS: Отключение магнетометра
void Mag_Disable (void){
	//так в https://narodstream.ru/urok-51-podkljuchaem-magnitometr-lis3mdl-chast-2/
	//uint8_t value = 0;
	//пока выключим датчик (MD = 0x02)
	//value = Mag_IO_Read(MAG_I2C_ADDRESS,LIS3MDL_MAG_CTRL_REG3);
	//value = I2Cx_ReadData(MAG_I2C_ADDRESS, CFG_REG_A_M);
	//value&=~LIS3MDL_MAG_MD_MASK;
	//value|=LIS3MDL_MAG_MD_POWER_DOWN;
	//Mag_IO_Write(MAG_I2C_ADDRESS,LIS3MDL_MAG_CTRL_REG3,value);

	//Конечно, можно проверить регистр LSM303AGR_CFG_REG_A_M на значение, и выключать
	//т.е. записать туда LSM303AGR_SLEEP только в случае, если записанное значение отличается от LSM303AGR_SLEEP,
	//но пока отключаем жестко (в любом случае).
	I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_A_M, LSM303AGR_SLEEP);
}

/**
 *Bключение магнетометра и установка режима измерения
 *@param mode //0  для непрерывного измерения (CONTINUOS_CONVERSION), 1 для одиночного (SINGLE_CONVERSION)
*/
void Mag_Enable_And_Set_Mode (uint8_t mode){
	switch (mode) {
		case 0:
			I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_A_M, LSM303AGR_CONTINUOS_CONVERSION);
		case 1:
			I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_A_M, LSM303AGR_SINGLE_CONVERSION);
			break;
		default:
			I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_A_M, LSM303AGR_CONTINUOS_CONVERSION);
			break;
	}
}

//Включить бит BDU (00010000, 0x10)
void Mag_Enable_BDU(void){
	I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_C_M, LSM303AGR_BDU_ENABLE);
}
//Установка частоты выборки (ODR) в 75 Гц (При этом устанавливается также бит LP (LOW_POWER).Зачем-хрен знает)
//Чтобы без LP (тогда это будет режим HR (Hight Resolution) надо 00001000 или 0x08)
void Mag_Set_ODR_75(void){
	I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_C_M, LSM303AGR_ODR_75_HZ);
}

void Mag_Set_ODR_10(void){
	I2Cx_WriteData(MAG_I2C_ADDRESS, LSM303AGR_CFG_REG_A_M, LSM303AGR_ODR_15_HZ);
}



//Get Magnetometer data
void Mag_GetXYZ(uint16_t* pData){
    uint8_t buffer[6];

    uint8_t i = 0;
    buffer[0] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTX_L_REG_M);
    buffer[1] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTX_H_REG_M );
    buffer[2] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTY_L_REG_M);
    buffer[3] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTY_H_REG_M);
    buffer[4] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTZ_L_REG_M);
    buffer[5] = I2Cx_ReadData(MAG_I2C_ADDRESS, LSM303AGR_OUTZ_H_REG_M);

    for(i=0;i<3;i++){
       pData[i] = ((int16_t)((uint16_t)buffer[2*i+1]<<8)+buffer[2*i]);
    }
}

/**
  * @Read a value in a register of the device through BUS.
  * @param  Addr Device address on BUS Bus.
  * @param  Reg The target register address to read
  * @retval Data read at register @
  */
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;

  status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error();
  }
  return value;
}

/**
  * @Write a value in a register of the device through BUS.
  * @param  Addr Device address on BUS Bus.
  * @param  Reg The target register address to write
  * @param  Value The target register value to be written
  * @retval  None
  */
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error();
 }
}
/**
  * @I2C3 error treatment function
  * @retval None
  */
static void I2Cx_Error (void)
{
  /* De-initialize the I2C communication BUS */
  HAL_I2C_DeInit(&hi2c1);
  /* Re- Initiaize the I2C communication BUS */
  MX_I2C1_Init();
}

//https://narodstream.ru/urok-51-podkljuchaem-magnitometr-lis3mdl-chast-2/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim -> Instance == TIM1) //если будет несколько таймеров, чтобы попасть именно в нужный
		{
		    Mag_ReadData ();
		}
}

void Mag_ReadData (void){
	  Mag_GetXYZ(pData);
	  mx = pData[0];
	  my = pData[1];
	  mz = pData[2];
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
