/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

volatile unsigned int led_status = 0;

void initRGBLED(void)
{
	//INITIALITZATION
	//R: PORTB18, G: PORTB19, B: PORTD1
	//Enable clock to Port B using System	Clock	Gating	Control	Register 5
	SIM_SCGC5 |= 0x1 << SIM_SCGC5_PORTB_SHIFT; //Position 10 to HIGH, OR to not erase the whole register
	SIM_SCGC5 |= 0x1 << SIM_SCGC5_PORTD_SHIFT;
	
	//Set Pin Control Register --> GPIO
	PORTB_PCR18 = 0x100;
	PORTB_PCR19 = 0x100;
	PORTD_PCR1 = 0x100;
	
	//Set Dir. Register, output
	GPIOB_PDDR |= 0xC0000; //B19, B18
	GPIOD_PDDR |= 0x2; 		//D1	
}

void LEDOn(char rgb){
	switch(rgb){
		case 'R': 
			GPIOB_PDOR &= ~0x1 << 18;
				break;
		case 'G': 
			GPIOB_PDOR &= ~0x1 << 19;
				break;
		case 'B': 
			GPIOD_PDOR &= ~0x1 << 1;
				break;
	}	
}

void LEDOff(char rgb){
	switch(rgb){
		case 'R': 
			GPIOB_PDOR |= 0x1 << 18;
				break;
		case 'G': 
			GPIOB_PDOR |= 0x1 << 19;
				break;
		case 'B': 
			GPIOD_PDOR |= 0x1 << 1;
				break;
	}	
}


int main(void)
{
	initRGBLED();
	LEDOff('R');
	LEDOff('G');
	LEDOff('B');
	
	SYST_CSR = 0x1; //Bit 2 when 0 -> Use system clock divided by 16, Bit 0 when 1 -> Enable Timer
	SYST_CSR |= 0x1 << SysTick_CSR_TICKINT_SHIFT; //Enable Interruptions
	SYST_RVR = 41940000/16-1; //Timer start value
	
	for(;;) {	   

	   	
	}
	
	return 0;
}

void SysTick_Handler(void){
	if(led_status == 1){
		LEDOff('B');
		led_status = 0;
	}else{
		LEDOn('B');
		led_status = 1;
	}
	
}
