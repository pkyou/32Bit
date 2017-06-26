#include "usart.h"
#include "config.h"

extern uint16_t data;
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*设置是否使用硬件流控制*/
//#define HwFlowControl
/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure Open_USARTx 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
	
	
	//TX PA2  RX  PA3
	void Usart2_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure; 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		
		//TX PA2
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	//RX PA3
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		
		
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置 USART Rx 为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
	
	
	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
  /* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
     Open_USARTx transmit data register is empty */
		 
  //USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */

  USART_Cmd(USART2, ENABLE);
	
  USART_ClearFlag(USART2, USART_FLAG_TC); 
	}
	
void USART_Configuration(void)
{ 												
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  //RCC_AHB1PeriphClockCmd(Open_USARTx_RX_GPIO_CLK,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 
//TX PB10
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	//RX PB11
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_PinSource10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  GPIO_InitStructure.GPIO_Pin = GPIO_PinSource11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
 // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  #if defined HwFlowControl && !defined OpenUART4 && !defined OpenUART5 
  	RCC_AHB1PeriphClockCmd(Open_USARTx_RTS_GPIO_CLK,ENABLE);
	RCC_AHB1PeriphClockCmd(Open_USARTx_CTS_GPIO_CLK,ENABLE);
	
	GPIO_PinAFConfig(Open_USARTx_RTS_GPIO_PORT, Open_USARTx_RTS_SOURCE, Open_USARTx_RTS_AF);
	GPIO_PinAFConfig(Open_USARTx_CTS_GPIO_PORT, Open_USARTx_CTS_SOURCE, Open_USARTx_CTS_AF);

	GPIO_InitStructure.GPIO_Pin = Open_USARTx_RTS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open_USARTx_RTS_GPIO_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = Open_USARTx_CTS_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(Open_USARTx_CTS_GPIO_PORT, &GPIO_InitStructure);
  #endif
	
	
	
	
/*
   		 USARTx configured as follow:
         - BaudRate = 115200 baud  
		 - Word Length = 8 Bits
         - One Stop Bit
         - No parity
         - Hardware flow control disabled (RTS and CTS signals)
         - Receive and transmit    
 */

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  #if defined HwFlowControl && !defined OpenUART4 && !defined OpenUART5
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
  #else
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  #endif
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);
  /* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
     Open_USARTx transmit data register is empty */
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
  USART_Cmd(USART3, ENABLE);
}

void USART_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

  /* Enable the USARTx Interrupt */
 	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/* Use no semihosting */
#if 1
#pragma import(__use_no_semihosting)
struct __FILE
{  
	int handle;
};
FILE __stdout;

_sys_exit(int x)
{
	x = x;
}
#endif

/**
  * @brief  Retargets the C library printf function to the USART1.
  * @param  None
  * @retval None
  */

void  Delay1(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
//  USART_SendData(USART2, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
}


void USART2_IRQHandler(void)
{
	uint16_t ch=0;
	uint16_t a=0;
    //int i = 0; 
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		     
      ch = USART_ReceiveData(USART2);
			Delay1(3000);
		  data=ch+1;
	}
}	






