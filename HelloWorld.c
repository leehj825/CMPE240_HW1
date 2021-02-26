/*
===============================================================================
 Name        : HelloWorld.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdbool.h>

#define GPIO0_LED_PIN       21
#define GPIO0_SWITCH_PIN     3

void initialize(void);
bool get_GPIO0_pin(uint8_t pin);
void set_GPIO0_pin(uint8_t pin, bool on);

int main(void) {


	initialize();

    printf("Hello World\n");
    printf("Hyejun Lee, SID 1254\n");

    bool prev_switch_state = false;

    while(1) {

    	// Read P0.3 pin connected to a switch
    	bool cur_switch_state = get_GPIO0_pin(GPIO0_SWITCH_PIN);

    	// when switch is toggled, different from previous state
    	if (cur_switch_state != prev_switch_state)
    	{

    		printf("switch is toggled %d\n", (uint32_t) cur_switch_state);

    		// save current state
    		prev_switch_state = cur_switch_state;

    		// set P0.21 pin connected to a red LED
    		set_GPIO0_pin(GPIO0_LED_PIN, cur_switch_state);

    	}
    }

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}

void initialize(void)
{
	SystemInit();

	// set GPIO0 P0.21 as output for external Red LED
	LPC_GPIO0->FIODIR |= (1 << GPIO0_LED_PIN);
}

bool get_GPIO0_pin(uint8_t pin)
{
	// if pin is output, exit function
	if ((LPC_GPIO0->FIODIR & (1<<pin)) > 0) return false;

	// get input pin state
	uint32_t pin_state = LPC_GPIO0->FIOPIN & (1<<pin);

	if(pin_state > 0) return true;
	else return false;
}

void set_GPIO0_pin(uint8_t pin, bool on)
{
	// if pin is input, exit function
	if ((LPC_GPIO0->FIODIR & (1<<pin)) == 0) return;

	if (on) {	/* Set pin */
		LPC_GPIO0->FIOPIN |= 1 << pin;
		printf("pin %d is on\n", pin);
	}
	else {	/* Clear pin */
		LPC_GPIO0->FIOPIN &= ~(1 << pin);
		printf("pin %d is off\n", pin);
	}
}

