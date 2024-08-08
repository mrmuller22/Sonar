#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "protos.h"


/*
Name: Matthew Muller
Date: 3/28/23
Lab 11
*/


void main(void) {
  /* put your own code here */
  
	EnableInterrupts;
	
	// Setting up I/O ports
  // only output atm
  DDRT = 0x40;
  
  // Init our display port
  //DisplayPortInit();
  
  // Init our display
  //DisplayInit();

  // Initializing timer call
  InitTimer();

  for(;;) {
    // Turning off our sonar
    PTT &= ~0x40;
    
    // waiting for push Button to go low
    while(PTIS & 0x10){
      ; // Waiting
    }
    
    // Delay for 10 milliseconds
    Delay(20);
    
    // waiting for push button to go high
    while(!(PTIS & 0x10)){
      ; // Waiting
    }
    
    // Running start Sonar
    StartSonar();
    
    // Running Check Sonar
    CheckSonar();
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}