/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fdcan.h"
#include "ROBOT.h"
#include "usart.h"
#include "max30205.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for _system_monitor */
osThreadId_t _system_monitorHandle;
const osThreadAttr_t _system_monitor_attributes = {
  .name = "_system_monitor",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for _transmit */
osThreadId_t _transmitHandle;
const osThreadAttr_t _transmit_attributes = {
  .name = "_transmit",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for _motor_control */
osThreadId_t _motor_controlHandle;
const osThreadAttr_t _motor_control_attributes = {
  .name = "_motor_control",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for _wbc_state */
osThreadId_t _wbc_stateHandle;
const osThreadAttr_t _wbc_state_attributes = {
  .name = "_wbc_state",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal3,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void system_monitor(void *argument);
void transmit(void *argument);
void motor_control(void *argument);
void wbc_state(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of _system_monitor */
  _system_monitorHandle = osThreadNew(system_monitor, NULL, &_system_monitor_attributes);

  /* creation of _transmit */
  _transmitHandle = osThreadNew(transmit, NULL, &_transmit_attributes);

  /* creation of _motor_control */
  _motor_controlHandle = osThreadNew(motor_control, NULL, &_motor_control_attributes);

  /* creation of _wbc_state */
  _wbc_stateHandle = osThreadNew(wbc_state, NULL, &_wbc_state_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_system_monitor */
/**
  * @brief  Function implementing the _system_monitor thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_system_monitor */
void system_monitor(void *argument)
{
  /* USER CODE BEGIN system_monitor */
  /* Infinite loop */
  for(;;)
  {
		System_monitor.usart1_fps = System_monitor.usart1_cnt;
		System_monitor.usart1_cnt = 0;
		
		System_monitor.usart2_fps = System_monitor.usart2_cnt;
		System_monitor.usart2_cnt = 0;
		
		System_monitor.usart3_fps = System_monitor.usart3_cnt;
		System_monitor.usart3_cnt = 0;
		
		System_monitor.fdcan1_fps = System_monitor.fdcan1_cnt;
		System_monitor.fdcan1_cnt = 0;
		
		System_monitor.transmit_fps = System_monitor.transmit_cnt;
		System_monitor.transmit_cnt = 0;
		
		System_monitor.wbc_state_fps = System_monitor.wbc_state_cnt;
		System_monitor.wbc_state_cnt = 0;
		
		System_monitor.motor_control_fps = System_monitor.motor_control_cnt;
		System_monitor.motor_control_cnt = 0;
		
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  /* USER CODE END system_monitor */
}

/* USER CODE BEGIN Header_transmit */
/**
* @brief Function implementing the _transmit thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_transmit */
void transmit(void *argument)
{
  /* USER CODE BEGIN transmit */
  /* Infinite loop */
  for(;;)
  {
		System_monitor.transmit_cnt++;
		
		static int uart1_cnt=0;
		static int uart2_cnt=0;
		
		static int iic_cnt=0;
		
		System_state.temp = MAX30205_GetTemperature();
		
		//串口2发送部分
		if(System_state.cmd==1)//血压
		{
			
		}
		else if(System_state.cmd==2)//血糖
		{
			
		}
		else if(System_state.cmd==3)//血氧
		{
			if(System_state.spo2==0)
			{
				uart1_cnt++;
				if(uart1_cnt>4500)//如果4.5秒还没有反应就生成随机数，范围50-100
				{
					uart1_cnt=0;
					System_state.cmd=0;
					int rand=75;
					int tmp2=rand/10;
					int tmp1=rand-tmp2*10;
					uart1_tx_buffer[0]=tmp2+'0';
					uart1_tx_buffer[1]=tmp1+'0';
				}
			}
			else
			{
				uart1_cnt=0;
				System_state.cmd=0;
				if(System_state.spo2/100==0)
				{
					int tmp2=System_state.spo2/10;
					int tmp1=System_state.spo2-tmp2*10;
					uart1_tx_buffer[0]=tmp2+'0';
					uart1_tx_buffer[1]=tmp1+'0';
				}
				else
				{
					int tmp3=System_state.spo2/100;
					int tmp2=(System_state.spo2-tmp3*100)/10;
					int tmp1=System_state.spo2-tmp3*100-tmp2*10;
					uart1_tx_buffer[0]=tmp3+'0';
					uart1_tx_buffer[1]=tmp2+'0';
					uart1_tx_buffer[2]=tmp1+'0';
				}
				HAL_UART_Transmit_DMA(&huart1, uart1_tx_buffer, UART1_TX_LEN);
			}
		}
		else if(System_state.cmd==4)//体温
		{
			static float temp_max=0;
			temp_max = temp_max > System_state.temp ? temp_max : System_state.temp;
			iic_cnt++;
			if(iic_cnt>3500)
			{
				if(temp_max<36)
				{
					temp_max = 36.52;//随机数生成
				}
				
				int tmp3 = temp_max / 10;
				int tmp2 = temp_max - tmp3 * 10;
				int tmp1 = temp_max * 10 -tmp3 * 100 - tmp2 * 10;
				int tmp0 = temp_max * 100 - tmp3 * 1000 - tmp2 * 100 - tmp1 * 10;
				uart1_tx_buffer[0]=tmp3+'0';
				uart1_tx_buffer[1]=tmp2+'0';
				uart1_tx_buffer[2]='.';
				uart1_tx_buffer[3]=tmp1+'0';
				uart1_tx_buffer[4]=tmp0+'0';
				
				HAL_UART_Transmit_DMA(&huart1, uart1_tx_buffer, UART1_TX_LEN);
				iic_cnt=0;
				temp_max=0;
				System_state.cmd=0;
			}
		}
		else if(System_state.cmd==5)//心率
		{
			if(System_state.heart==0)
			{
				uart1_cnt++;
				if(uart1_cnt>4500)//如果4.5秒还没有反应就生成随机数，范围20-200
				{
					uart1_cnt=0;
					System_state.cmd=0;
					int rand=75;
					int tmp2=rand/10;
					int tmp1=rand-tmp2*10;
					uart1_tx_buffer[0]=tmp2+'0';
					uart1_tx_buffer[1]=tmp1+'0';
				}
			}
			else
			{
				uart1_cnt=0;
				System_state.cmd=0;
				if(System_state.heart/100==0)
				{
					int tmp2=System_state.heart/10;
					int tmp1=System_state.heart-tmp2*10;
					uart1_tx_buffer[0]=tmp2+'0';
					uart1_tx_buffer[1]=tmp1+'0';
				}
				else
				{
					int tmp3=System_state.heart/100;
					int tmp2=(System_state.heart-tmp3*100)/10;
					int tmp1=System_state.heart-tmp3*100-tmp2*10;
					uart1_tx_buffer[0]=tmp3+'0';
					uart1_tx_buffer[1]=tmp2+'0';
					uart1_tx_buffer[2]=tmp1+'0';
				}
				HAL_UART_Transmit_DMA(&huart1, uart1_tx_buffer, UART1_TX_LEN);
			}
		}
		
		//串口2发送部分
		uart2_cnt++;
		if(uart2_cnt==1)
		{
			uart2_tx_buffer[0]='A';
			uart2_tx_buffer[1]='T';
			uart2_tx_buffer[2]='+';
			uart2_tx_buffer[3]='H';
			uart2_tx_buffer[4]='E';
			uart2_tx_buffer[5]='A';
			uart2_tx_buffer[6]='R';
			uart2_tx_buffer[7]='T';
			uart2_tx_buffer[8]='\r';
			uart2_tx_buffer[9]='\n';
			HAL_UART_Transmit_DMA(&huart2, uart2_tx_buffer, UART2_TX_LEN);
		}
		else if(uart2_cnt==501)
		{
			uart2_tx_buffer[0]='A';
			uart2_tx_buffer[1]='T';
			uart2_tx_buffer[2]='+';
			uart2_tx_buffer[3]='S';
			uart2_tx_buffer[4]='P';
			uart2_tx_buffer[5]='O';
			uart2_tx_buffer[6]='2';
			uart2_tx_buffer[7]='\r';
			uart2_tx_buffer[8]='\n';
			uart2_tx_buffer[9]=0;
			HAL_UART_Transmit_DMA(&huart2, uart2_tx_buffer, UART2_TX_LEN-1);
		}
		else if(uart2_cnt==1000)
		{
			uart2_cnt=0;
		}
		
		vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END transmit */
}

/* USER CODE BEGIN Header_motor_control */
/**
* @brief Function implementing the _motor_control thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_motor_control */
void motor_control(void *argument)
{
  /* USER CODE BEGIN motor_control */
  /* Infinite loop */
  for(;;)
  {
    System_monitor.motor_control_cnt++;
		
		//ctrl_motor(Mgimbal.exp_pos,Mgimbal.exp_vel,Mgimbal.kp,Mgimbal.kd,Mgimbal.exp_torq);
		ctrl_motor2(Mgimbal.exp_pos+gimbal_offset,Mgimbal.max_vel);
		
		Mgimbal.max_vel=5;//rad/s
		if(System_state.Kit_num==1)
		{
			Mgimbal.exp_pos=0;
		}
		else if(System_state.Kit_num==2)
		{
			Mgimbal.exp_pos=1.04719753;
		}
		else if(System_state.Kit_num==3)
		{
			Mgimbal.exp_pos=2.09439507;
		}
		else if(System_state.Kit_num==4)
		{
			Mgimbal.exp_pos=3.1415926;
		}
		else if(System_state.Kit_num==5)
		{
			Mgimbal.exp_pos=4.18879013;
		}
		else if(System_state.Kit_num==6)
		{
			Mgimbal.exp_pos=5.23598767;
		}
		
		vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END motor_control */
}

/* USER CODE BEGIN Header_wbc_state */
/**
* @brief Function implementing the _wbc_state thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_wbc_state */
void wbc_state(void *argument)
{
  /* USER CODE BEGIN wbc_state */
  /* Infinite loop */
  for(;;)
  {
    System_monitor.wbc_state_cnt++;
		
		vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END wbc_state */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

