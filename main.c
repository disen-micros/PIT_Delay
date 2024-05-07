

#include "PIT.h"
#include "GPIO.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "NVIC.h"


int main(void) {

	uint32_t clock_pit = 0;
	GPIO_init();

	CLOCK_SetSimSafeDivs();

	clock_pit = CLOCK_GetFreq(kCLOCK_BusClk);

	PIT_init(clock_pit);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);

	while(1) {


		if (true == PIT_get_irq_status(PIT_Ch0))
		{
			GPIO_PortToggle(GPIOB,1 << 22 );
			GPIO_PortToggle(GPIOD, 1 << 0);

			PIT_clear_irq_status(PIT_Ch0);
		}

    }
    return 0 ;
}
