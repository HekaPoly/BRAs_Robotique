/*
 ******************************************************************************
 * @file    read_data_polling.c
 * @author  Sensors Software Solution Team
 * @brief   This file show how to get data from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/*
 * This example was developed using the following STMicroelectronics
 * evaluation boards:
 *
 * - STEVAL_MKI109V3 + STEVAL-MKI194V1
 * - NUCLEO_F401RE + X_STEVAL-MKI194V1
 * - DISCOVERY_SPC584B + STEVAL-MKI194V1
 *
 * Used interfaces:
 *
 * STEVAL_MKI109V3    - Host side:   USB (Virtual COM)
 *                    - Sensor side: SPI(Default) / I2C(supported)
 *
 * NUCLEO_STM32F411RE - Host side: UART(COM) to USB bridge
 *                    - I2C(Default) / SPI(supported)
 *
 * DISCOVERY_SPC584B  - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I2C(Default) / SPI(supported)
 *
 * If you need to run this example on a different hardware platform a
 * modification of the functions: `platform_write`, `platform_read`,
 * `tx_com` and 'platform_init' is required.
 *
 */

/* STMicroelectronics evaluation boards definition
 *
 * Please uncomment ONLY the evaluation boards in use.
 * If a different hardware is used please comment all
 * following target board and redefine yours.
 */

//#define STEVAL_MKI109V3  /* little endian */
#define NUCLEO_F401RE    /* little endian */
//#define SPC584B_DIS      /* big endian */

/* ATTENTION: By default the driver is little endian. If you need switch
 *            to big endian please see "Endianness definitions" in the
 *            header file of the driver (_reg.h).
 */

#if defined(STEVAL_MKI109V3)
/* MKI109V3: Define communication interface */
#define SENSOR_BUS hspi2
/* MKI109V3: Vdd and Vddio power supply values */
#define PWM_3V3 915

#elif defined(NUCLEO_F401RE)
/* NUCLEO_F401RE: Define communication interface */
//#define SENSOR_BUS hi2c1

#elif defined(SPC584B_DIS)
/* DISCOVERY_SPC584B: Define communication interface */
#define SENSOR_BUS I2CD1

#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "lsm6dsr.h"
#include "lsm6dsr_read_data.h"
#include "tim.h"

#if defined(NUCLEO_F401RE)
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "i2c.h"
#include "tim.h"
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;

#elif defined(STEVAL_MKI109V3)
#include "stm32f4xx_hal.h"
#include "usbd_cdc_if.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"
#include "stm32f4xx_ll_tim.h"

#elif defined(SPC584B_DIS)
#include "components.h"
#endif

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            10 //ms
#define    PI                   3.141592653589793

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static int16_t data_raw_temperature;

 float ax =0 ,ay = 0,az = 0,axy = 0, ayz = 0, axz = 0;
 float a_limite = 10.0;
 volatile uint32_t dt = 0;
 float vx = 0, vy = 0, vz = 0;
 float acceleration_mg[3];
 float angular_rate_mdps[3];
 float temperature_degC;
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];
/*Définition des variables pour la moyenne mobile de la température-----------*/
#define WINDOW_SIZE 5 // Taille de la fenêtre pour la moyenne mobile

float temperature_window[WINDOW_SIZE] = {0}; // Tableau pour stocker les dernières températures
int window_index = 0; // Indice courant dans le tableau
int valid_readings = 0; // Compteur de lectures valides




/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void tx_com( uint8_t *tx_buffer, uint16_t len );
static void platform_delay(uint32_t ms);
static void platform_init(void);

/* Main Example --------------------------------------------------------------*/

