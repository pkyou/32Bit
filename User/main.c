/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "config.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
uint16_t data=0;
unsigned char RS485_tx_buffer[200] = {0,0,0,0,0,0,0,0};
/* Private function prototypes -----------------------------------------------*/
void  Delay(uint32_t nCount);


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  OpenDio();
	//GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_4);
	
//	GPIO_SetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12);
//	GPIO_SetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12);
 // USART_Configuration();

	
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
  Usart2_Init();
	USART_NVIC_Config();
	
	Delay(100);
	GPIO_SetBits(GPIOA,GPIO_Pin_8); 

	GPIO_SetBits(GPIOA,GPIO_Pin_15); 	
	Delay(3000);
  USART_SendData(USART2,0x44);
//	printf("FFFSDFSDFSDFSD");
	Delay(100);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); 
	GPIO_ResetBits(GPIOA,GPIO_Pin_15); 
//	printf("***************************************************\r\n");
	/* Infinite loop */
	while (1)
	{
	
	}
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
