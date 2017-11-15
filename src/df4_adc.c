#include <stm32f4xx.h>
#include <df4_adc.h>
#include <stdint.h>





void df4AdcInit(void) {

	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN | RCC_APB2ENR_ADC2EN | RCC_APB2ENR_ADC3EN ;   //ADCCLK ENABLE

	//dla wszystkich ADC:
	//ADC->CCR|=ADC_CCR_ADCPRE;							//11->preskaler na 8 czyli:ADCCLK  =72 / 8 =9Mhz
														//00->preskaler na 2 czyli 36 Mhz
	ADC->CCR|= ADC_CCR_DDS 	  //countinuous DMA request
			| ADC_CCR_DMA_1   //DMA for tripple interleaved ADC
			| ADC_CCR_MULTI_0 //tripple interleaved mode
			| ADC_CCR_MULTI_1
			| ADC_CCR_MULTI_2
			| ADC_CCR_MULTI_4
			| ADC_CCR_DELAY_1 // 15 ADCclk delay beetwen sampling (ma byc rowny lub wiekszy niz sampling time)
			| ADC_CCR_DELAY_3;


	//dla wybranego adc:

	ADC1->CR1&=~ADC_CR1_RES;				//12b mode, 12 cycles conv czyli: fs=9Mhz/(15+12) //12-bitow, 15-samplig time
	ADC2->CR1&=~ADC_CR1_RES;
	ADC3->CR1&=~ADC_CR1_RES;

	ADC1->CR2=ADC2->CR2=ADC3->CR2=
			  ADC_CR2_CONT
			|  ADC_CR2_EOCS;		//EOC set on end of regular conversion


	ADC1->SQR3=ADC2->SQR3=ADC3->SQR3=1ul;//kanal 1(PA1) pierwszy w kolejce do konwersji

	ADC1->SMPR2=ADC2->SMPR2=ADC3->SMPR2=  ADC_SMPR2_SMP1_0 ;//samping time =15 cycles
	
	//INTERRUPTS:
	ADC1->CR1|=ADC2->CR1|=ADC3->CR1|=ADC_CR1_OVRIE;				//overrun error
	NVIC_EnableIRQ(ADC_IRQn);				//interrupt ON
	NVIC_SetPriority(ADC_IRQn, 2);			//priority
	
	ADC1->CR2|=ADC2->CR2|=ADC3->CR2|=ADC_CR2_ADON;					//ADC ON
}

inline void df4AdcContOn (void) {
	ADC1->CR2|=ADC2->CR2|=ADC3->CR2|=
			  ADC_CR2_CONT 				//continuous conversion mode
			| ADC_CR2_SWSTART;			//start conversion
}

inline void df4AdcSingleConversionOn(void){
	ADC->CCR&=~(ADC_CCR_DMA | ADC_CCR_MULTI);
	ADC1->CR1&=~(ADC_CR1_EOCIE);
	ADC1->CR1|= ADC_CR1_DISCEN;
}
inline uint16_t df4AdcSingleConversion(void){
	ADC1->CR2&=~ADC_CR2_SWSTART;
	ADC1->CR2|=ADC_CR2_SWSTART;
	while(!(ADC1->SR & ADC_SR_EOC));
	return ADC1->DR;
}
inline void df4AdcSingleConversionOff(void){
	ADC->CCR|=(ADC_CCR_DMA | ADC_CCR_MULTI);
	ADC1->CR1|=(ADC_CR1_EOCIE);
	ADC1->CR1&=~ADC_CR1_DISCEN;
	ADC1->CR2&=~ADC_CR2_SWSTART;
}
//inline void df4AdcTim2On(void) {
//	//adc->CR2|=ADC_CR2_EXTEN_0; 			//external trigger rising edge TIM2
//}

inline void df4AdcStop(void){
	ADC1->CR2&=ADC2->CR2&=ADC3->CR2&=
			  ~(  ADC_CR2_CONT				//stop continuous conversion mode
			    | ADC_CR2_SWSTART);			//toogle start bit
}
inline void df4AdcSetDelay(uint32_t delay){
	ADC->CCR&=~ADC_CCR_DELAY;
	ADC->CCR|=delay;
}
inline void df4AdcSetSmplTime(uint32_t smplTime){
	ADC1->SMPR2=ADC2->SMPR2=ADC3->SMPR2=smplTime;
}
inline void df4AdcSetResolution(uint32_t res){
	ADC1->CR1=ADC2->CR1=ADC3->CR1&=~ADC_CR1_RES;
	ADC1->CR1=ADC2->CR1=ADC3->CR1|=res;
}