void lsm6dsr_read_data_polling(void)
{
  stmdev_ctx_t dev_ctx;
  uint8_t reg;
  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;
  /* Init test platform */
  platform_init();

  /* Wait sensor boot time */
  platform_delay(BOOT_TIME);
  /* Check device ID */
  lsm6dsr_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSR_ID)
    while(1);

  /* Restore default configuration */
  lsm6dsr_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lsm6dsr_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Disable I3C interface */
  lsm6dsr_i3c_disable_set(&dev_ctx, LSM6DSR_I3C_DISABLE);
  /* Enable Block Data Update */
  lsm6dsr_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Output Data Rate */
  lsm6dsr_xl_data_rate_set(&dev_ctx, LSM6DSR_XL_ODR_6667Hz);
  lsm6dsr_gy_data_rate_set(&dev_ctx, LSM6DSR_GY_ODR_6667Hz);
  /* Set full scale */
  lsm6dsr_xl_full_scale_set(&dev_ctx, LSM6DSR_2g);
  lsm6dsr_gy_full_scale_set(&dev_ctx, LSM6DSR_125dps);
  /* Configure filtering chain(No aux interface)
   * Accelerometer - LPF1 + LPF2 path
   */
  lsm6dsr_xl_hp_path_on_out_set(&dev_ctx, LSM6DSR_LP_ODR_DIV_100);
  lsm6dsr_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsr_gy_hp_path_internal_set(&dev_ctx,LSM6DSR_HP_FILTER_1Hz04);
  lsm6dsr_gy_filter_lp1_set(&dev_ctx,PROPERTY_ENABLE);
  /* Read samples in polling mode */
  while (1) {

    /* Read output only if new xl value is available */
    lsm6dsr_xl_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
    	HAL_TIM_Base_Start_IT(&htim1);
      /* Read acceleration field data */
    	memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
      lsm6dsr_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
     //acceleration selon l'axe x du IMU
        acceleration_mg[0] =
      lsm6dsr_from_fs2g_to_mg(data_raw_acceleration[0]);
      //selon l'axe y du IMU
      acceleration_mg[1] =
        lsm6dsr_from_fs2g_to_mg(data_raw_acceleration[1]);
      // selon l'axe z du IMU
      acceleration_mg[2] =
        lsm6dsr_from_fs2g_to_mg(data_raw_acceleration[2]);

      //Définition des composantes du vecteur accélération//
      /*selon les axes principales du IMU*/



      ax = acceleration_mg[0]*0.00981; // Accélération en X (m/s²)
      ay = acceleration_mg[1]*0.00981; // Accélération en Y
      az = acceleration_mg[2]*0.00981; // Accélération en Z

      axy = sqrt(pow(ax, 2) + pow(ay, 2));
      ayz =sqrt(pow(ay, 2) + pow(az, 2));
      axz=sqrt(pow(ax, 2) + pow(az, 2));



      if (axy > a_limite||axz > a_limite||ayz > a_limite||fabs(ax)>a_limite||fabs(ay)>a_limite||fabs(az)>a_limite){
          sprintf((char *)tx_buffer,
                  "Attention!\r\n");
          tx_com(tx_buffer, strlen((char const *)tx_buffer));
          sprintf((char *)tx_buffer,
                  "\r\n");
      }

      else{

          };
	  // Update the timer interrupt function for velocity and position calculations
	  sprintf((char *)tx_buffer,
			  "Acceleration [m/s^2]: ax:%4.2f\tay:%4.2f\taz:%4.2f\r\n",
			  ax,ay,az);
	  tx_com(tx_buffer, strlen((char const *)tx_buffer));
	  sprintf((char *)tx_buffer,
			  "\r\n");
	  HAL_Delay(1000);

    }

    lsm6dsr_gy_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
      /* Read angular rate field data */
     /*memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
      lsm6dsr_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
      angular_rate_mdps[0] =
        lsm6dsr_from_fs125dps_to_mdps(data_raw_angular_rate[0]);
      angular_rate_mdps[1] =
        lsm6dsr_from_fs125dps_to_mdps(data_raw_angular_rate[1]);
      angular_rate_mdps[2] =
        lsm6dsr_from_fs125dps_to_mdps(data_raw_angular_rate[2]);

      vx = angular_rate_mdps[0]/1000;
      vy = angular_rate_mdps[1]/1000;
      vz = angular_rate_mdps[2]/1000;
      sprintf((char *)tx_buffer,
              "Angular rate [dps]: v_x:%4.2f\tv_y:%4.2f\tv_z:%4.2f\r\n",
			  vx,vy,vz);

      tx_com(tx_buffer, strlen((char const *)tx_buffer));
      sprintf((char *)tx_buffer,
              "\r\n");
      HAL_Delay(1000);*/
    }

		///Mesure de temp
	  lsm6dsr_temp_flag_data_ready_get(&dev_ctx, &reg);


	if (reg) {
		/* Initialiser les données de température */
		memset(&data_raw_temperature, 0x00, sizeof(int16_t));

		/* Lire les données de température brute */
		if (lsm6dsr_temperature_raw_get(&dev_ctx, &data_raw_temperature) == 0) {
			/* Convertir en Celsius */
			float temperature_degC = lsm6dsr_from_lsb_to_celsius(data_raw_temperature);

			/* Stocker la température dans le tableau pour la moyenne mobile */
			temperature_window[window_index] = temperature_degC;
			window_index = (window_index + 1) % WINDOW_SIZE; // Mettre à jour l'indice

			// Si moins de WINDOW_SIZE lectures, incrémenter le compteur
			if (valid_readings < WINDOW_SIZE) {
				valid_readings++;
			}

			/* Calculer la moyenne mobile */
			float average_temperature = 0;
			for (int i = 0; i < valid_readings; i++) {
				average_temperature += temperature_window[i];
			}
			average_temperature /= valid_readings;

			/* Formater et transmettre la température moyenne */
			snprintf((char *)tx_buffer, sizeof(tx_buffer), "Temperature [degC]: %6.2f\r\n", average_temperature);
			tx_com(tx_buffer, strlen((char const *)tx_buffer));

			// Optionnel : transmettre une nouvelle ligne
			snprintf((char *)tx_buffer, sizeof(tx_buffer), "\r\n");
			tx_com(tx_buffer, strlen((char const *)tx_buffer));
		} else {
			// Gérer le cas d'erreur
		}

		/* Délai avant la prochaine lecture */
		HAL_Delay(1000);

		}
}
}



