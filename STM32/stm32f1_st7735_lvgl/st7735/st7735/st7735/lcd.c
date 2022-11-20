#include "lcd.h"
#include "font.h"

extern SPI_HandleTypeDef hspi1;
//extern TIM_HandleTypeDef htim2; 

void LCD_Write_Command(uint8_t CmdData)  //写指令
{
	SPI_LCD_CS_LOW; //片选
	SPI_LCD_COMMAND_W;//写指令
	HAL_SPI_Transmit(&hspi1,&CmdData,1,100);
	SPI_LCD_CS_HIGH;
} 

void LCD_Write_Data(uint8_t Data)  //写8位数据
{
	SPI_LCD_CS_LOW; //片选
	SPI_LCD_DATA_W;//写数据
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&Data,1,1);
	SPI_LCD_CS_HIGH; 
}

void LCD_Write_Data_16(uint16_t data) //写16位数据
{
	SPI_LCD_CS_LOW;
	SPI_LCD_DATA_W;//写数据
	uint8_t colorHighBit = data >> 8;
	uint8_t colorLowBit = (uint8_t)data;
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&colorHighBit,1,16);
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&colorLowBit,1,16);
	SPI_LCD_CS_HIGH;
}	 

void LCD_Set_Window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)  //设定位置
{  
   LCD_Write_Command(0x2a);
   LCD_Write_Data(x1>>8);
   LCD_Write_Data(x1);
   LCD_Write_Data(x2>>8);
   LCD_Write_Data(x2);
	
   LCD_Write_Command(0x2b);
   LCD_Write_Data(y1>>8);
   LCD_Write_Data(y1);
   LCD_Write_Data(y2>>8);
   LCD_Write_Data(y2);
	
   LCD_Write_Command(0x2C);
}


void LCD_DrawWindowAsColor(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	LCD_Set_Window(x1,y1,x2,y2);
	SPI_LCD_CS_LOW;
	SPI_LCD_DATA_W;//写数据
	uint8_t colorHighBit = color >> 8;
	uint8_t colorLowBit = (uint8_t)color;
	for(int i = 0; i < (x2 - x1 + 1)*(y2 - y1 + 1) ; i++)
	{	
		HAL_SPI_Transmit(&hspi1,(uint8_t *)&colorHighBit,1,16);
		HAL_SPI_Transmit(&hspi1,(uint8_t *)&colorLowBit,1,16);
	}
	SPI_LCD_CS_HIGH;
}


