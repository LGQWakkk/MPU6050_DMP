#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "nmswj.h"

//2023.11.15 @Wakkk

//STM32F103C8T6+MPU6050×ËÌ¬ÏÔÊ¾
//MPU6050½ÓÏß£º VCC->3V3
// 				GND->GND
// 				SCL->PB10
//				SDA->PB11
//USART1
//TX PA9
//RX PA10

int main(void)
{
	float pitch,roll,yaw; 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	uart_init(115200);	 	
	delay_init();	
	LED_Init();		  			
	MPU_Init();				
	while(mpu_dmp_init())
	{
		delay_ms(20);
	}
	while(1)
	{
		delay_ms(2);
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			LED=~LED;
		}
		SEND_OULA_ANGLE((short)(roll*100),(short)(-pitch*100),(short)(-yaw*100));
	} 	
}
 


