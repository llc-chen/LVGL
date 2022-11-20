#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"

#define SPI_LCD_CS_LOW    LCD_CS_GPIO_Port->BSRR = LCD_CS_Pin << 16 //HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,0)
#define SPI_LCD_CS_HIGH   LCD_CS_GPIO_Port->BSRR = LCD_CS_Pin    // HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,1)  

#define SPI_LCD_DATA_W    LCD_DC_GPIO_Port->BSRR =  LCD_DC_Pin         //  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,1)        
#define SPI_LCD_COMMAND_W   LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin << 16 //HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,0)     

#define LCD_RES_HIGH  	LCD_RST_GPIO_Port->BSRR =  LCD_RST_Pin //HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,1) 
#define LCD_RES_LOW 		 LCD_RST_GPIO_Port->BSRR =  LCD_RST_Pin << 16 //HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,0) 

#define LCD_W 128
#define LCD_H 160

// uint16_t BACK_COLOR, POINT_COLOR;

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

typedef struct model
{
	uint16_t modelType;
	uint16_t modelDirection;
	uint16_t modelColor;
	uint16_t modelPositionX;
	uint16_t modelPositionY;
}CubeModel;



void LCD_Write_Command(uint8_t CmdData);//写指令
void LCD_Write_Data(uint8_t Data);  //写数据
void LCD_Init(void);//初始化LCD
void LCD_Set_Window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);  //设定位置
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//画点
void LCD_Write_Data_16(uint16_t data); //写16位数据
void LCD_DrawWindowAsColor(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawCube(uint16_t x,uint16_t y,uint16_t color);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t color,uint16_t bgColor ,uint8_t size,uint8_t *p,uint8_t mode);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_ShowNum(uint16_t x,uint16_t y,uint16_t color,uint16_t bgColor,uint32_t num,uint8_t len,uint8_t size);
uint32_t mypow(uint8_t m,uint8_t n);
//void LCD_DrawCubeModel(uint16_t x,uint16_t y,uint16_t color,uint16_t a[28][4],uint16_t type ,uint16_t direction);
void LCD_DrawCubeModel(CubeModel* model,uint16_t a[28][4]);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);


#endif


