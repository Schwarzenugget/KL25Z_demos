/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

void initRGBLED_TPM(void)
{
	//INITIALITZATION
	//R: PORTB18, G: PORTB19, B: PORTD1
	//Enable clock to Port B using System	Clock	Gating	Control	Register 5
	//SIM_SCGC5 |= 0x1 << SIM_SCGC5_PORTB_SHIFT; //Position 10 to HIGH, OR to not erase the whole register
	SIM_SCGC5 |= 0x1 << SIM_SCGC5_PORTD_SHIFT;
	
	//Set Pin Control Register --> TPM0_CH1
	//PORTB_PCR18 = 0x100;
	//PORTB_PCR19 = 0x100;
	PORTD_PCR1 = 0x400;
}

void delay(int n){
	int counter;
	for(counter=0;counter<100000*n;counter++){}
}

int main(void)
{
	initRGBLED_TPM();
	
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
	/*Divide Clock by 2^7*/
	TPM0_SC |= 0x7;
	
	/*OC toogle mode*/
	TPM0_C1SC = 0x05 << TPM_CnSC_ELSA_SHIFT;
	/*Clear CHF*/
	TPM0_C1SC |= 0x01 << TPM_CnSC_CHF_SHIFT;
	/*schedule next transition*/
	//TPM0_C1V = TPM0_CNT + 32766; default 0x0
	/*Enable Timer Up-counter timer mode*/
	TPM0_SC |= 0x01 << 3; //Clock Mode Selection
	
	
	for(;;) {	  
	   	while(!(TPM0_C1SC & TPM_CnSC_CHF_MASK)){};
	   	TPM0_C1SC |= 0x01 << TPM_CnSC_CHF_SHIFT;
	   	//TPM0_C1V = TPM0_CNT + 32766;
	   	
	}
	
	return 0;
}
