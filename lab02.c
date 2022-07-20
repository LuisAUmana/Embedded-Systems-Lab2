#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/adc.h"

#define GreenVoltage 2.8
#define RedVoltage   2.5

// Counter set up
int X;
void SysTickX(void)
{
X++;
}

void Blinking(){
{
while (X < 5)
{
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0X0);
}
while (X <10){
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
}
X = 0;
}
}

//Function to turn on Leds
void RedLed(){
//The X = 0; here will instantly reset the counter in order to better the response of change in voltage
X = 0;
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
}

void GreenLed(){
//The X = 0; here will instantly reset the counter in order to better the response of change in voltage
X = 0;
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 , GPIO_PIN_3);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
}

int
main(void)
{
uint32_t adcValues[1];
volatile float Voltage;
//set the clock frequency to 80 MHz
SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
//set SysTick RELOAD value for a 0.2 s delay
SysTickPeriodSet(16000000);
//enable the SysTick peripheral
SysTickEnable();
SysTickIntRegister(SysTickX);

// Enable the GPIO port that is used for the on-board LED.
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

// Enables the Red and Green LEDs
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_3);

//Enable the ADC functions and get data
GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
ADCSequenceEnable(ADC0_BASE, 3);
ADCIntClear(ADC0_BASE, 3);

//create a while(1) do-forever loop
while(1)
{
ADCProcessorTrigger(ADC0_BASE, 3);
while(!ADCIntStatus(ADC0_BASE, 3, false))
{
}
ADCIntClear(ADC0_BASE, 3);
ADCSequenceDataGet(ADC0_BASE, 3, adcValues);

Voltage = ((float)adcValues[0]) * (3.3/4096.0);

//When voltage is over 2.8v
if(Voltage >= GreenVoltage){
GreenLed();
}
// When voltage is over 2.5v
else if(Voltage >= RedVoltage){
RedLed();
}
//When voltage is below 2.5v
else if(Voltage < RedVoltage){
Blinking();
}
}
}
