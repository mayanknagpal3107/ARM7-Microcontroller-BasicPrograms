#include<lpc21XX.h>
#define bit(x) (1<<x)

void delay(void);
void lcd_cmm(unsigned char command);
void lcd_data(unsigned char data);
void lcd_init(void);
unsigned char buf[10]= "hellooo";
int u=0;
void LCD_PRINTS(char * string)
{
    int c=0;
    while (string[c]!='\0')
    {
        lcd_data(string[c]);
        c++;
    }
}
void main(void){
//	PINSEL0=0X00000000;
	IODIR0|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<15);
	IODIR1|=(1<<16)|(1<<17)|bit(18)|(1<<19);
	//IO1CLR_bit_P0.19 = 1;
	IOSET0=bit(15);
	lcd_init();
	delay();
	
	
	while(1){
		delay();
		//lcd_cmm(0x00000001);
		//delay();
		lcd_cmm(0x80);
		//LCD_PRINTS("deependra");
	
		//if(IOPIN0 &(1<<8)){
			
		LCD_PRINTS("deependra");
		//delay();
	//	IO0CLR=0X07;
		//delay();
		//}	
		//if(IOPIN0 &(1<<3))
		
			//IO0CLR=0X07;*/
	}	
	//return 0;
}	
void lcd_init(){
	
	lcd_cmm(0x38);
	lcd_cmm(0x0c);
	lcd_cmm(0x06);
	lcd_cmm(0x01);
}	
	void lcd_cmm(unsigned char command){
		
		IOCLR1|=bit(16);
		IOCLR1|=bit(17);
		IOSET1|=bit(18);
		IOPIN0=command;
		 delay();
		IOCLR1|=bit(18);
		
}
	void lcd_data(unsigned char data){
			
		IOSET1=bit(16);
		IOCLR1=bit(17);
		IOSET1|=bit(18);
		IOPIN0=data;
		 delay();
		IOCLR1|=bit(18);
	}	
		
void delay(){
		
		int z,c;
		c=0;
		for(z=0;z<5000;z++){
			c++;
		}
	}		