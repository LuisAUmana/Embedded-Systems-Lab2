# Embedded-Systems-Lab2
This project was performed using a board EK-TM4C123GXL and Energia IDE
Objective
For this lab we will be developing an application to monitor the voltage level of a battery and provide LED feedback indicating the battery's level. As a battery's charge depletes, the output voltage will begin to drop. Usually an application or device will have a defined range of voltages that the device can operate normally within. Once it has dropped below the estimated threshold, a warning of some kind is produced to alert the user that it is time to recharge. Here, our warning will be produced using the LEDs. The LED will display green if the battery is well within operating voltage, red if low, and blinking red if critically low. The "battery" level will be simulated by using a potentiometer and bread board.

Materials and Resources
For this lab you will need:

TM4C123GXL Development Board
5K Potentiometer (502 9L)
Breadboard
Male to Female or Male to Male Jumper Wires
Schematic of the connection (Will be labelled as Battery Level Indicator Schematic)

Procedure
In this lab we will be setting an LED to indicate the voltage level of a battery. The voltage level of the battery is simulated by the potentiometer's output. When the voltage is above 2.8 V, the LED should be set to green. When the voltage is below 2.8 V, but above 2.5, the LED should be set to red, and when the voltage is below 2.5 V, the LED should blink red at a rate of approximately 1 second (1 second on, 1 second off).

Clone or import the "blinky" example code and remove all lines pertaining to the blinking LED demo function.

Add the ADC TivaWare header file to your source file (#include "driverlib/adc.h").

Initialize the peripherals:
-Configure the system clock (Note that the PLL will need to be configured for the ADC)
-Configure the GPIO
-Configure the ADC

Create a state machine for selecting between the LED functions. How many states should there be? What should be the inputs to the states? Consider how you can structure this state machine to maximize responsiveness. Try to avoid including any loops within your state machine's individual states.

Create a function for sampling the ADC that will return the converted voltage value.

Create a function for setting the LED. Can you make one function that sets the LED appropriately for all states?

Requirements
The LED changes color according to the specified voltage thresholds.
-Green when voltage is above 2.8 V
-Red when voltage is below 2.8 V but greater than 2.5 V
-Blinking Red when voltage is below 2.5 V at a rate of 1s (1s on, 1s off)

The code is designed to be as responsive as possible (no stalling loops within function calls)
