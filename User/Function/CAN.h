#ifndef __CAN_H
#define	__CAN_H



#define CAN_MASTER          0x0000 	    //定义主机代号

void CAN1_Init(void);

u8 CAN_SendMsg(uint32_t ID, u8* data,u8 len);

u8 Can_Receive_Msg(u8 *buf);


#endif /* __CAN_H */


