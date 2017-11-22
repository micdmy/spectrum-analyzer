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

uint8_t toSend[5] ={'S','T','M','3','2'};

int main(void)
{
	mcoOutputPinEnable();
	/*
	 * PLL is working, source clock is MSI.
	 * SysClk = 80MHz. MCO available on GPIOA, pin 8 (Nucleo D9 goldpin)
	 */

	fillBufferWith(0xAA);

	adcConfig();
	dmaForAdcConfig((uint8_t *) buffer, buffersize);
	DusartConfig();

	dmaForAdcStart();
	adcStart();

	while(1) {
		if(usartRec[(recNum-1) & (USART_REC_L-1)] == 't') {
			usartRec[(recNum-1) & (USART_REC_L-1)] = 0;
			DusartSendViaInterrupts(toSend, 5);
		}
	}




}
