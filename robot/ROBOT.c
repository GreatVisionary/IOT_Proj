#include "ROBOT.h"

uint8_t uart1_rx_buffer[UART1_RX_LEN];
uint8_t uart2_rx_buffer[UART2_RX_LEN];
uint8_t uart3_rx_buffer[UART3_RX_LEN];

uint8_t uart1_tx_buffer[UART1_RX_LEN];
uint8_t uart2_tx_buffer[UART2_TX_LEN];
uint8_t uart3_tx_buffer[UART3_RX_LEN];

uint8_t Rx_fdcan1[FDCAN1_RX_LEN];

ST_system_monitor System_monitor;
ST_system_state System_state;
MotorDM Mgimbal;

float gimbal_offset=0;

uint8_t watch_data[8];

