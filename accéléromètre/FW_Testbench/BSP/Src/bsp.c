/**
 * @file bsp.c
 * @author HEKA
 * @brief Board support package for all hardware-level modules
 *
 * @date 2023-10-05
 * 
 * @copyright Copyright HEKA (c) 2023
 * 
 */

#include "../Inc/bsp.h"
#include "../Inc/motor_control.h"

/**
 * @brief Initialization of the board support package
 * 
 */
void BSP_Init(void)
{
    MotorControl_Init();
<<<<<<< HEAD
    Encoder_Init();
    Gyroscope_Init();
=======
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
}

/**
 * @brief Board support package task repartition
 * 
 */
void BSP_Task(void)
{
	MotorControl_Task();
<<<<<<< HEAD
    Encoder_Task();
    Gyroscope_Task();
=======
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
}
