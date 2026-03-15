/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "telemetria_obc.h"
#include "consolidacion.h"
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
osThreadId TareaLecturaOBCHandle;
osThreadId ConsolidacionHandle;
osMessageQId ColaLecturaOBCHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLecturaOBC(void const * argument);
void StartConsolidacion(void const * argument);

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of ColaLecturaOBC */
  osMessageQDef(ColaLecturaOBC, 1, uint32_t);
  ColaLecturaOBCHandle = osMessageCreate(osMessageQ(ColaLecturaOBC), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of TareaLecturaOBC */
  osThreadDef(TareaLecturaOBC, StartLecturaOBC, osPriorityNormal, 0, 256);
  TareaLecturaOBCHandle = osThreadCreate(osThread(TareaLecturaOBC), NULL);

  /* definition and creation of Consolidacion */
  osThreadDef(Consolidacion, StartConsolidacion, osPriorityNormal, 0, 256);
  ConsolidacionHandle = osThreadCreate(osThread(Consolidacion), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartLecturaOBC */
/**
  * @brief  Function implementing the TareaLecturaOBC thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLecturaOBC */
void StartLecturaOBC(void const * argument)
{
  /* USER CODE BEGIN StartLecturaOBC */
  /* Infinite loop */
  //for(;;)
  //{
  //  osDelay(1);
  //
	OBC_IniciarLectura((void*)argument);
  /* USER CODE END StartLecturaOBC */
}

/* USER CODE BEGIN Header_StartConsolidacion */
/**
* @brief Function implementing the Consolidacion thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartConsolidacion */
void StartConsolidacion(void const * argument)
{
  /* USER CODE BEGIN StartConsolidacion */
  /* Infinite loop */
  //for(;;)
  //{
  //  osDelay(1);
  //}
	OBC_IniciarConsolidacion((void*)argument);
  /* USER CODE END StartConsolidacion */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