/*void USART_SendString(char *str) {
    while (*str) {
        HAL_UART_Transmit(&huart2, (uint8_t *)str++, 1, HAL_MAX_DELAY);
    }
}

*/
/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
#if defined(NUCLEO_F401RE)
  HAL_I2C_Mem_Write(handle, LSM6DSR_I2C_ADD_L, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
#elif defined(STEVAL_MKI109V3)
  HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Transmit(handle, (uint8_t*) bufp, len, 1000);
  HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_SET);
#elif defined(SPC584B_DIS)
  i2c_lld_write(handle,  LSM6DSR_I2C_ADD_L & 0xFE, reg, (uint8_t*) bufp, len);
#endif
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
#if defined(NUCLEO_F401RE)
  HAL_I2C_Mem_Read(handle, LSM6DSR_I2C_ADD_L, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
#elif defined(STEVAL_MKI109V3)
  reg |= 0x80;
  HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Receive(handle, bufp, len, 1000);
  HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_SET);
#elif defined(SPC584B_DIS)
  i2c_lld_read(handle, LSM6DSR_I2C_ADD_L & 0xFE, reg, bufp, len);
#endif
  return 0;
}

/*
 * @brief  Send buffer to console (platform dependent)
 *
 * @param  tx_buffer     buffer to transmit
 * @param  len           number of byte to send
 *
 */
static void tx_com(uint8_t *tx_buffer, uint16_t len)
{
#if defined(NUCLEO_F401RE)
  HAL_UART_Transmit(&huart2, tx_buffer, len, 1000);
#elif defined(STEVAL_MKI109V3)
  CDC_Transmit_FS(tx_buffer, len);
#elif defined(SPC584B_DIS)
  sd_lld_write(&SD2, tx_buffer, len);
#endif
}

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */
static void platform_delay(uint32_t ms)
{
#if defined(NUCLEO_F401RE) | defined(STEVAL_MKI109V3)
  HAL_Delay(ms);
#elif defined(SPC584B_DIS)
  osalThreadDelayMilliseconds(ms);
#endif
}

/*
 * @brief  platform specific initialization (platform dependent)
 */
static void platform_init(void)
{
#if defined(STEVAL_MKI109V3)
  TIM3->CCR1 = PWM_3V3;
  TIM3->CCR2 = PWM_3V3;
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_Delay(1000);
#endif
}
