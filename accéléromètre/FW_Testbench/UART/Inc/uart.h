/**
 * @file uart.h
 * @author HEKA
 * @brief Header file for UART communication with the interface
 *
 * @date 2023-10-05
 * 
 * @copyright Copyright HEKA (c) 2023
 * 
 */

#include "stdbool.h"
#include "usart.h"

/* Constants */
#define NUMBER_OF_BYTES_PER_MSG 4
#define INDEX_FIRST_BYTE 	0
#define INDEX_SECOND_BYTE 	1
#define INDEX_THIRD_BYTE 	2
#define INDEX_FOURTH_BYTE 	3

/**
 * Structure describing the UART module
 */
typedef struct
{
	bool is_uart_initialized;
	UART_HandleTypeDef * uart_handle;
	uint8_t * message_received;
	uint8_t * message_to_send;
} UART;

/* Function protoytpes */
void UART_Init(void);
void UART_Task(void);
