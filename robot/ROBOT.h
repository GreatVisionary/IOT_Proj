#ifndef ROBOT_H
#define ROBOT_H

#include "stm32h7xx_hal.h"

#define UART1_RX_LEN 10
#define UART2_RX_LEN 20
#define UART3_RX_LEN 10

#define UART1_TX_LEN 10
#define UART2_TX_LEN 10
#define UART3_TX_LEN 10

#define FDCAN1_RX_LEN 8

#define P_MIN -12.5
#define P_MAX 12.5
#define V_MIN -45
#define V_MAX 45
#define KP_MIN 0
#define KP_MAX 500
#define KD_MIN 0
#define KD_MAX 5
#define T_MIN -18
#define T_MAX 18

extern uint8_t uart1_rx_buffer[];//ÍøÂç
extern uint8_t uart2_rx_buffer[];//ÐÄÂÊÑªÑõ
extern uint8_t uart3_rx_buffer[];//ÑªÑ¹

extern uint8_t uart1_tx_buffer[];//ÍøÂçTX
extern uint8_t uart2_tx_buffer[];//ÐÄÂÊÑªÑõTX
extern uint8_t uart3_tx_buffer[];//ÑªÑ¹TX

extern uint8_t Rx_fdcan1[];

typedef struct
{
	int usart1_cnt;
	int usart1_fps;
	
	int usart2_cnt;
	int usart2_fps;
	
	int usart3_cnt;
	int usart3_fps;
	
	int fdcan1_cnt;
	int fdcan1_fps;
	
	int transmit_cnt;
	int transmit_fps;
	
	int motor_control_cnt;
	int motor_control_fps;
	
	int wbc_state_cnt;
	int wbc_state_fps;
	
	
}ST_system_monitor;

extern ST_system_monitor System_monitor;

enum Sys_state
{
	RX_state, CH_state, STOP_state
};

typedef struct
{
	//uint8_t sys_state;
	enum Sys_state sys_state;
	
	uint8_t cmd;//ÑªÑ¹£¨a£©¡¢ÑªÌÇ£¨b£©¡¢ÑªÑõ£¨c£©¡¢ÌåÎÂ£¨d£©¡¢ÐÄÂÊ£¨e£©
	
	uint8_t Kit_num;//Ò©Ïä±àºÅ1¡¢2¡¢3¡¢4¡¢5¡¢6
	
	//Datas
	int spo2;
	int heart;
	float temp;
	
}ST_system_state;

extern ST_system_state System_state;

typedef struct
{
	float pos;
	float vel;
	float torq;
	
//	float kp;
//	float kd;
//	float exp_pos;
//	float exp_vel;
//	float exp_torq;
	
	float exp_pos;
	float max_vel;
}MotorDM;

extern MotorDM Mgimbal;

extern float gimbal_offset;

//debug
extern uint8_t watch_data[];

#endif//ROBOT_H
