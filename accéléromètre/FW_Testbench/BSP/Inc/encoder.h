/**
 * @file encoder.h
 * @author HEKA
<<<<<<< HEAD
 * @brief Header file for the encoders functions
 *
 * @date 2023-10-05
 * 
 * @copyright Copyright HEKA (c) 2023
 * 
 */

#include "tim.h"
#include "stdbool.h"
#include <float.h>
#include <stdlib.h>

/* Constants */
#define NUM_ENCODERS 3


/* Structs and enums */
// Enum describing the encoder state 
 
typedef enum
{
	ENCODER_STATE_WAITING_FOR_SEMAPHORE 	= -2,
	ENCODER_STATE_OK 						= 0
} Encoder_State;


/**
 * Structure describing an encoder
 */
typedef struct
{
	bool is_encoder_initialized;
	TIM_HandleTypeDef * encoder_timer_handle;
	uint32_t encoder_timer_channel; 
	uint16_t delay;
} Encoder;

/* Function declaration */

void Encoder_Init(void);
Encoder_State Encoder_Task(void);
=======
 * @brief Header file for the encoders management
 *
 * @date 2024-03-28
 * 
 * @copyright Copyright HEKA (c) 2024
 * 
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "tim.h"

/* Constants */
#define DEGREES_PER_TURN 360
#define OVERFLOW 2000
#define DEGREES_PER_COUNTER_INCREMENTS (360.0f / (640.0f * 4))

/* Structs and enums */
typedef struct 
{
	TIM_HandleTypeDef * htim;
	float encoder_position_degrees;
	uint32_t encoder_last_counter_value;
	int32_t encoder_velocity;
	int32_t encoder_position_non_converted;
} Encoder;

/* Function declaration */
void Encoder_Init(void);
void Encoder_Task(void);
void Encoder_Update(Encoder * current_encoder);
void Encoder_Reset(Encoder * current_encoder);

#endif /* __ENCODER_H__ */
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
