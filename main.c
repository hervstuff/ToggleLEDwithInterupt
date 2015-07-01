#include <msp430g2553.h>
/*This is the header file.
 *This file contains predefined keywords and allows us to use keywords such as BIT0 to represent binary 00000001 and save time.
 */

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; 			// Stop watchdog timer
	/*
	 *This is explained in the hervstuff/PushButtonDownGreenLEDOn/main.c.
	 */

	P1DIR |= BIT0; 					// Set P1.0 to output direction
	/*BIT0 is predefined as 00000001.
	 *The "|=" bit wise operator "OR EQUALS" P1DIR with 00000001.
	 *P1DIR is initially 00000000, when OR EQUALS with 00000001, the result is 00000001.
	 *This means that Port 1.0 is set to output. The least significant bit is Port 1.0 and the most significant is Port 1.7.
	 *To understand the pin functions, refer to the MIXED SIGNAL MICROCONTROLLER manual table 16 on port pin functions
	 */which is what I am using to set up the direction of input/output.
	 
	P1OUT &= ~BIT0; 			     	// Set the red LED on
  /*BIT0 is predefined as 00000001.
	 *The "~" operator infront of BIT0 means that "~BIT0" = 11111110.
	 */P1OUT is "AND EQUALS to 11111110 which flips the digits again and makes it 00000001 and turns Port 1.0 into a output.
	TACCR0 = 6000;					// Count limit (16 bit)
	/*TACCR0 is a 16 bit register meaning it can store a binary value of 1111 1111 1111 1111 or 32768 in decimal.
	 *TACCR0 has two modes. In compare mode, we use TA0CCR0 to hold a value which we will use to compare to the value in
	 *Timer_A register TAR.
	 *In capture mode, Timer_A register TAR is copied into the TACCR0 register.
	 */Use MSP430x2xx Family User's Guide section 12 to understand the bit functions of timers.

	TACCTL0 = 0x10;					// Enable counter interrupts, bit 4=1 or 1000 in binary
	/*TACCTLx is the capture/compare control register and it holds 16 bits. The bit we are setting to high is the 
	 */capture/compare interrupt enable bit or CCIE which enables the interrupt request of the corresponding CCIFG flag.

	TACTL = TASSEL_1 + MC_1; 			// Timer A 0 with ACLK @ 12KHz, count UP
	/*TACTL is the Timer_A control register and holds 16 bits.
	 *TASSEL_1 are bits 8-9 inside the TACTL control register. When we add the "_1" behind "TASSEL", we are saying that
	 *we want to set the Timer_A clock source select to be "01" which is the ACLK.
	 *ACLK stands for auxillary clock.
	 *MC is the mode control bits 4-5 inside of the TACTL control register. By adding "_1" behind MC, we are telling
	 *the telling the MC to set the mode to up mode and count towards TACCR0.
	 *TASSEL_1 and MC_1 are predefined in the msp430g2553.h header file. The logic behind using "_0", "_1", "_2", "_3"
	 *is that it allows us to shorthand "_0" as bits 00, "_1" bits 01, "_2" bits 10, "_3" bits 11.
	 */If you were to use octal, MC_0 would be "0*0x10u", MC_1 would be "1*0x10u", etc; "u" means unsigned.

	_BIS_SR(LPM0_bits + GIE); 	          // LPM0 (low power mode) with interrupts enabled
}
  /*
	 *
	 /

#pragma vector=TIMER0_A_VECTOR
   __interrupt void Timer_A (void) {		// Timer A interrupt service routine
   /*
	 *
	 /

	P1OUT ^= BIT0;						// Toggle red LED
	/*
	 *
	 /
}
