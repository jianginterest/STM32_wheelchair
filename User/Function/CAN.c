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
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;//������

    /* ���ù��ܺ�GPIOB�˿�ʱ��ʹ��*/	 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	  
    /* CAN1 ģ��ʱ��ʹ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	

    /******************* Configure CAN pin: RX *******************/	 // PB8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	    // ��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /******************* Configure CAN pin: TX **********************/   // PB9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     // �����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);//ʹ����ӳ��	

  
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
		//NVIC_IRQChannel 		�ò�������ʹ�ܻ���ʧ��ָ���� IRQ ͨ��
		//USB_LP_CAN_RX0_IRQChannel 		USB �����ȼ����� CAN ���� 0 �ж� 
		//CAN_ITConfig 		ʹ�ܻ���ʧ��ָ���� CAN �ж�
		//CAN_IT_FMP0  FIFO0 ��Ϣ�Һ��ж�����
    CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);  //FIFO0��Ϣ�Һ��ж�����   
    NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;  //CAN1 RX0�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ա NVIC_IRQChannel �еĴ����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /************************* CAN register init ******************************/
    CAN_DeInit(CAN1);	//������CAN��ȫ���Ĵ�������Ϊȱʡֵ
    CAN_StructInit(&CAN_InitStructure);//��CAN_InitStruct�е�ÿһ��������ȱʡֵ����

    /* CAN ��Ԫ���� */
    CAN_InitStructure.CAN_TTCM=DISABLE;         //û��ʹ��ʱ�䴥��ģʽ 
    CAN_InitStructure.CAN_ABOM=DISABLE;         //û��ʹ���Զ����߹���
    CAN_InitStructure.CAN_AWUM=DISABLE;         //û��ʹ���Զ�����ģʽ
    CAN_InitStructure.CAN_NART=DISABLE;         //û��ʹ�ܷ��Զ��ش�ģʽ
    CAN_InitStructure.CAN_RFLM=DISABLE;         //û��ʹ�ܽ���FIFO����ģʽ
    CAN_InitStructure.CAN_TXFP=DISABLE;         //û��ʹ�ܷ���FIFO���ȼ�
		
	  /*���ò�����*/
    CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//CAN����Ϊ����ģʽ
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      //����ͬ����Ծ���1��ʱ�䵥λ
    CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      //ʱ���1Ϊ3��ʱ�䵥λ
    CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      //ʱ���2Ϊ2��ʱ�䵥λ
    CAN_InitStructure.CAN_Prescaler=6;         //��Ƶϵ����CAN_Prescaler+1��	
    CAN_Init(CAN1,&CAN_InitStructure);          //������Ϊ��72M/2/60(1+3+2)=0.1 ��������Ϊ100KBPs

    /**********CAN filter init ���������Ѿ�����Ϊ���⣬����ͨ��ExtId��ʶ�����ִӻ�����**************/
		//https://www.cnblogs.com/dongry/p/9896691.html
    CAN_FilterInitStructure.CAN_FilterNumber=1;                     //ָ��������Ϊ1�����ķ�Χ�� 1 �� 13��
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;   //ָ��������Ϊ��ʶ������λģʽ
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //������λ��Ϊ32λ
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                //��������ʶ���ĸ�16λֵ
    CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_EXT|CAN_RTR_DATA;//��������ʶ���ĵ�16λֵ
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;            //���������α�ʶ���ĸ�16λֵ
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;             //���������α�ʶ���ĵ�16λֵ
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     //�趨��ָ���������FIFOΪ0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;            //ʹ�ܹ�����
    CAN_FilterInit(&CAN_FilterInitStructure);                       //������Ĳ�����ʼ��������

        
}
/* ��������*/
u8 CAN_SendMsg(uint32_t ID, u8* data,u8 len)
{ 
    u8 mbox;
    u16 i=0; 
    CanTxMsg TxMessage;  //�ṹ CanTxMsg �������ļ���stm32f10x_can.h
    
    TxMessage.StdId=ID;	 	//��׼��ʶ��Ϊ0x0000��StdId �����趨��׼��ʶ��
    TxMessage.ExtId=CAN_MASTER;  	//��չ��ʶ��0x0000��ExtId �����趨��չ��ʶ��
    TxMessage.IDE=CAN_ID_STD;   	//ʹ����չ��ʶ����IDE �����趨��Ϣ��ʶ�������ͣ�CAN_ID_STD ��ʹ�ñ�׼��ʶ�� CAN_ID_EXT ��ʹ�ñ�׼��ʶ�� + ��չ��ʶ�� 
    TxMessage.RTR=CAN_RTR_DATA; 	//Ϊ����֡��RTR �����趨��������Ϣ��֡���ͣ�CAN_RTR_DATA ������֡ CAN_RTR_REMOTE ��Զ��֡
    TxMessage.DLC=len;	        		//��Ϣ�����ݳ���Ϊ2���ֽڣ�DLC �����趨��������Ϣ��֡���ȡ�
    for(i=0;i<len;i++)  
        TxMessage.Data[i] = data[i];//Data[8]�����˴��������ݣ�����ȡֵ��ΧΪ 0 �� 0xFF
    mbox= CAN_Transmit(CAN1, &TxMessage);  //��������
	/*
	����ԭ�� uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox) 
	��������  �����Ϣ�����״̬
	����ֵ  CANTXOK CAN �����Ƿ��ڴ������� 
					CANTXPENDING ��Ϣ�Ƿ�Һ� 
					CANTXFAILED ���� 
	*/
	//������ݵķ���״̬�����ʧ�ܣ��ȵ�i�ӵ�0xFFF�˳�ѭ����������"1"���ɹ��򷵻�"0".
   i=0;
	 while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
        i++;	//�ȴ����ͽ���
		Delay_ms(70);
    if(i>=0XFFF)
        return 0;//����ʧ��
    return 1;//���ͳɹ�	
}


/*
	can �ڽ������ݲ�ѯ 
	buf:���ݻ�����;   
	����ֵ:0,�����ݱ��յ�; 
	����,���յ����ݳ���; 
*/
u8 Can_Receive_Msg(u8 *buf) 
{           
  u32 i; 
  CanRxMsg RxMessage; 
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;//û�н��յ�����,ֱ���˳�  
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);       //��ȡ����  
  for(i=0;i<8;i++) 
    buf[i]=RxMessage.Data[i];   
  return RxMessage.DLC;  
} 


