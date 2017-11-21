#include "stm32l4xx.h"
#include "user.h"
#include "DConfig.h"

#define buffersize 16ul
uint16_t buffer[16];
void fillBufferWith(uint16_t fill) {
	for(unsigned int i=0; i<buffersize; i++) {
		buffer[i] = fill;
	}
}
unsigned int i = 0;
uint32_t temp=0;
int main(void)
{
	mcoOutputPinEnable();
	/*
	 * PLL is working, source clock is MSI.
	 * SysClk = 80MHz. MCO available on GPIOA, pin 8 (Nucleo D9 goldpin)
	 */

	fillBufferWith(0xAA);

	adcConfig();
	//dmaForAdcConfig((uint8_t *) buffer, buffersize);

	//dmaForAdcStart();


	while(1) {
		adcStart();
		while(!(MY_ADC->ISR & ADC_ISR_EOC));
		temp = MY_ADC->DR & 0x00000FFF;
		if(i==buffersize) {
			i=0;
		}
	}




}
