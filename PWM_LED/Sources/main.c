/*
 * main implementation: use this 'C' sample to create your own application
 *
 */



/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include <math.h>

void delay(int n){
	int counter;
	for(counter=0; counter<100000*n; counter++){};
}

int main()
{
    //MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK; //  INTERNAL CLOCK|MCGIRCLK ACTIVE(SET)
    //MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;   // SELECT FAST INTERNAL REFERENCE CLOCK (1)
   // SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;  // ENABLE TPM2 CLOCK GATE
   // SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);  // MCGIRCLK IS SELECTED FOR TPM CLOCK

    //TPM2_BASE_PTR->SC = TPM_SC_CMOD(0);  // DISABLE EVERY CLOCK
    //TPM2_BASE_PTR->SC |= TPM_SC_PS(0);  // TODO especificar frequencia

    //TPM2_BASE_PTR->MOD = 40000;  // TODO especificar frequencia

    //SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    //PORTB_BASE_PTR->PCR[18] = PORT_PCR_MUX(3);  // TODO especificar multiplexacio del TPM2_CH0

    //TPM2_BASE_PTR->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // SELECT CHANNEL MODE

    //TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD/10;  // TODO especificar duty cycle
    
    //TPM2_BASE_PTR->SC = TPM_SC_CMOD(1);  // COUNTER INC. ON EVERY CLOCK
    
    //LED CONFIG
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTD_PCR1 |= PORT_PCR_MUX(4);
    
    //TPM CONFIG
	/*Enable clock con TPM0*/
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	/*Select clock source*/
	SIM_SOPT2 |= 0x01 << SIM_SOPT2_TPMSRC_SHIFT; //MCGFLLCLK clock
	/*Disable TPM while configuring it*/
	TPM0_SC = TPM_SC_CMOD(0);
	/*TPM Modulo Register */
	TPM0_MOD = 8000; //1sec
	/*Divide Clock by 2^n*/
	TPM0_SC |= TPM_SC_PS(0);
	/*OC toogle mode*/
	TPM0_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; //PWM and Make signal low on match
	/*schedule next transition*/
	TPM0_C1V = 7600; //Duty Cycle 
	/*Enable timer mode*/
	TPM0_SC |= TPM_SC_CMOD(1);
	
	/*PORTD_PCR1 &= ~PORT_PCR_MUX(4);
	PORTD_PCR1 |= PORT_PCR_MUX(1);
	GPIOD_PDDR |= 0x2; 	
	GPIOD_PDOR &= ~0x2;*/

    while(1){
    }
    return 0;
}

/*int main(){
	SIM_BASE_PTR->SCGC5 |= 0x1000;
	PORTD_BASE_PTR->PCR[1] |= 0x0400;
	
	SIM_BASE_PTR->SCGC6 |= 0x01000000;
	SIM_BASE_PTR->SOPT2 |= 0x01000000;
	TPM0_BASE_PTR->SC = 0;
	TPM0_BASE_PTR->CONTROLS[1].CnSC = 0x20 | 0x80;
	TPM0_BASE_PTR->MOD = 43702;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 14568;
	TPM0_BASE_PTR->SC = 0x0C;
	
	while(1){
		
	}
	
	return 0;
	
}*/

void NMI_Handler() {}
void HardFault_Handler() {}
void SVC_Handler() {}
void PendSV_Handler() {}
void SysTick_Handler() {};

void DMA0_IRQHandler() {}
void DMA1_IRQHandler() {}
void DMA2_IRQHandler(){}
void DMA3_IRQHandler(){}
void MCM_IRQHandler() {}
void FTFL_IRQHandler() {}
void PMC_IRQHandler() {}
void LLW_IRQHandler() {}
void I2C0_IRQHandler() {}
void I2C1_IRQHandler() {}
void SPI0_IRQHandler() {}
void SPI1_IRQHandler() {}
void UART0_IRQHandler() {}
void UART1_IRQHandler() {}
void UART2_IRQHandler() {}
void ADC0_IRQHandler() {}
void CMP0_IRQHandler() {}
void FTM0_IRQHandler() {}
void FTM1_IRQHandler(){}
void FTM2_IRQHandler(){}
void RTC_Alarm_IRQHandler(){}
void RTC_Seconds_IRQHandler(){}
void PIT_IRQHandler() {}
void USBOTG_IRQHandler() {}
void DAC0_IRQHandler() {}
void TSI0_IRQHandler() {}
void MCG_IRQHandler() {}
void LPTimer_IRQHandler() {}
void PORTA_IRQHandler() {}
void PORTD_IRQHandler(){}
