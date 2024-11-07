/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
<<<<<<< HEAD
#include "../../BSP/Inc/bsp.h"
#include "../../BSP/Inc/uart.h"
=======
#include "motor_control.h"
#include "uart.h"
#include "encoder.h"
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
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
<<<<<<< HEAD
osThreadId defaultTaskHandle;
osThreadId Bsp_TaskHandle;
osThreadId Uart_taskHandle;
=======
osThreadId Sensors_TaskHandle;
osThreadId MotorControl_TaHandle;
osThreadId UART_taskHandle;
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
osSemaphoreId binarySemaphoreHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

<<<<<<< HEAD
void StartDefaultTask(void const * argument);
void StartBsp_Task(void const * argument);
void StartUart_task(void const * argument);
=======
void StartSensorsTask(void const * argument);
void StartMotorControlTask(void const * argument);
void StartUART_task(void const * argument);
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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

  /* Create the semaphores(s) */
  /* definition and creation of binarySemaphore */
  osSemaphoreDef(binarySemaphore);
  binarySemaphoreHandle = osSemaphoreCreate(osSemaphore(binarySemaphore), 1);

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
<<<<<<< HEAD
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Bsp_Task */
  osThreadDef(Bsp_Task, StartBsp_Task, osPriorityNormal, 0, 128);
  Bsp_TaskHandle = osThreadCreate(osThread(Bsp_Task), NULL);

  /* definition and creation of Uart_task */
  osThreadDef(Uart_task, StartUart_task, osPriorityNormal, 0, 128);
  Uart_taskHandle = osThreadCreate(osThread(Uart_task), NULL);
=======
  /* definition and creation of Sensors_Task */
  osThreadDef(Sensors_Task, StartSensorsTask, osPriorityNormal, 0, 128);
  Sensors_TaskHandle = osThreadCreate(osThread(Sensors_Task), NULL);

  /* definition and creation of MotorControl_Ta */
  osThreadDef(MotorControl_Ta, StartMotorControlTask, osPriorityNormal, 0, 128);
  MotorControl_TaHandle = osThreadCreate(osThread(MotorControl_Ta), NULL);

  /* definition and creation of UART_task */
  osThreadDef(UART_task, StartUART_task, osPriorityNormal, 0, 128);
  UART_taskHandle = osThreadCreate(osThread(UART_task), NULL);
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

<<<<<<< HEAD
/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartBsp_Task */
/**
* @brief Function implementing the Bsp_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBsp_Task */
void StartBsp_Task(void const * argument)
{
  /* USER CODE BEGIN StartBsp_Task */
  /* Infinite loop */
  for(;;)
  {
	  BSP_Task();
	  osDelay(100);
  }
  /* USER CODE END StartBsp_Task */
}

/* USER CODE BEGIN Header_StartUart_task */
/**
* @brief Function implementing the Uart_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUart_task */
void StartUart_task(void const * argument)
{
  /* USER CODE BEGIN StartUart_task */
  /* Infinite loop */
  for(;;)
  {
    UART_Task();
	osDelay(50);
  }
  /* USER CODE END StartUart_task */
=======
/* USER CODE BEGIN Header_StartSensorsTask */
/**
  * @brief  Function implementing the Sensors_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartSensorsTask */
void StartSensorsTask(void const * argument)
{
  /* USER CODE BEGIN StartSensorsTask */
  Encoder_Init();

  /* Infinite loop */
  for(;;)
  {
	Encoder_Task();
    osDelay(100);
  }
  /* USER CODE END StartSensorsTask */
}

/* USER CODE BEGIN Header_StartMotorControlTask */
/**
* @brief Function implementing the MotorControl_Ta thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotorControlTask */
void StartMotorControlTask(void const * argument)
{
  /* USER CODE BEGIN StartMotorControlTask */
  /* Encoder_Init() à rajouter */
  MotorControl_Init();

  /* Infinite loop */
  for(;;)
  {
	/* Encoder_Task() à rajouter */
	MotorControl_Task();
    osDelay(100);
  }
  /* USER CODE END StartMotorControlTask */
}

/* USER CODE BEGIN Header_StartUART_task */
/**
* @brief Function implementing the UART_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUART_task */
void StartUART_task(void const * argument)
{
  /* USER CODE BEGIN StartUART_task */
  UART_Init();

  /* Infinite loop */
  for(;;)
  {

	UART_Task();
    osDelay(75);
  }
  /* USER CODE END StartUART_task */
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
