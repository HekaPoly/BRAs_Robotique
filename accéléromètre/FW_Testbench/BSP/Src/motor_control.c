/**
 * @file motor_control.c
 * @author HEKA
 * @brief Manual motor control implementation
 *
 * @date 2023-10-05
 * 
 * @copyright Copyright HEKA (c) 2023
 * 
 */

<<<<<<< HEAD
#include "../Inc/motor_control.h"
#include "main.h"
#include "../../Data_Structure/Inc/data_structure.h"

/* Constants */
#define FACTOR_SECONDS_TO_MS 1000

/* Private functions declaration */
static void Modify_Speed(void);
static void Modify_Direction(int16_t difference);

/* Global variables */
Motor g_base_motor =
{
	.is_motor_initialized = false,
};

/* Function implementation */
=======
#include "motor_control.h"
#include "main.h"
#include "data_structure.h"

/* Constants */
#define FACTOR_SECONDS_TO_MS 1000
#define NUMBER_MOTOR 6


/* Private functions declaration */
static void Modify_Speed(int16_t difference_deg, uint32_t motor_speed_desired, Motor* currentMotor);
static void Modify_Direction(int16_t difference_deg, Motor* currentMotor);

/* Global variables */
Motor Motors[NUMBER_MOTOR]; //Array of all the motors

/* Function implementation */

>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
/**
 * @brief Initialization function for all stepper motors
 * 
 */
void MotorControl_Init(void)
{
<<<<<<< HEAD
    /* Initialize all stepper motors (PWM, Direction GPIO and Enable GPIO) */
	g_base_motor.motor_direction = MOTOR_DIRECTION_CLOCKWISE;
	g_base_motor.motor_timer_handle = &htim2;
	g_base_motor.motor_timer_channel = TIM_CHANNEL_1;

	g_base_motor.motor_angle_to_reach = 0u;
	g_base_motor.deg_per_turn = DEGREES_PER_PULSE_WITH_GEARBOX;
	g_base_motor.current_motor_angle = 0u;
	g_base_motor.nb_pulse = 0u;
	g_base_motor.delay = 0u;
=======
    // Initializes all stepper motors (PWM, Direction GPIO and Enable GPIO)
	for(int i=0;i<NUMBER_MOTOR;i++){
		Motors[i].motor_direction = MOTOR_DIRECTION_CLOCKWISE;
		Motors[i].deg_per_turn = DEGREES_PER_PULSE_WITH_GEARBOX;
		Motors[i].nb_pulse = 0u;
		Motors[i].delay = 0u;
		Motors[i].is_motor_initialized = true;
	}
	// Initialize the timer and the channels for each motor
	// change timing handle if necessary
	Motors[0].motor_timer_handle = &htim2;
	Motors[0].motor_timer_channel = TIM_CHANNEL_1; 		
	Motor_gpio_section direction0 = {DIR_MOTOR_1_GPIO_Port, DIR_MOTOR_1_Pin};
	Motors[0].direction_port = direction0;   

	Motors[1].motor_timer_handle = &htim2;
	Motors[1].motor_timer_channel = TIM_CHANNEL_3;
	Motor_gpio_section direction1 = {DIR_MOTOR_2_GPIO_Port, DIR_MOTOR_2_Pin};
	Motors[1].direction_port = direction1;
	
	Motors[2].motor_timer_handle = &htim4;
	Motors[2].motor_timer_channel = TIM_CHANNEL_4;
	Motor_gpio_section direction2 = {DIR_MOTOR_3_GPIO_Port, DIR_MOTOR_3_Pin};
	Motors[2].direction_port = direction2;

	Motors[3].motor_timer_handle = &htim4;
	Motors[3].motor_timer_channel = TIM_CHANNEL_3;
	Motor_gpio_section direction3 = {DIR_MOTOR_4_GPIO_Port, DIR_MOTOR_4_Pin};
	Motors[3].direction_port = direction3;
	
	Motors[4].motor_timer_handle = &htim4;
	Motors[4].motor_timer_channel = TIM_CHANNEL_2;
	Motor_gpio_section direction4 = {DIR_MOTOR_5_GPIO_Port, DIR_MOTOR_5_Pin};
	Motors[4].direction_port = direction4;
	
	Motors[5].motor_timer_handle = &htim5;
	Motors[5].motor_timer_channel = TIM_CHANNEL_1;
	Motor_gpio_section direction5 = {DIR_MOTOR_6_GPIO_Port, DIR_MOTOR_6_Pin};
	Motors[5].direction_port = direction5;
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
}

