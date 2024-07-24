/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */
FDCAN_FilterTypeDef FDCAN1_RXFilter;
/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 5;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 2;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 0;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.RxFifo0ElmtsNbr = 8;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 8;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */
	
	FDCAN1_RXFilter.IdType=FDCAN_STANDARD_ID;
	FDCAN1_RXFilter.FilterIndex=0;
	FDCAN1_RXFilter.FilterType=FDCAN_FILTER_MASK;
	FDCAN1_RXFilter.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;
	FDCAN1_RXFilter.FilterID1=0x0000;
	FDCAN1_RXFilter.FilterID2=0x0000;
	if(HAL_FDCAN_ConfigFilter(&hfdcan1,&FDCAN1_RXFilter)!=HAL_OK)
	{
		Error_Handler();
	}
	
	HAL_FDCAN_Start(&hfdcan1);
	HAL_FDCAN_ActivateNotification(&hfdcan1,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);
	
  /* USER CODE END FDCAN1_Init 2 */

}

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_HSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN1 clock enable */
    __HAL_RCC_FDCAN_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_FDCAN_CLK_DISABLE();

    /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//以下为达妙电机特定传输协议
float uint_to_float(int x_int, float x_min, float x_max, int bits)
{
//converts unsigned int to float , given range and number of bits
	float span=x_max-x_min;
	float offset=x_min;
	return((float)x_int)*span/((float)((1<<bits)-1))+ offset;
}

int float_to_uint(float x,float x_min, float x_max, int bits)
{
//converts a float to an unsigned int, given range and number of bits
	float span=x_max-x_min;
	float offset=x_min;
	return (int)((x-offset)*((float)((1<<bits)-1))/span);
}

void ctrl_motor(float _pos, float _vel, float _KP, float _KD, float _torq)
{
	uint16_t pos_tmp,vel_tmp,kp_tmp,kd_tmp,tor_tmp;
	pos_tmp=float_to_uint( _pos,P_MIN,P_MAX,16);
	vel_tmp=float_to_uint( _vel, V_MIN, V_MAX,12);
	kp_tmp=float_to_uint(_KP,KP_MIN,KP_MAX,12);
	kd_tmp= float_to_uint( _KD, KD_MIN, KD_MAX,12);
	tor_tmp=float_to_uint( _torq,T_MIN, T_MAX, 12);
	
	// 配置Tx Header
	FDCAN_TxHeaderTypeDef Tx_Header;
	Tx_Header.Identifier = 0x01;
	Tx_Header.IdType = FDCAN_STANDARD_ID;
	Tx_Header.TxFrameType = FDCAN_DATA_FRAME;
	Tx_Header.DataLength = 0x08;
	Tx_Header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	Tx_Header.BitRateSwitch = FDCAN_BRS_OFF;
	Tx_Header.FDFormat = FDCAN_CLASSIC_CAN;
	Tx_Header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	Tx_Header.MessageMarker = 0;

	uint8_t Data[8];
	Data[0]=(pos_tmp >>8);
	Data[1]= pos_tmp ;
	Data[2]=(vel_tmp >>4);
	Data[3]=((vel_tmp & 0xF)<<4) | (kp_tmp >> 8);
	Data[4] = kp_tmp;
	Data[5] = (kd_tmp >> 4);
	Data[6] = ((kd_tmp & 0xF)<<4) | (kp_tmp >> 8);
	Data[7] = tor_tmp;
	
	memcpy(&watch_data[0], &Data[0], 8);
	
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &Tx_Header, Data) != HAL_OK)
	{
    // 发送失败处理代码，可以根据需要重试或进行其他处理
    Error_Handler();
	}
}

void ctrl_motor2(float _pos, float _vel)
{
	uint8_t *pbuf,*vbuf;
	pbuf=(uint8_t*)&_pos;
	vbuf=(uint8_t*)&_vel;
	
	// 配置Tx Header
	FDCAN_TxHeaderTypeDef Tx_Header;
	Tx_Header.Identifier = 0x101;//0x100+0x01
	Tx_Header.IdType = FDCAN_STANDARD_ID;
	Tx_Header.TxFrameType = FDCAN_DATA_FRAME;
	Tx_Header.DataLength = 0x08;
	Tx_Header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	Tx_Header.BitRateSwitch = FDCAN_BRS_OFF;
	Tx_Header.FDFormat = FDCAN_CLASSIC_CAN;
	Tx_Header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	Tx_Header.MessageMarker = 0;
	
	uint8_t Data[8];
	Data[0] = *pbuf;
	Data[1] = *(pbuf+1);
	Data[2] = *(pbuf+2);
	Data[3] = *(pbuf+3);
	Data[4] = *vbuf;
	Data[5] = *(vbuf+1);
	Data[6] = *(vbuf+2);
	Data[7] = *(vbuf+3);
	
	memcpy(&watch_data[0], &Data[0], 8);
	
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &Tx_Header, Data) != HAL_OK)
	{
    // 发送失败处理代码，可以根据需要重试或进行其他处理
    Error_Handler();
	}
}

uint8_t FDCAN1_Send_Msg(uint8_t *pData, uint32_t Len)
{
	static FDCAN_TxHeaderTypeDef Tx_Header;
    
	// 设置FDCAN Tx Header参数
	Tx_Header.Identifier = 0x101;
	Tx_Header.IdType = FDCAN_STANDARD_ID;
	Tx_Header.TxFrameType = FDCAN_DATA_FRAME;
	Tx_Header.DataLength = Len;  // FDCAN uses a shifted value for the length
	Tx_Header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	Tx_Header.BitRateSwitch = FDCAN_BRS_OFF;
	Tx_Header.FDFormat = FDCAN_CLASSIC_CAN;
	Tx_Header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	Tx_Header.MessageMarker = 0;
    
	// 尝试将消息添加到发送FIFO队列中
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &Tx_Header, pData) != HAL_OK)
	{
		// 如果发送失败，处理错误
		Error_Handler();
		return HAL_ERROR;
	}
	return HAL_OK;
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	static uint8_t catch_init = 0;
	static uint8_t slide_init = 0;
	if (hfdcan->Instance == FDCAN1)
	{
		System_monitor.fdcan1_cnt++;
			
		uint16_t EncodeNumber;
		int p_int, v_int, t_int;
		FDCAN_RxHeaderTypeDef RxHeader;
        
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, Rx_fdcan1) != HAL_OK)
		{
			// 处理接收错误
			Error_Handler();
		}

		if (RxHeader.Identifier == 0x11)
		{
			p_int = (Rx_fdcan1[1] << 8) | Rx_fdcan1[2];
			v_int = (Rx_fdcan1[3] << 4) | (Rx_fdcan1[4] >> 4);
			t_int = ((Rx_fdcan1[4] & 0xF) << 8) | Rx_fdcan1[5];
			Mgimbal.pos = uint_to_float(p_int, P_MIN, P_MAX, 16);
			Mgimbal.vel = uint_to_float(v_int, V_MIN, V_MAX, 12);
			Mgimbal.torq = uint_to_float(t_int, T_MIN, T_MAX, 12);
		}
	}
}


/* USER CODE END 1 */
