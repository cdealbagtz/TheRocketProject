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
#include "System/System.h"
#include "Tasks/MissionManager/MissionManager.h"
#include "Tasks/Actuators/Actuators.h"
#include "Tasks/Memory/Memory.h"
#include "Tasks/Config/Config.h"
#include "Tasks/Initializer/Initializer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
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
/* Definitions for MissionManager */
osThreadId_t MissionManagerHandle;
uint32_t MissionManagerBuffer[ 256 ];
osStaticThreadDef_t MissionManagerControlBlock;
const osThreadAttr_t MissionManager_attributes = {
  .name = "MissionManager",
  .cb_mem = &MissionManagerControlBlock,
  .cb_size = sizeof(MissionManagerControlBlock),
  .stack_mem = &MissionManagerBuffer[0],
  .stack_size = sizeof(MissionManagerBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for ActuatorsTask */
osThreadId_t ActuatorsTaskHandle;
uint32_t ActuatorsTaskBuffer[ 256 ];
osStaticThreadDef_t ActuatorsTaskControlBlock;
const osThreadAttr_t ActuatorsTask_attributes = {
  .name = "ActuatorsTask",
  .cb_mem = &ActuatorsTaskControlBlock,
  .cb_size = sizeof(ActuatorsTaskControlBlock),
  .stack_mem = &ActuatorsTaskBuffer[0],
  .stack_size = sizeof(ActuatorsTaskBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for MemoryTask */
osThreadId_t MemoryTaskHandle;
uint32_t MemoryTaskBuffer[ 256 ];
osStaticThreadDef_t MemoryTaskControlBlock;
const osThreadAttr_t MemoryTask_attributes = {
  .name = "MemoryTask",
  .cb_mem = &MemoryTaskControlBlock,
  .cb_size = sizeof(MemoryTaskControlBlock),
  .stack_mem = &MemoryTaskBuffer[0],
  .stack_size = sizeof(MemoryTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for InitializerTask */
osThreadId_t InitializerTaskHandle;
uint32_t InitializerTaskBuffer[ 256 ];
osStaticThreadDef_t InitializerTaskControlBlock;
const osThreadAttr_t InitializerTask_attributes = {
  .name = "InitializerTask",
  .cb_mem = &InitializerTaskControlBlock,
  .cb_size = sizeof(InitializerTaskControlBlock),
  .stack_mem = &InitializerTaskBuffer[0],
  .stack_size = sizeof(InitializerTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CommandInterfac */
osThreadId_t CommandInterfacHandle;
uint32_t CommandInterfacBuffer[ 256 ];
osStaticThreadDef_t CommandInterfacControlBlock;
const osThreadAttr_t CommandInterfac_attributes = {
  .name = "CommandInterfac",
  .cb_mem = &CommandInterfacControlBlock,
  .cb_size = sizeof(CommandInterfacControlBlock),
  .stack_mem = &CommandInterfacBuffer[0],
  .stack_size = sizeof(CommandInterfacBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ConfigTask */
osThreadId_t ConfigTaskHandle;
uint32_t ConfigTaskBuffer[ 512 ];
osStaticThreadDef_t ConfigTaskControlBlock;
const osThreadAttr_t ConfigTask_attributes = {
  .name = "ConfigTask",
  .cb_mem = &ConfigTaskControlBlock,
  .cb_size = sizeof(ConfigTaskControlBlock),
  .stack_mem = &ConfigTaskBuffer[0],
  .stack_size = sizeof(ConfigTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for INSTask */
osThreadId_t INSTaskHandle;
uint32_t INSTaskBuffer[ 256 ];
osStaticThreadDef_t INSTaskControlBlock;
const osThreadAttr_t INSTask_attributes = {
  .name = "INSTask",
  .cb_mem = &INSTaskControlBlock,
  .cb_size = sizeof(INSTaskControlBlock),
  .stack_mem = &INSTaskBuffer[0],
  .stack_size = sizeof(INSTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for BlackboxTask */
osThreadId_t BlackboxTaskHandle;
uint32_t BlackboxTaskBuffer[ 256 ];
osStaticThreadDef_t BlackboxTaskControlBlock;
const osThreadAttr_t BlackboxTask_attributes = {
  .name = "BlackboxTask",
  .cb_mem = &BlackboxTaskControlBlock,
  .cb_size = sizeof(BlackboxTaskControlBlock),
  .stack_mem = &BlackboxTaskBuffer[0],
  .stack_size = sizeof(BlackboxTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for FaultTask */
osThreadId_t FaultTaskHandle;
uint32_t FaultTaskBuffer[ 256 ];
osStaticThreadDef_t FaultTaskControlBlock;
const osThreadAttr_t FaultTask_attributes = {
  .name = "FaultTask",
  .cb_mem = &FaultTaskControlBlock,
  .cb_size = sizeof(FaultTaskControlBlock),
  .stack_mem = &FaultTaskBuffer[0],
  .stack_size = sizeof(FaultTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for System_Queue */
osMessageQueueId_t System_QueueHandle;
const osMessageQueueAttr_t System_Queue_attributes = {
  .name = "System_Queue"
};
/* Definitions for Actuator_Queue */
osMessageQueueId_t Actuator_QueueHandle;
const osMessageQueueAttr_t Actuator_Queue_attributes = {
  .name = "Actuator_Queue"
};
/* Definitions for Memory_writeQueue */
osMessageQueueId_t Memory_writeQueueHandle;
const osMessageQueueAttr_t Memory_writeQueue_attributes = {
  .name = "Memory_writeQueue"
};
/* Definitions for Memory_readQueue */
osMessageQueueId_t Memory_readQueueHandle;
const osMessageQueueAttr_t Memory_readQueue_attributes = {
  .name = "Memory_readQueue"
};
/* Definitions for Memory_requestQueue */
osMessageQueueId_t Memory_requestQueueHandle;
const osMessageQueueAttr_t Memory_requestQueue_attributes = {
  .name = "Memory_requestQueue"
};
/* Definitions for Config_Request */
osMessageQueueId_t Config_RequestHandle;
const osMessageQueueAttr_t Config_Request_attributes = {
  .name = "Config_Request"
};
/* Definitions for DeployParachuteTimer */
osTimerId_t DeployParachuteTimerHandle;
const osTimerAttr_t DeployParachuteTimer_attributes = {
  .name = "DeployParachuteTimer"
};
/* Definitions for ParachuteDeploymentPulse */
osTimerId_t ParachuteDeploymentPulseHandle;
const osTimerAttr_t ParachuteDeploymentPulse_attributes = {
  .name = "ParachuteDeploymentPulse"
};
/* Definitions for MemoryMutex */
osMutexId_t MemoryMutexHandle;
const osMutexAttr_t MemoryMutex_attributes = {
  .name = "MemoryMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartMissionManager(void *argument);
void StartActuatorsTask(void *argument);
void StartMemoryTask(void *argument);
void StartInitializerTask(void *argument);
void StartCommandInterfaceTask(void *argument);
void StartConfigTask(void *argument);
void StartINSTask(void *argument);
void StartBlackboxTask(void *argument);
void StartFaultTask(void *argument);
void DeployParachuteFunction(void *argument);
void DisableDeplymentOutputs(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of MemoryMutex */
  MemoryMutexHandle = osMutexNew(&MemoryMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of DeployParachuteTimer */
  DeployParachuteTimerHandle = osTimerNew(DeployParachuteFunction, osTimerOnce, NULL, &DeployParachuteTimer_attributes);

  /* creation of ParachuteDeploymentPulse */
  ParachuteDeploymentPulseHandle = osTimerNew(DisableDeplymentOutputs, osTimerOnce, NULL, &ParachuteDeploymentPulse_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of System_Queue */
  System_QueueHandle = osMessageQueueNew (16, sizeof(System_Notification_t), &System_Queue_attributes);

  /* creation of Actuator_Queue */
  Actuator_QueueHandle = osMessageQueueNew (8, sizeof(Actuator_Request_t), &Actuator_Queue_attributes);

  /* creation of Memory_writeQueue */
  Memory_writeQueueHandle = osMessageQueueNew (6, sizeof(Memory_Write_t), &Memory_writeQueue_attributes);

  /* creation of Memory_readQueue */
  Memory_readQueueHandle = osMessageQueueNew (6, sizeof(Memory_Read_t), &Memory_readQueue_attributes);

  /* creation of Memory_requestQueue */
  Memory_requestQueueHandle = osMessageQueueNew (6, sizeof(Memory_ReadRequest_t), &Memory_requestQueue_attributes);

  /* creation of Config_Request */
  Config_RequestHandle = osMessageQueueNew (4, sizeof(uint8_t), &Config_Request_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MissionManager */
  MissionManagerHandle = osThreadNew(StartMissionManager, NULL, &MissionManager_attributes);

  /* creation of ActuatorsTask */
  ActuatorsTaskHandle = osThreadNew(StartActuatorsTask, NULL, &ActuatorsTask_attributes);

  /* creation of MemoryTask */
  MemoryTaskHandle = osThreadNew(StartMemoryTask, NULL, &MemoryTask_attributes);

  /* creation of InitializerTask */
  InitializerTaskHandle = osThreadNew(StartInitializerTask, NULL, &InitializerTask_attributes);

  /* creation of CommandInterfac */
  CommandInterfacHandle = osThreadNew(StartCommandInterfaceTask, NULL, &CommandInterfac_attributes);

  /* creation of ConfigTask */
  ConfigTaskHandle = osThreadNew(StartConfigTask, NULL, &ConfigTask_attributes);

  /* creation of INSTask */
  INSTaskHandle = osThreadNew(StartINSTask, NULL, &INSTask_attributes);

  /* creation of BlackboxTask */
  BlackboxTaskHandle = osThreadNew(StartBlackboxTask, NULL, &BlackboxTask_attributes);

  /* creation of FaultTask */
  FaultTaskHandle = osThreadNew(StartFaultTask, NULL, &FaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartMissionManager */
/**
  * @brief  Function implementing the MissionManager thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartMissionManager */
void StartMissionManager(void *argument)
{
  /* USER CODE BEGIN StartMissionManager */
  /* Infinite loop */
  for(;;)
  {

	MissionManager_Task();
    osDelay(20);
  }
  /* USER CODE END StartMissionManager */
}

/* USER CODE BEGIN Header_StartActuatorsTask */
/**
* @brief Function implementing the ActuatorsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartActuatorsTask */
void StartActuatorsTask(void *argument)
{
  /* USER CODE BEGIN StartActuatorsTask */
  /* Infinite loop */
  for(;;)
  {
	Actuators_Task();
    osDelay(5);
  }
  /* USER CODE END StartActuatorsTask */
}

/* USER CODE BEGIN Header_StartMemoryTask */
/**
* @brief Function implementing the MemoryTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMemoryTask */
void StartMemoryTask(void *argument)
{
  /* USER CODE BEGIN StartMemoryTask */
  /* Infinite loop */
  for(;;)
  {
	Memory_Task();
    osDelay(5);
  }
  /* USER CODE END StartMemoryTask */
}

/* USER CODE BEGIN Header_StartInitializerTask */
/**
* @brief Function implementing the InitializerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInitializerTask */
void StartInitializerTask(void *argument)
{
  /* USER CODE BEGIN StartInitializerTask */
  /* Infinite loop */
  for(;;)
  {
	Initializer_Task();
    osDelay(100);
  }
  /* USER CODE END StartInitializerTask */
}

/* USER CODE BEGIN Header_StartCommandInterfaceTask */
/**
* @brief Function implementing the CommandInterfac thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCommandInterfaceTask */
void StartCommandInterfaceTask(void *argument)
{
  /* USER CODE BEGIN StartCommandInterfaceTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(200);
  }
  /* USER CODE END StartCommandInterfaceTask */
}

/* USER CODE BEGIN Header_StartConfigTask */
/**
* @brief Function implementing the ConfigTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartConfigTask */
void StartConfigTask(void *argument)
{
  /* USER CODE BEGIN StartConfigTask */
  /* Infinite loop */
  for(;;)
  {
	Config_Task();
    osDelay(200);
  }
  /* USER CODE END StartConfigTask */
}

/* USER CODE BEGIN Header_StartINSTask */
/**
* @brief Function implementing the INSTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartINSTask */
void StartINSTask(void *argument)
{
  /* USER CODE BEGIN StartINSTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartINSTask */
}

/* USER CODE BEGIN Header_StartBlackboxTask */
/**
* @brief Function implementing the BlackboxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlackboxTask */
void StartBlackboxTask(void *argument)
{
  /* USER CODE BEGIN StartBlackboxTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartBlackboxTask */
}

/* USER CODE BEGIN Header_StartFaultTask */
/**
* @brief Function implementing the FaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFaultTask */
void StartFaultTask(void *argument)
{
  /* USER CODE BEGIN StartFaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartFaultTask */
}

/* DeployParachuteFunction function */
void DeployParachuteFunction(void *argument)
{
  /* USER CODE BEGIN DeployParachuteFunction */

  /* USER CODE END DeployParachuteFunction */
}

/* DisableDeplymentOutputs function */
void DisableDeplymentOutputs(void *argument)
{
  /* USER CODE BEGIN DisableDeplymentOutputs */

  /* USER CODE END DisableDeplymentOutputs */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