/**
 * @brief Task to control the stepper motors in manual mode
<<<<<<< HEAD
 * 
=======
 * @return The state of the motors.
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
 */
Motor_State MotorControl_Task(void)
{
	Data * data_structure = DataStruct_Get();
	if (data_structure == NULL)
	{
		return MOTOR_STATE_WAITING_FOR_SEMAPHORE;
	}
<<<<<<< HEAD

	/* Test pour valider l'écriture et la lecture de la structure de données */
	data_structure->gyro_value = 3000;
	uint32_t speed_value = data_structure->motor_speed;

	int16_t difference = g_base_motor.motor_angle_to_reach - g_base_motor.current_motor_angle;
	if (difference != 0)
	{
		Modify_Direction(difference);
		Modify_Speed();
=======
	
	// Data of the Motor we are currently changing
	Data_Motor * currentData;
	Motor * currentMotor;

	for(int i=0;i<NUMBER_MOTOR;i++)
	{ // loops each motor
		// call encoder
		// call PID
		
		currentData = &data_structure->Data_Motors[i];
		currentMotor = &Motors[i];

		int16_t difference_deg = currentData->motor_angle_to_reach_deg - currentData->motor_current_angle_deg;

		if (difference_deg != 0)
		{
			Modify_Direction(difference_deg, currentMotor);
			Modify_Speed(difference_deg, currentData->motor_desired_speed_percent, currentMotor);

			currentData->motor_current_angle_deg = currentData->motor_angle_to_reach_deg;
		}
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
	}

	DataStruct_ReleaseSemaphore();

	return MOTOR_STATE_OK;
}

/**
<<<<<<< HEAD
 * @brief Calculation of new ARR value to give the PWM in order to modifiy the motor's speed
 *
 */
void Modify_Speed(void)
{
	uint16_t new_freq = (g_base_motor.motor_speed_percent * FREQ_MAX_HZ) / 100;
	uint16_t new_arr = (FREQ_CLK_HZ / ((PSC + 1)* new_freq)) - 1;

	g_base_motor.motor_timer_handle->Instance->ARR = new_arr;
	g_base_motor.motor_timer_handle->Instance->CCR1 = g_base_motor.motor_timer_handle->Instance->ARR / 2;

	g_base_motor.nb_pulse = (abs(g_base_motor.motor_angle_to_reach - g_base_motor.current_motor_angle)) / g_base_motor.deg_per_turn ;
	g_base_motor.delay = ((float)g_base_motor.nb_pulse / (float)new_freq) * FACTOR_SECONDS_TO_MS;

	HAL_TIM_PWM_Start(g_base_motor.motor_timer_handle, g_base_motor.motor_timer_channel);
	HAL_Delay(g_base_motor.delay);
	HAL_TIM_PWM_Stop(g_base_motor.motor_timer_handle, g_base_motor.motor_timer_channel);

	g_base_motor.current_motor_angle = g_base_motor.motor_angle_to_reach;
}

/**
 * @brief Modifies the direction signal controlling the turning direction of the motor
 *
 * @param[in] difference	The difference between the angle to reach and the current motor's angle
 *
 */
void Modify_Direction(int16_t difference)
{
	if (difference < 0)
	{
		g_base_motor.motor_direction = MOTOR_DIRECTION_COUNTERCLOCKWISE;
	}

	else if (difference > 0)
	{
		g_base_motor.motor_direction = MOTOR_DIRECTION_CLOCKWISE;
	}
	else
	{
		/* Do nothing here */
	}

	if (g_base_motor.motor_direction == MOTOR_DIRECTION_CLOCKWISE)
	{
		HAL_GPIO_WritePin(DIR_Motor_1_GPIO_Port, DIR_Motor_1_Pin, GPIO_PIN_SET);
	}
    else if (g_base_motor.motor_direction == MOTOR_DIRECTION_COUNTERCLOCKWISE)
	{
    	HAL_GPIO_WritePin(DIR_Motor_1_GPIO_Port, DIR_Motor_1_Pin, GPIO_PIN_RESET);
=======
 * @brief Modifies the speed of a motor based on the desired speed percentage and the difference in degrees.
 *
 * This function calculates the new frequency and new auto-reload value (ARR) for the motor timer based on the desired speed percentage.
 * It then updates the ARR and CCR1 registers of the motor timer to control the motor speed.
 * The number of pulses and delay are calculated based on the difference in degrees and the new frequency.
 * The LED is toggled on and off to indicate the motor operation.
 *
 * @param[in] difference_deg	The difference between the angle to reach and the current motor's angle
 * @param[in] motor_speed_desired_percent	The desired motor speed percentage used to calculate the motor speed
 * @param[in] currentMotor	The current motor's speed we are changing
 */
static void Modify_Speed(int16_t difference_deg, uint32_t motor_speed_desired_percent, Motor* currentMotor)
{
	uint16_t new_freq = (motor_speed_desired_percent * FREQ_MAX_HZ) / 100;
	uint16_t new_arr = (FREQ_CLK_HZ / ((PSC + 1)* new_freq)) - 1;

	currentMotor->motor_timer_handle->Instance->ARR = new_arr;
	currentMotor->motor_timer_handle->Instance->CCR1 = currentMotor->motor_timer_handle->Instance->ARR / 2;

	currentMotor->nb_pulse = abs(difference_deg) / currentMotor->deg_per_turn;
	currentMotor->delay = ((float)currentMotor->nb_pulse / (float)new_freq) * FACTOR_SECONDS_TO_MS;

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // Turn on LED

	HAL_TIM_PWM_Start(currentMotor->motor_timer_handle, currentMotor->motor_timer_channel);
	HAL_Delay(currentMotor->delay);
	HAL_TIM_PWM_Stop(currentMotor->motor_timer_handle, currentMotor->motor_timer_channel);

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // Turn off LED
}

/**
 * @brief Modifies the direction signal of a motor based on the given difference in degrees.
 *
 * This function updates the direction of the motor based on the difference in degrees.
 * If the difference is negative, the motor direction is set to counter-clockwise.
 * If the difference is positive, the motor direction is set to clockwise.
 * The direction is then set on the motor driver using the appropriate GPIO pin.
 *
 * @param[in] difference_deg The difference in degrees to determine the motor direction.
 * @param[in] currentMotor Pointer to the Motor structure representing the motor.
 */
static void Modify_Direction(int16_t difference_deg , Motor* currentMotor)
{
	//switch direction if needed
	if (difference_deg < 0)
	{
		currentMotor->motor_direction = MOTOR_DIRECTION_COUNTERCLOCKWISE;
	}
	else if (difference_deg > 0)
	{
		currentMotor->motor_direction = MOTOR_DIRECTION_CLOCKWISE;
	}

	//set the direction on the driver
	if (currentMotor->motor_direction == MOTOR_DIRECTION_CLOCKWISE)
	{
		HAL_GPIO_WritePin(currentMotor->direction_port.section, currentMotor->direction_port.pin_num, GPIO_PIN_SET);  // check validity of the pin and motor pin number member
	}
	else if (currentMotor->motor_direction == MOTOR_DIRECTION_COUNTERCLOCKWISE)
	{
		HAL_GPIO_WritePin(currentMotor->direction_port.section, currentMotor->direction_port.pin_num, GPIO_PIN_RESET); // check validity of the pin and motor pin number member
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
	}
}
