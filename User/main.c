/**
  ******************************************************************************
  * @file    main.c
  * @author  zhangsu
  * @version V1.0receive
  * @date    2017-08-02
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  */
  
#include "include.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
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
		 res=CAN_SendMsg(0x12 ,canbuf,8);                //���� 8 ���ֽ�		
     if(res)OLED_Display_Str(0,7,"Failed");    //��ʾ����ʧ�� 
     else OLED_Display_Str(0,11,"successful");  //��ʾ���ͳɹ� 
			
			key=Can_Receive_Msg(canbuf); 
			 if(key)                            //���յ������� 
      {    
       for(i=0;i<key;i++) 
       {              
        OLED_Display_Str(15,7,canbuf);//��ʾ����
       } 
      } 
			 Delay_ms(10); 
			
    }
}

/**********************************END OF FILE***********************************/

