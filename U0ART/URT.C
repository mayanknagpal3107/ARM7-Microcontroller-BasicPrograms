#include<lpc21XX.h>
void uart0_char(unsigned char data);
void uart0_str(unsigned char *msg);
void uart0_init(void);
unsigned char uart0_read(void);
unsigned char UART0ISR(void);

void delay(void);
void uart0_init(){
	PINSEL0=0X00000005;
	U0LCR=0X83;
	U0FDR = 0xa1;
	U0DLM=0X00;
	U0DLL=0X62;
	U0LCR=0X03;	
	U0FCR=0X01;
	U0IER =0x03;
	
}
void uart0_char(unsigned char data){
	
		while(!(U0LSR&0X20));
		U0THR=data;
}
void uart0_str(unsigned char *msg){
	
	int c=0;
	while(msg[c]!='\0'){
		uart0_char(msg[c]);
		c++;
	}	
}	
unsigned char i=0;
int main(void){
	IODIR0|=(1<<4);
	IOCLR0=8;
	uart0_init();
	//
	while(1){
		i=UART0ISR();
		if(IOPIN0&(1<<4)){
			uart0_char('d');
			delay();
		}
		if(i!=0){
			//IOSET0=8;
		uart0_char(i);
		}	
}
	}
void delay(){
		
		int z,c;
		c=0;
		for(z=0;z<5000;z++){
			c++;
		}
	}
unsigned char UART0ISR(void)
{
    if(U0IIR &0X04){
			//VICVectAddr = 0x00;
        return(U0RBR);
		}	
		else
				return 0;
    
}
/*unsigned char uart0_read(void){
	
		//while(!(U0LSR&0X01));
		//i=0;
	if(U0LSR&)
		return(U0RBR);
	else
		return 0;
	
}*/