#include<lpc21XX.h>
void SWUInt(unsigned int dataword);
void initClocks(void);
void initTimer0(void);
void setupPLL0(void);
void feedSeq(void);
void connectPLL0(void);
void uart0_char(unsigned char data);
void uart0_str(unsigned char *msg);
void uart0_init(void);
unsigned char uart0_read(void);
unsigned char UART0ISR(void);
__irq void PWM1_IRQ(void);
void initPWM(void);
#define PLOCK 0x00000400
#define PRESCALE 60000   //60000 PCLK clock cycles to increment TC by 1 
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
void initClocks(void)
{
    setupPLL0();
    feedSeq(); //sequence for locking PLL to desired freq.
    connectPLL0();
    feedSeq(); //sequence for connecting the PLL as system clock
   
    //SysClock is now ticking @ 60Mhz!
       
    VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz
    
    //Using PLL settings as shown in : http://www.ocfreaks.com/lpc214x-pll-tutorial-for-cpu-and-peripheral-clock/
    //PLL0 Now configured!
}
void setupPLL0(void)
{
    //Note : Assuming 12Mhz Xtal is connected to LPC2148.
    
    PLLCON = 0x01; // PPLE=1 & PPLC=0 so it will be enabled
                    // but not connected after FEED sequence
    PLLCFG = 0x24; // set the multipler to 5 (i.e actually 4)
                    // i.e 12x5 = 60 Mhz (M - 1 = 4)!!!
                    // Set P=2 since we want FCCO in range!!!
                    // So , Assign PSEL =01 in PLL0CFG as per the table.
}

void feedSeq(void)
{
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
}

void connectPLL0(void)
{
    // check whether PLL has locked on to the  desired freq by reading the lock bit
    // in the PPL0STAT register

    while( !( PLLSTAT & PLOCK ));

    // now enable(again) and connect
    PLLCON = 0x03;
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
int a=0;
int main(){
	
	initClocks();
	uart0_init();
	//IODIR0 = 0xFFFFFFFF;
	//PWMIR=0X02;
	//PWMMCR = (1<<1); // Reset PWMTC on PWMMR0 match
	/*PWMMR0=10000;
	PWMMR1=1000;
	PWMMCR=0X02;
	PINSEL0 = (1<<1);
	 PWMPCR = (1<<9); // enable PWM output
	PWMPR=59999;
	PWMLER = (1<<1) | (1<<0);
	VICVectAddr8 = (unsigned)PWM1_IRQ; //PWM ISR vec.addr
 VICVectCntl8 = 0x00000028; // Set channel
 VICIntEnable = 0x00000100; // Enable the interrupt
	PWMTCR = 0x00000002; // Reset counter and prescaler
   PWMTCR = 0x00000005; // release counter from reset*/
	initPWM();
	while(1){
	}
	
}
void initPWM(void)
{
	/*Assuming that PLL0 has been setup with CCLK = 60Mhz and PCLK also = 60Mhz.*/
	/*This is a per the Setup & Init Sequence given in the tutorial*/

	PINSEL0 = (1<<1); // Select PWM1 output for Pin0.0
	PWMPCR = (1<<9); // enable PWM output
	PWMPR = 60000-1; // 1 micro-second resolution
	PWMMR0 = 10000; // 10ms period duration
	PWMMR1 = 2500; // 2.5ms - pulse duration i.e width (Brigtness level)
	PWMMCR = (1<<1); // Reset PWMTC on PWMMR0 match
	PWMLER = (1<<1) | (1<<0); // update MR0 and MR1
	PWMPCR = (1<<9); // enable PWM output
	PWMTCR =0X18 ; //Reset PWM TC & PR

	//Now , the final moment - enable everything
	PWMTCR = (1<<0) | (1<<3); // enable counters and PWM Mode

	//PWM Generation goes active now - LED must be 25% Bright after boot!!
	//Now you can get the PWM output at Pin P0.0!
}
__irq void PWM1_IRQ()
{
	
 PWMIR |= 0x00000001; // Clear match0 interrupt
 VICVectAddr = 0x00000000;
	a++;
	//IOSET0=0XFFFFFFFF;
	//PWMTC=0X00;
}
