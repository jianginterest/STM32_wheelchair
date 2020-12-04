/**
  ******************************************************************************
  * @file       OLED.c
  * @author  	Qin xingpeng
  * @date     	2017年8月11日01:48:56
  * @brief     	OLED功能配置
  ******************************************************************************
  * @attention	采用模拟SPI进行控制，移植到其他芯片请修改.h文件进行修改宏定义
  *				
  ******************************************************************************
  */

#include "include.h"

uint16_t Signal_Value=0;

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 
#define X_WIDTH 128
#define Y_WIDTH 64


/**
 * @brief   OLED屏幕写数据
 * @param  	8位数据，一个无符号字符型变量
 * @retval	None
 */
void OLED_WrDat(unsigned char data){
	unsigned char i=8;
    OLED_DC_OH;
	 __NOP();
    OLED_D0_OL;
    __NOP();
	while(i--){
		if(data&0x80){ 
			OLED_D1_OH;
		}else{
			OLED_D1_OL;
		}
		OLED_D0_OH;
		__NOP(); 
		OLED_D0_OL;    
		data<<=1;    
	}
}

/**
 * @brief   OLED屏幕写命令
 * @param  	8位命令，一个无符号字符型变量
 * @retval	None
 */
void OLED_WrCmd(unsigned char cmd){
	unsigned char i=8;
	OLED_DC_OL;
	OLED_D0_OL;
	__NOP(); 
	while(i--){
		if(cmd&0x80){
			OLED_D1_OH;
		}else{
			OLED_D1_OL;
		}
		OLED_D0_OH;
		__NOP();      
		OLED_D0_OL;   
		cmd<<=1;  
	} 	
}

/**
 * @brief   OLED显示配置，配置开始行
 * @param  	8位数据，一个无符号字符型变量
 * @retval	None
 */
