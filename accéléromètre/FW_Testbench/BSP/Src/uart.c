/**
 * @file uart.c
 * @author HEKA
 * @brief UART communication with the interface
 *
 * @date 2023-10-05
 * 
 * @copyright Copyright HEKA (c) 2023
 * 
 */

#include "../Inc/uart.h"
#include "../Inc/motor_control.h"
#include "main.h"

/* External variables */
extern Motor g_base_motor;

/* Private functions declaration */
static void Receive_Data(UART * uart);

/* Global variables */
uint8_t g_rx_buffer[NUMBER_OF_BYTES_PER_MSG] = {0};

UART g_uart =
{
	.is_uart_initialized = false,
	.uart_handle = 0u,
	.message_received = g_rx_buffer,
};

/**
 * @brief Initialization of the UART communication with the interface
 * 
 */
void UART_Init(void)
{
    /* Initialize the UART communication */
	g_uart.uart_handle = &huart2;

	g_uart.is_uart_initialized = true;
}

/**
 * @brief Communication task
 * 
 */
void UART_Task(void)
{
	if (g_uart.is_uart_initialized)

		/* Receive data from the interface */
		Receive_Data(&g_uart);

		/* Update the data structure with desired speed and angle for every motor */
		g_base_motor.motor_speed_percent = (g_uart.message_received[INDEX_FIRST_BYTE] + (g_uart.message_received[INDEX_SECOND_BYTE] << 8));
		g_base_motor.motor_angle_to_reach = (g_uart.message_received[INDEX_THIRD_BYTE] + (g_uart.message_received[INDEX_FOURTH_BYTE] << 8));
	}
}

/**
 * @brief Receives data from the GUI
 * 
 * @param uart The UART structure containing pertinent information about the UART module used
 */
static void Receive_Data(UART * uart)
{
	HAL_UART_Receive(uart->uart_handle, g_rx_buffer, NUMBER_OF_BYTES_PER_MSG, 1000);
}
