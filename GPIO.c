/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	19/02/2021
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include <stdbool.h>

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};


void PORTC_IRQHandler(void)
{
	g_intr_status_flag.flag_port_c = true;
	GPIO_PortClearInterruptFlags(GPIOC, 0xFFFF);

}


void PORTA_IRQHandler(void)
{
	g_intr_status_flag.flag_port_a = true;
	GPIO_PortClearInterruptFlags(GPIOA, 0xFFFF);
}

void GPIO_init(void)
{

	gpio_pin_config_t gpio_output_config = {
			        kGPIO_DigitalOutput,
			        1,
			    };

	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortD);

	PORT_SetPinMux(PORTB, 22u, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, 22u, &gpio_output_config);

	PORT_SetPinMux(PORTD, 0u, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOD, 0u, &gpio_output_config);


}


void GPIO_clear_irq_status(gpio_name_t gpio)
{
	if(GPIO_A == gpio)
	{
		g_intr_status_flag.flag_port_a = false;
	}
	else
	{
		g_intr_status_flag.flag_port_c = false;
	}
}

uint8_t GPIO_get_irq_status(gpio_name_t gpio)
{
	uint8_t status = 0;

	if(GPIO_A == gpio)
	{
		status = g_intr_status_flag.flag_port_a;
	}
	else
	{
		status = g_intr_status_flag.flag_port_c;
	}

	return(status);
}

