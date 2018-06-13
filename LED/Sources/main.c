/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */



int main(void)
{
	int counter = 0;
	
	
	
	
	for(;;) {
		//INITIALITZATION
		//R: PORTB18, G: PORTB19, B: PORTD1
		//Enable clock to Port B using System	Clock	Gating	Control	Register 5
		SIM_SCGC5 |= 0x400; //Position 10 to HIGH, OR to not erase the whole register
		
		//Set Pin Control Register PORTx_PCRn
		PORTB_PCR19 = 0x100;
		
		//Set Direction Register
		GPIOB_PDDR |= 0x80000;
		
		//LED ON
		GPIOB_PDOR &= ~0x80000; // tilde -> bitwise not operation, and -> prevents setting all the register to high
		for(counter=0;counter<3000000;counter++){}
	   	//LED OFF
		GPIOB_PDOR |= 0x80000;
		for(counter=0;counter<3000000;counter++){}
	}
	
	return 0;
}
