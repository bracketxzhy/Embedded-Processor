#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13



void demo_of_printf_scanf(){
	char rxByte;
	printf("Are you enrolled in ECE 202 (Y or N ):\r\n");
	scanf ("%c", &rxByte);
	if (rxByte == 'N' || rxByte == 'n'){
		printf("You should not be here!!!\r\n\r\n");
	}
	else if (rxByte == 'Y' || rxByte == 'y'){
		printf("Welcome!!! \n\r\n\r\n");
	}
}

	
int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	UART2_Init(); // Communicate with Tera Term
	
	demo_of_printf_scanf();//I suggest you commented this code out!

	// ****************************//
	// USER CODE GOES HERE
	// ****************************//

	// Configure PA5
	
	
	// Configure PC13
	
	
	// Read from PC13 and Set LED light
	// The blue user button is pulled up externally. 
	// The GPIO input is low if the button is pressed down.
	
	
	

}