void LCD_Init(void)
{ 
	LCD_RES_HIGH;
  HAL_Delay(5);	
	LCD_RES_LOW;
	HAL_Delay(5);
	LCD_RES_HIGH;
	SPI_LCD_CS_HIGH; 
	HAL_Delay(5);
	SPI_LCD_CS_LOW;  //打开片选使能

	LCD_Write_Command(0x11); //Sleep out
	HAL_Delay(120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	LCD_Write_Command(0xB1);
	LCD_Write_Data(0x05);


	LCD_Write_Command(0x11);//Sleep exit 
	HAL_Delay (120);
	 
	//ST7735R Frame Rate
	LCD_Write_Command(0xB1); 
	LCD_Write_Data(0x01); 

	LCD_Write_Data(0x2C); LCD_Write_Data(0x2D); 
	LCD_Write_Command(0xB2); 
	LCD_Write_Data(0x01); LCD_Write_Data(0x2C); LCD_Write_Data(0x2D); 
	LCD_Write_Command(0xB3); 
	LCD_Write_Data(0x01); LCD_Write_Data(0x2C); LCD_Write_Data(0x2D); 
	LCD_Write_Data(0x01); LCD_Write_Data(0x2C); LCD_Write_Data(0x2D); 

	LCD_Write_Command(0xB4); //Column inversion 
	LCD_Write_Data(0x07); 
	 
	//ST7735R Power Sequence
	LCD_Write_Command(0xC0); 
	LCD_Write_Data(0xA2); LCD_Write_Data(0x02); LCD_Write_Data(0x84); 
	LCD_Write_Command(0xC1); LCD_Write_Data(0xC5); 
	LCD_Write_Command(0xC2); 
	LCD_Write_Data(0x0A); LCD_Write_Data(0x00); 
	LCD_Write_Command(0xC3); 
	LCD_Write_Data(0x8A); LCD_Write_Data(0x2A); 
	LCD_Write_Command(0xC4); 
	LCD_Write_Data(0x8A); LCD_Write_Data(0xEE); 
	 
	LCD_Write_Command(0xC5); //VCOM 
	LCD_Write_Data(0x0E); 
	 
	LCD_Write_Command(0x36); //MX, MY, RGB mode 
	LCD_Write_Data(0xC8); 

	//ST7735R Gamma Sequence
	LCD_Write_Command(0xe0); 
	LCD_Write_Data(0x0f); LCD_Write_Data(0x1a); 
	LCD_Write_Data(0x0f); LCD_Write_Data(0x18); 
	LCD_Write_Data(0x2f); LCD_Write_Data(0x28); 
	LCD_Write_Data(0x20); LCD_Write_Data(0x22); 
	LCD_Write_Data(0x1f); LCD_Write_Data(0x1b); 
	LCD_Write_Data(0x23); LCD_Write_Data(0x37); LCD_Write_Data(0x00); 

	LCD_Write_Data(0x07); 
	LCD_Write_Data(0x02); LCD_Write_Data(0x10); 
	LCD_Write_Command(0xe1); 
	LCD_Write_Data(0x0f); LCD_Write_Data(0x1b); 
	LCD_Write_Data(0x0f); LCD_Write_Data(0x17); 
	LCD_Write_Data(0x33); LCD_Write_Data(0x2c); 
	LCD_Write_Data(0x29); LCD_Write_Data(0x2e); 
	LCD_Write_Data(0x30); LCD_Write_Data(0x30); 
	LCD_Write_Data(0x39); LCD_Write_Data(0x3f); 
	LCD_Write_Data(0x00); LCD_Write_Data(0x07); 
	LCD_Write_Data(0x03); LCD_Write_Data(0x10);  

	LCD_Write_Command(0x2a);
	LCD_Write_Data(0x00);LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);LCD_Write_Data(0x7f);
	LCD_Write_Command(0x2b);
	LCD_Write_Data(0x00);LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);LCD_Write_Data(0x7f);
	/*
	LCD_Write_Command(0xF0); //Enable test command  
	LCD_Write_Data(0x01); 
	LCD_Write_Command(0xF6); //Disable ram power save mode 
	LCD_Write_Data(0x00); 
	 */

	LCD_Write_Command(0x3A); //65k mode 
	LCD_Write_Data(0x05); 
	LCD_Write_Command(0x29); //Display on
	LCD_Write_Command(0x2C);  
}



void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Set_Window(x,y,x,y);//设置光标位置 
	LCD_Write_Data_16(color); 	    
} 	

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}  


void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
{  
    uint8_t temp;
    uint8_t pos,t;
		   
	num=num-' ';//得到偏移后的值
	LCD_Set_Window(x,y,x+size/2-1,y+size-1);//设置单个文字显示窗口
	
	if(!mode) //非叠加方式
	{		
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
			else temp=asc2_1608[num][pos];		 //调用1608字体
			for(t=0;t<size/2;t++)
		    {                 
		      if(temp&0x01)LCD_Write_Data_16(fc); 
					else LCD_Write_Data_16(bc); 
					temp>>=1; 
		    }
		}	
	}else//叠加方式
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
			else temp=asc2_1608[num][pos];		 //调用1608字体
			for(t=0;t<size/2;t++)
		    {              
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos,fc);//画一个点    
		        temp>>=1; 
		    }
		}
	}
	LCD_Set_Window(0,0,131,161);//恢复窗口为全屏    	   	 	  
}

uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

void LCD_ShowNum(uint16_t x,uint16_t y,uint16_t color,uint16_t bgColor,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,color,bgColor,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,color,bgColor,temp+'0',size,0); 
	}
} 

void LCD_ShowString(uint16_t x,uint16_t y,uint16_t color,uint16_t bgColor ,uint8_t size,uint8_t *p,uint8_t mode)
{         
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
		if(x>(132-1)||y>(161-1)) 
		return;     
        LCD_ShowChar(x,y,color,bgColor,*p,size,mode);
        x+=size/2;
        p++;
    }  
} 

void LCD_DrawCube(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_DrawWindowAsColor(x+1,y+1,x+6,y+6,color);
}

void LCD_DrawCubeModel(CubeModel* model,uint16_t a[28][4])
{
	for(int i = 0 ; i < 4 ; i ++)
	{
		uint16_t temp = a[model->modelType*4+model->modelDirection][i];
		uint16_t row = temp/4;
		uint16_t col = temp%4;
		LCD_DrawCube(8*col+(1+8*model->modelPositionX),8*row+(1+8*model->modelPositionY),model->modelColor);
	}
}






