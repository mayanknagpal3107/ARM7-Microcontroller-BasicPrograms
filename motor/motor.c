#include<lpc21xx.h>
#define bit(x) (1<<x)
static void pll_feed(void); 
void pll_init( int cfg );
void delay();
int main(){
	
		IODIR0|=bit(0)|bit(1)|bit(2)|bit(3);
		IOSET0=bit(0);
		IOCLR0=bit(3);
	pll_init(0x24);
	while(1){
		
		//if(IOPIN0&bit(3)){
			IOSET0=bit(1);
			delay();
			IOCLR0=bit(1);
			delay();
		//}
		//if(~IOPIN0&bit(3)){
			//IOSET0=bit(2);
			//IOCLR0=bit(1);
		//}
	}	
}
void pll_init( int cfg )
{
  int loop_ctr;
  // Step 1: Set CFG and CON
  PLLCFG = cfg;
  PLLCON = 0x01; // PLL Enable
  // Step 2: Security measure: feed
  pll_feed();
// Step 3: Wait for the lock into the new frequency
  //loop_ctr = 10000;
	while(!(PLLSTAT & 0x00000400)); //is locked?
  // if PLL0STAT & (1<<10) does not hold, we have an issue...
  // Step 4: Connect the PLL
  PLLCON = 0x03;
  // Step 5: Security measure: feed
  pll_feed();
	VPBDIV=0x01;
}
 
static void pll_feed( void )
{
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
}
void delay(){
	unsigned long int x,d=0;
	for(x=0;x<=63;x++);
}
	
