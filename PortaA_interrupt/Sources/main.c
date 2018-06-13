/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */


#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ISF_SHIFT))&PORT_PCR_ISF_MASK)

volatile int DataReady = 0;

void PORTA_IRQHandler(){
	
	DataReady = 1;	
	
	//Interruption served
	PORTA_PCR19 |= PORT_PCR_ISF(1);
	
	return;
}

int main(void)
{
	//ENABLE PORTA Clock
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	//Clear interrupt IRQC of PORTA19
	PORTA_PCR19 &= ~PORT_PCR_IRQC(0b1111);
	//Interrupt when PORTA19 = 1
	PORTA_PCR19 |= PORT_PCR_IRQC(0b1100);
	
	//Set Pin as GPIO
	PORTA_PCR19 |= PORT_PCR_MUX(1);
	
	//DIRECTION REGISTER, INPUT DEFAULT, NOT NEEDED
	//GPIOA_PDDR = 0 << 19;
	
	//EENABLE PORTA A Interruption (IRQ30) EN0 (ISER[0])
	NVIC_ISER = NVIC_ISER_SETENA(0x40000000);
	
	
	for(;;) {	   
	   if(DataReady){
		   //DO SOMETHING
		   DataReady = 0;
	   }
	}
	
	return 0;
}
