#include "include.h"

/*
PB8		CAN_Rx
PB9		CAN_Tx
*/
void CAN1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;//过滤器

    /* 复用功能和GPIOB端口时钟使能*/	 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	  
    /* CAN1 模块时钟使能 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	

    /******************* Configure CAN pin: RX *******************/	 // PB8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	    // 上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /******************* Configure CAN pin: TX **********************/   // PB9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     // 复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);//使能重映射	

  
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    #ifdef  VECT_TAB_RAM  
    /* Set the Vector Table base location at 0x20000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
    #else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
    #endif

    /********************* enabling interrupt ************************/
		//NVIC_IRQChannel 		该参数用以使能或者失能指定的 IRQ 通道
		//USB_LP_CAN_RX0_IRQChannel 		USB 低优先级或者 CAN 接收 0 中断 
		//CAN_ITConfig 		使能或者失能指定的 CAN 中断
		//CAN_IT_FMP0  FIFO0 消息挂号中断屏蔽
    CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);  //FIFO0消息挂号中断允许   
    NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;  //CAN1 RX0中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//成员 NVIC_IRQChannel 中的从优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /************************* CAN register init ******************************/
    CAN_DeInit(CAN1);	//将外设CAN的全部寄存器重设为缺省值
    CAN_StructInit(&CAN_InitStructure);//把CAN_InitStruct中的每一个参数按缺省值填入

    /* CAN 单元设置 */
    CAN_InitStructure.CAN_TTCM=DISABLE;         //没有使能时间触发模式 
    CAN_InitStructure.CAN_ABOM=DISABLE;         //没有使能自动离线管理
    CAN_InitStructure.CAN_AWUM=DISABLE;         //没有使能自动唤醒模式
    CAN_InitStructure.CAN_NART=DISABLE;         //没有使能非自动重传模式
    CAN_InitStructure.CAN_RFLM=DISABLE;         //没有使能接收FIFO锁定模式
    CAN_InitStructure.CAN_TXFP=DISABLE;         //没有使能发送FIFO优先级
		
	  /*设置波特率*/
    CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//CAN设置为正常模式
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      //重新同步跳跃宽度1个时间单位
    CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      //时间段1为3个时间单位
    CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      //时间段2为2个时间单位
    CAN_InitStructure.CAN_Prescaler=6;         //分频系数（CAN_Prescaler+1）	
    CAN_Init(CAN1,&CAN_InitStructure);          //波特率为：72M/2/60(1+3+2)=0.1 即波特率为100KBPs

    /**********CAN filter init 过滤器，已经设置为任意，可以通过ExtId标识符区分从机代号**************/
		//https://www.cnblogs.com/dongry/p/9896691.html
    CAN_FilterInitStructure.CAN_FilterNumber=1;                     //指定过滤器为1，它的范围是 1 到 13。
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;   //指定过滤器为标识符屏蔽位模式
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //过滤器位宽为32位
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                //过滤器标识符的高16位值
    CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_EXT|CAN_RTR_DATA;//过滤器标识符的低16位值
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;            //过滤器屏蔽标识符的高16位值
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;             //过滤器屏蔽标识符的低16位值
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     //设定了指向过滤器的FIFO为0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;            //使能过滤器
    CAN_FilterInit(&CAN_FilterInitStructure);                       //按上面的参数初始化过滤器

        
}
/* 发送数据*/
u8 CAN_SendMsg(uint32_t ID, u8* data,u8 len)
{ 
    u8 mbox;
    u16 i=0; 
    CanTxMsg TxMessage;  //结构 CanTxMsg 定义于文件“stm32f10x_can.h
    
    TxMessage.StdId=ID;	 	//标准标识符为0x0000，StdId 用来设定标准标识符
    TxMessage.ExtId=CAN_MASTER;  	//扩展标识符0x0000，ExtId 用来设定扩展标识符
    TxMessage.IDE=CAN_ID_STD;   	//使用扩展标识符，IDE 用来设定消息标识符的类型：CAN_ID_STD ：使用标准标识符 CAN_ID_EXT ：使用标准标识符 + 扩展标识符 
    TxMessage.RTR=CAN_RTR_DATA; 	//为数据帧，RTR 用来设定待传输消息的帧类型：CAN_RTR_DATA ：数据帧 CAN_RTR_REMOTE ：远程帧
    TxMessage.DLC=len;	        		//消息的数据长度为2个字节，DLC 用来设定待传输消息的帧长度。
    for(i=0;i<len;i++)  
        TxMessage.Data[i] = data[i];//Data[8]包含了待传输数据，它的取值范围为 0 到 0xFF
    mbox= CAN_Transmit(CAN1, &TxMessage);  //发送数据
	/*
	函数原形 uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox) 
	功能描述  检查消息传输的状态
	返回值  CANTXOK CAN 驱动是否在传输数据 
					CANTXPENDING 消息是否挂号 
					CANTXFAILED 其他 
	*/
	//检测数据的发送状态。如果失败，等到i加到0xFFF退出循环，并返回"1"；成功则返回"0".
   i=0;
	 while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
        i++;	//等待发送结束
		Delay_ms(70);
    if(i>=0XFFF)
        return 0;//发送失败
    return 1;//发送成功	
}


/*
	can 口接收数据查询 
	buf:数据缓存区;   
	返回值:0,无数据被收到; 
	其他,接收的数据长度; 
*/
u8 Can_Receive_Msg(u8 *buf) 
{           
  u32 i; 
  CanRxMsg RxMessage; 
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;//没有接收到数据,直接退出  
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);       //读取数据  
  for(i=0;i<8;i++) 
    buf[i]=RxMessage.Data[i];   
  return RxMessage.DLC;  
} 


