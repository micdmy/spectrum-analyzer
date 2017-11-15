#include "stm32l4xx.h"
#include "user.h"
#include "adc.h"
#include "DConfig.h"
int main(void)
{
	/*
	 * PLL is working, source clock is MSI.
	 * SysClk = 80MHz. MCO available on GPIOA, pin 8 (Nucleo D9 goldpin)
	 */
  mcoOutputPinEnable();
 adcConfig();
  while (1)
  {
  }
  /*
   * Before enabling ADC:
   */
  //ADC->CCR |= ADC_CCR_CKMODE_0; //AHB as a clock source for ADC's
  //ADC-CCR &= ~(ADC_CCR_PRESC); //prescaller for ADC clock set to 1

  //SQR - channel selectino

}
