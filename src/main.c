#include "stm32l4xx.h"
#include "user.h"
#include "DConfig.h"
int main(void)
{

  mcoOutputPinEnable();
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
