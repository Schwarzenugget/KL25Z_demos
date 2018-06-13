/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

void exercici1(){
	int counter = 0;
	//INITIALITZATION
	//R: PORTB18, G: PORTB19, B: PORTD1
	//Enable clock to Port B using System	Clock	Gating	Control	Register 5
	SIM_SCGC5 |= 0x400; //Position 10 to HIGH, OR to not erase the whole register
	
	//Set Pin Control Register PORTx_PCRn --> GPIO
	PORTB_PCR18 = 0x100;
	
	//Set Direction Register, as output
	GPIOB_PDDR |= 0x40000;
	for(;;) {
			
			//LED ON
			GPIOB_PDOR &= ~0x40000; // tilde -> bitwise not operation, and -> prevents setting all the register to high
			for(counter=0;counter<3000000;counter++){}
		   	//LED OFF
			GPIOB_PDOR |= 0x40000;
			for(counter=0;counter<3000000;counter++){}
		}
}

void delay(int n){
	int counter;
	for(counter=0;counter<100000*n;counter++){}
}

void exercici2(){
	//INITIALITZATION
	GPIOB_PDOR |= 0xC0000; //Green and Red off
	GPIOD_PDOR |= 0x1;      //Blue off
	int counter;
	
	//R: PORTB18, G: PORTB19, B: PORTD1
	//Set clock
	SIM_SCGC5 |= 0x1400;
	
	//Set Pin Control Register --> GPIO
	PORTB_PCR18 = 0x100;
	PORTB_PCR19 = 0x100;
	PORTD_PCR1 = 0x100;
	
	//Set Dir. Register, output
	GPIOB_PDDR |= 0xC0000; //B19, B18
	GPIOD_PDDR |= 0x2; 		//D1
	
	
	//SEMAPHORE
	while(1){
		//GREEN
		GPIOB_PDOR &= ~0x80000; //ON
		delay(30);
		GPIOB_PDOR |= 0x80000; //OF
		
		//BLINK PURPLE
		delay(2);
		for(counter=0; counter < 10; counter++){
			//PURPLE ON
			GPIOB_PDOR &= ~0x40000; //R
			GPIOD_PDOR &= ~0x2; //B
			
			delay(2);
			
			//PURPLE OFF
			GPIOB_PDOR |= 0x40000;  //R
			GPIOD_PDOR |= 0x2;      //B
			
			delay(2);
		}
		
		
		//RED
		GPIOB_PDOR &= ~0x40000; //ON
		delay(30);
		GPIOB_PDOR |= 0x40000; //OF	
	}	
	
}

int main(void)
{
	
	
	//exercici1();
	exercici2();

	
	return 0;
}

