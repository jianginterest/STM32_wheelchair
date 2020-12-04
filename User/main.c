/**
  ******************************************************************************
  * @file    main.c
  * @author  zhangsu
  * @version V1.0receive
  * @date    2017-08-02
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  */
  
#include "include.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */


int main(void)
{
  	u8 canbuf[8]; 
	  u8 res ,key,i; 
	
	  Delay_init();
	  GPIO_init();
	  Usart_init();
	  OLED_init();	
	  OLED_Display_Symbol();
	  CAN1_Init();
	
	  
	  while(1)
		{
	    //Delay_ms(100);
	    //USART_SendData(USART1,'c');
		 res=CAN_SendMsg(0x12 ,canbuf,8);                //发送 8 个字节		
     if(res)OLED_Display_Str(0,7,"Failed");    //提示发送失败 
     else OLED_Display_Str(0,11,"successful");  //提示发送成功 
			
			key=Can_Receive_Msg(canbuf); 
			 if(key)                            //接收到有数据 
      {    
       for(i=0;i<key;i++) 
       {              
        OLED_Display_Str(15,7,canbuf);//显示数据
       } 
      } 
			 Delay_ms(10); 
			
    }
}

/**********************************END OF FILE***********************************/

