/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

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

void delay(int n){
	int counter;
	for(counter=0;counter<100000*n;counter++){}
}

int main(void)
{
	int i;
	initRGBLED();
	LEDOff('R');
	LEDOff('G');
	LEDOff('B');
	
	/*Enable clock con TPM0*/
	SIM_SCGC6 |= 1 << SIM_SCGC6_TPM0_SHIFT; 
	/*Select clock source*/
	SIM_SOPT2 |= 0x01 << SIM_SOPT2_TPMSRC_SHIFT; //MCGFLLCLK clock
	/*Disable TPM while configuring it*/
	TPM0_SC = 0x0;
	/*TPM Modulo Register set to max*/
	TPM0_MOD = 0xFFFF;
	/*Clear Timer Overflow Flag*/
	TPM0_SC |= 0x1 << 7;
	/*Divide Clock by 2^1*/
	TPM0_SC |= 0x1;
	/*Enable Timer Up-counter timer mode*/
	TPM0_SC |= 0x01 << 3; //Clock Mode Selection
	
	
	
	
	for(;;) {	  
	   	LEDOn('B');
		for(i=0; i< 320; i++){
			while((TPM0_SC & 1 << 7) == 0){};
			/*Clear Timer Overflow Flag*/
			TPM0_SC |= 0x1 << 7;
		}
	   	LEDOff('B');
		for(i=0; i< 320; i++){
			while((TPM0_SC & 1 << 7) == 0){};
			/*Clear Timer Overflow Flag*/
			TPM0_SC |= 0x1 << 7;
		}
	   	
	}
	
	return 0;
}