void OLED_SetStartColumn(unsigned char d){
	OLED_WrCmd(0x00+d%16);					
	OLED_WrCmd(0x10+d/16);							
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量
 * @retval	None
 */
void OLED_SetAddressingMode(unsigned char d)	{
	OLED_WrCmd(0x20);			
	OLED_WrCmd(d);			
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a和b
 * @retval	None
 */
void OLED_SetColumnAddress(unsigned char a, unsigned char b){
	OLED_WrCmd(0x21);			
	OLED_WrCmd(a);			
	OLED_WrCmd(b);			
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a和b
 * @retval	None
 */
void OLED_SetPageAddress(unsigned char a, unsigned char b){
	OLED_WrCmd(0x22);			
	OLED_WrCmd(a);			
	OLED_WrCmd(b);			
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_SetStartLine(unsigned char d){
	OLED_WrCmd(0x40|d);			
}


/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_SetContrastControl(unsigned char d){
	OLED_WrCmd(0x81);			
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_Set_Charge_Pump(unsigned char d){
	OLED_WrCmd(0x8D);
	OLED_WrCmd(0x10|d);			
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_Set_Segment_Remap(unsigned char d){
	OLED_WrCmd(0xA0|d);

}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_Set_Entire_Display(unsigned char d){
	OLED_WrCmd(0xA4|d);	
}


/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Inverse_Display(unsigned char d){
	OLED_WrCmd(0xA6|d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Multiplex_Ratio(unsigned char d){
	OLED_WrCmd(0xA8);		
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Display_On_Off(unsigned char d){
	OLED_WrCmd(0xAE|d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void SetStartPage(unsigned char d){
	OLED_WrCmd(0xB0|d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Common_Remap(unsigned char d){
	OLED_WrCmd(0xC0|d);
}


/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Display_Offset(unsigned char d){
	OLED_WrCmd(0xD3);
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Display_Clock(unsigned char d){
	OLED_WrCmd(0xD5);
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Precharge_Period(unsigned char d){
	OLED_WrCmd(0xD9);
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_Common_Config(unsigned char d){
	OLED_WrCmd(0xDA);
	OLED_WrCmd(0x02|d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_VCOMH(unsigned char d){
	OLED_WrCmd(0xDB);			
	OLED_WrCmd(d);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void Set_NOP(void){
	OLED_WrCmd(0xE3);
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_CLS(void){
	unsigned char y,x;	
	for(y=0;y<8;y++){
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10); 
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}

/**
 * @brief   OLED显示配置。
 * @param  	8位数据，一个无符号字符型变量a
 * @retval	None
 */
void OLED_Adjust(unsigned char a){
	OLED_WrCmd(a);	//指令数据0x0000~0x003f  
}

/**
 * @brief   OLED设置显示位置。
 * @param  	横坐标X和Y
 * @retval	None
 */
void OLED_Set_Position(unsigned char x, unsigned char y){ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd(x&0x0f);
} 

/**
 * @brief   OLED清屏
 * @param  	None
 * @retval	None
 */
void OLED_Display_Clear(void){
	unsigned char y,x;
	for(y=0;y<8;y++){
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0x00);
	}
}


/**
 * @brief   OLED延时配置，SPI时序
 * @param  	需要延时的时间
 * @retval	None
 */
void OLED_Delay_ms(unsigned int ms){                         
	unsigned int a;
	while(ms){
		a=1335;
		while(a--){}
		ms--;
	}
}

/**
 * @brief   OLED显示一个点。
 * @param  	绘制点的横纵坐标
 * @retval	None
 */
void OLED_Display_Pixel(unsigned char x,unsigned char y){
	unsigned char data1;
    OLED_Set_Position(x,y); 
	data1 = 0x01<<(y%8); 	
	OLED_WrCmd(0xb0+(y>>3));
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x00);
	OLED_WrDat(data1); 	 	
}



/**
 * @brief   OLED显示以为字符
 * @param  	字符的横纵坐标和字符的ascii码
 * @retval	None
 */
void OLED_Display_Char(unsigned char x,unsigned char y,unsigned char asc) {
    u8 i=0;
    OLED_Set_Position(x*7,y);
	for(i=0;i<6;i++){
	   OLED_WrDat(F6x8[asc-32][i]);        
	}
}

/**
 * @brief   OLED显示以为字符串
 * @param  	字符串的横纵坐标和字符的ascii码
 * @retval	None
 */
void OLED_Display_Str(u8 x,u8 y,u8 asc[]){
    u8 i=0,j=0;
    OLED_Set_Position(x*6,y);
	while(asc[j]!='\0'){
		for(i=0;i<6;i++){
		   OLED_WrDat(F6x8[asc[j]-32][i]);        
		}
		j++;
	}
}

/**
 * @brief   OLED显示以为字符串
 * @param  	字符串的横纵坐标和字符的ascii码
 * @retval	None
 */
void OLED_Display_Str2(u8 x,u8 y,u8 asc[]){
    u8 i=0,j=0;
    OLED_Set_Position(x*6,y);
	while(asc[j]!='\0'){
		for(i=0;i<6;i++){
		   OLED_WrDat(F6x8[asc[j]-32][i]);        
		}
		j++;
	}
}

/**
 * @brief   OLED显示浮点数
 * @param  	浮点数的横纵坐标  浮点数， 整数位数，小数位数
 * @retval	None
 */
void OLED_Display_Num(u8 x,u8 y,double Number,u8 N1,u8 N2){
    u8 i=0;
	u8 Num[10]={0};
	uint16_t integer=0,decimal=0;
    OLED_Set_Position(x*6,y);
	integer=(uint16_t)(fabs(Number));
	decimal=(uint16_t) ( ceilf((fabs(Number)-integer)*(pow(10,N2))));
	if(Number<0) Num[0]='-'; else Num[0]=' ';
	if (N2!=0) Num[N1+1]='.'; else Num[N1+1]=' ';
	for(i=1;i<=N1;i++){
		Num[i]=((int)((integer/( pow(10,(N1-i)))))%10)+48;
	}
	for(i=1;i<=N2;i++){
		Num[N1+i+1]=((int)((decimal/(pow(10,(N2-i)))))%10)+48;
	}
	OLED_Display_Str(x,y,Num); 
}


void OLED_Display_Num2(uint8_t x, uint8_t y, uint16_t num) {
	unsigned char j=0;
    unsigned char H1000[]="1000";
    if(num==1000){
        OLED_Display_Str(x,y,H1000); 
    }else{
        if(num>=100){
            unsigned char n[3]={0};
            n[0]=(num/100)%10;
            n[1]=(num/10)%10;
            n[2]=num%10;	   
            for(j=0;j<3;j++) n[j]=n[j]+16+32;
            OLED_Display_Str(x,y,n); 
        }else{
            unsigned char n[2]={0};
            n[0]=(num/10)%10;
            n[1]=num%10;		   
            for(j=0;j<2;j++) n[j]=n[j]+16+32;
            OLED_Display_Str(x,y,n); 
        }
    }
}

/**
 * @brief   OLED显示中文
 * @param  	None
 * @retval	None
 */
void OLED_ShowCHinese(u8 x,u8 y,u8 no){      			    
	u8 t,adder=0;
	OLED_Set_Position(x,y);	
    for(t=0;t<16;t++){
		OLED_WrDat(Hzk[2*no][t]);
		adder+=1;
	}	
	OLED_Set_Position(x,y+1);	
    for(t=0;t<16;t++){	
		OLED_WrDat(Hzk[2*no+1][t]);
		adder+=1;
	}					
}

/**
 * @brief   OLED显示图片
 * @param  	None
 * @retval	None
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]){ 	
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0) y=y1/8;      
	else y=y1/8+1;
	for(y=y0;y<y1;y++){
		OLED_Set_Position(x0,y);
		for(x=x0;x<x1;x++){      
		OLED_WrDat(BMP[j++]);	    	
		}
	}
} 

/**
 * @brief   动态刷新信号强度
 * @param  	None
 * @retval	None
 */
void OLED_Draw_Signal(uint8_t status){ 	
	uint8_t j=0,x,y;
    uint8_t Position_Clear[]="  "	;
	uint8_t Lost[]="x"	;
	
	OLED_Display_Str(0,0,Position_Clear);
    if(status>=4) status=12;
	if(status==3) status=11;
	if(status==2) status=9;
	if(status<=1) { 
		
		for(y=0;y<1;y++)
		{
			OLED_Set_Position(0,y);
			for(x=0;x<7;x++){      
				OLED_WrDat(Signal_Status[j++]);	    	
			}
		}
		OLED_Display_Str(1,0,Lost);
		
	}else{
		for(y=0;y<1;y++)
		{
			OLED_Set_Position(0,y);
			for(x=0;x<status;x++){      
				OLED_WrDat(Signal_Status[j++]);	    	
			}
		}
	}
} 

/**
 * @brief   动态刷新电池容量
 * @param  	None
 * @retval	None
 */
void OLED_Draw_Battery(float Battery_Level){ 
	uint8_t status=0;	

	OLED_Display_Num(12,0,Battery_Level,1,1);
	if(Battery_Level>8) status=4;
	if(Battery_Level<8 && Battery_Level>7.7 ) status=3;
	if(Battery_Level<7.7 && Battery_Level>7.5) status=2;
	if(Battery_Level<7.5 && Battery_Level>7.2) status=1;
	if(Battery_Level<7.2) status=0;

	switch(status){
		case 4: OLED_DrawBMP(110,0,128,1,Battery_Status_4); break;
		case 3: OLED_DrawBMP(110,0,128,1,Battery_Status_3); break;
		case 2: OLED_DrawBMP(110,0,128,1,Battery_Status_2); break;
		case 1: OLED_DrawBMP(110,0,128,1,Battery_Status_1); break;
		case 0: OLED_DrawBMP(110,0,128,1,Battery_Status_0); break;
	}	
} 



/**
 * @brief   OLED显示不动字符
 * @param  	None
 * @retval	None
 */
void OLED_Display_Symbol(void){
	uint8_t NRF_Fre[]="Ghz";
	uint8_t T_Str[]="T:  %";
	uint8_t P_Str[]="P:  %";
	uint8_t Y_Str[]="Y:  %";
	uint8_t R_Str[]="R:  %";
	uint8_t Frequency[]="PWM:";
	uint8_t Hz[]="Hz";
	uint8_t Option[]="Option";
	
	OLED_Display_Str(8,0,NRF_Fre);
	OLED_Display_Char(14,0,'v');
	
	OLED_Display_Str(2,2,T_Str);
	OLED_Display_Str(12,2,P_Str);
		
	OLED_Display_Str(2,4,Y_Str);
	OLED_Display_Str(12,4,R_Str);

	OLED_Display_Str(0,7,Frequency);

//	if(Flash_Buff[0]<100){
//		OLED_Display_Num2(4,7,Flash_Buff[0]);
//		OLED_Display_Str(6,7,Hz);
//	}else if(Flash_Buff[0]>=100&&Flash_Buff[0]<1000){
//		OLED_Display_Num2(4,7,Flash_Buff[0]);
//		OLED_Display_Str(7,7,Hz);
//	}else{
//        OLED_Display_Num2(4,7,Flash_Buff[0]);
//		OLED_Display_Str(8,7,Hz);
//    }

	OLED_Display_Str(15,7,Option);
	OLED_Draw_Signal(4);
//	OLED_Display_Num(2,0,(2400+NRF_Channel)/1000.0,1,3);
}

/**
 * @brief   OLED初始化，配置对应端口，初始化完成后清除所有内容
 * @param  	None
 * @retval	None
 */
void OLED_init(void){
	GPIO_InitTypeDef OLED_GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(OLED_RCCEN, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_SCL|OLED_SDA;
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &OLED_GPIO_InitStructure);
	
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_RST|OLED_DC;
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &OLED_GPIO_InitStructure);
	
	
	OLED_D0_OH;	
	OLED_RST_OL;
	OLED_Delay_ms(50);
	OLED_RST_OH;
    OLED_WrCmd(0xAE | 0x00);
    OLED_WrCmd(0xD5);
    OLED_WrCmd(0x80);
    OLED_WrCmd(0xA8);
    OLED_WrCmd(0x3F);
    OLED_WrCmd(0xD3);
    OLED_WrCmd(0x00);		   
    OLED_WrCmd(0x40 | 0x00);    
    OLED_WrCmd(0x8D);
    OLED_WrCmd(0x10 | 0x04);	 
    OLED_WrCmd(0x20);
    OLED_WrCmd(0x02);		    
    OLED_WrCmd(0xA0 | 0x01);     
    OLED_WrCmd(0xC0 | 0x08);     
    OLED_WrCmd(0xDA);
    OLED_WrCmd(0x02 | 0x10);     
    OLED_WrCmd(0x81);
    OLED_WrCmd(0xCF);	         
    OLED_WrCmd(0xD9);
    OLED_WrCmd(0xF1);            
    OLED_WrCmd(0xDB);
    OLED_WrCmd(0x40);	         
    OLED_WrCmd(0xA4 | 0x00);	 
    OLED_WrCmd(0xA6 | 0x00);	
    OLED_WrCmd(0xAE | 0x01);    
	OLED_Display_Clear();  
	OLED_Set_Position(0,0);  	
} 

/******************* (C) COPYRIGHT 2017 Qin xingpeng *****END OF FILE****/
