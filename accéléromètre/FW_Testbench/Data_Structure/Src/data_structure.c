/**
 * @file data_structure.c
 * @author HEKA
 * @brief Data structure for all sensor values and event information variables
 *
 * @date 2023-11-10
 *
 * @copyright Copyright HEKA (c) 2023
 *
 */

<<<<<<< HEAD
#include "../Inc/data_structure.h"
=======
#include "string.h"
#include "data_structure.h"
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
#include "cmsis_os.h"

/* External variables */
extern osSemaphoreId binarySemaphoreHandle;

/* Data structure address declaration in .c to keep other files from reaching it */
<<<<<<< HEAD
Data * data_struct = (Data *)0x20000000;
=======
Data g_data_struct = {0};
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f

/* Function implementation */
/**
 * @brief Returns data structure address if the semaphore is not taken
 * 
 * @return The data structure address when the semaphore is available, else returns a null pointer
 */
Data * DataStruct_Get(void)
{
<<<<<<< HEAD
	if (osSemaphoreWait(binarySemaphoreHandle, 0) == osOK)
	{
	    return data_struct;
=======
	if (g_data_struct.is_dataset_initialized != true)
	{
		memset(&g_data_struct, 0, sizeof(Data));
		g_data_struct.is_dataset_initialized = true;
	}

	if (osSemaphoreWait(binarySemaphoreHandle, 0) == osOK)
	{
	    return &g_data_struct;
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
	}
	else
	{
		return NULL;
	}
}

<<<<<<< HEAD
/* Function implementation */
=======
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
/**
 * @brief Releases the binary semaphore
 *
 */
void DataStruct_ReleaseSemaphore(void)
{
<<<<<<< HEAD
	/* No verifying of the release status - to be added if necessary */
=======
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
	osSemaphoreRelease(binarySemaphoreHandle);
}
