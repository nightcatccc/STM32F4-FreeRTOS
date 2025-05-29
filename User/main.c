#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "GPIO.h"
#include "OLED.h"
#include "Serial.h"
#include "Timer.h"
#include "PID.h"
#include "Delay.h"
#include "Serial2.h"
#include "Serial3.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


void SysTick_Handler(void)
{
    extern void xPortSysTickHandler( void );
    /* USER CODE END SysTick_IRQn 0 */
    #if (INCLUDE_xTaskGetSchedulerState == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
    #endif /* INCLUDE_xTaskGetSchedulerState */
        xPortSysTickHandler();
    #if (INCLUDE_xTaskGetSchedulerState == 1 )
    }
    #endif /* INCLUDE_xTaskGetSchedulerState */
}


void freertos_dome(void);
	
//ȎαӅψ¼¶
#define START_TASK_PRIO		1
//Ȏα¶ѕ»´󐡉
#define START_STK_SIZE 		128  
//Ȏα¾䱺
TaskHandle_t StartTask_Handler;
//Ȏαº¯ʽ
void start_task(void);

//ȎαӅψ¼¶
#define TASK1_PRIO		1
//Ȏα¶ѕ»´󐡉
#define STK1_SIZE 		128  
//Ȏα¾䱺
TaskHandle_t Task1_Handler;
//Ȏαº¯ʽ

//ȎαӅψ¼¶
#define TASK2_PRIO		1
//Ȏα¶ѕ»´󐡉
#define STK2_SIZE 		128  
//Ȏα¾䱺
TaskHandle_t Task2_Handler;
//Ȏαº¯ʽ
void task1(void);
void task2(void);
int main (void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	delay_init();
//	LED_Init();
	//uart_init(115200);
	freertos_dome();
}
	
void freertos_dome(void)
{
	
	xTaskCreate(
				(TaskFunction_t) start_task,
				(const char *  ) "start_task",
				(uint16_t) START_STK_SIZE,
				(void*) NULL,
				(UBaseType_t) START_TASK_PRIO,
				(TaskHandle_t*) &StartTask_Handler);
	
	
	
	
	vTaskStartScheduler();			
}
	
void start_task(void)
{
	taskENTER_CRITICAL();
	xTaskCreate(
				(TaskFunction_t) task1,
				(const char *  ) "task1",
				(uint16_t) STK1_SIZE,
				(void*) NULL,
				(UBaseType_t) TASK1_PRIO,
				(TaskHandle_t*) &Task1_Handler
	);
	xTaskCreate(
				(TaskFunction_t) task2,
				(const char *  ) "task2",
				(uint16_t) STK2_SIZE,
				(void*) NULL,
				(UBaseType_t) TASK2_PRIO,
				(TaskHandle_t*) &Task2_Handler
	);
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();
	
}

void task1(void)
{
	while(1){
	
	vTaskDelay(500);
	GPIO_WriteBit(GPIOA ,GPIO_Pin_10,Bit_SET);
	GPIO_WriteBit(GPIOA ,GPIO_Pin_10,Bit_RESET);
	vTaskDelay(500);
	}
}
void task2(void)
{
	while(1){
	
	vTaskDelay(500);
	GPIO_WriteBit(GPIOA ,GPIO_Pin_10,Bit_SET);
	GPIO_WriteBit(GPIOA ,GPIO_Pin_10,Bit_RESET);
	vTaskDelay(500);
	}
}