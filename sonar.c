#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include "derivative.h" /* derivative-specific definitions */
#include "protos.h"


/*
Name: Matthew Muller
Date: 3/28/23
Lab 11
*/

// File for Sonar

// Variable Decleration 
volatile unsigned int start;
volatile unsigned int received;
volatile unsigned int realCount;
volatile unsigned int time;
volatile unsigned int speed;
volatile unsigned int distance;
volatile unsigned int returnDistance;
unsigned int feet;
char buffer[32];


// Initialize timer
void InitTimer(void){
  
  // Enabling the timer
  ECT_TSCR1 |= 0x80;
  
  // Setting channels 6 and 7 as input capture
  ECT_TIOS_IOS6 = 0;
  ECT_TIOS_IOS7 = 0;
 
  // Setting channel 6 as rising edge
  ECT_TCTL3_EDG6A = 1;
  ECT_TCTL3_EDG6B = 0;
  
  // Setting channel 7 as rising edge
  ECT_TCTL3_EDG7A = 1;
  ECT_TCTL3_EDG7B = 0;
  
  // Setting our pre scaler setting
  ECT_TSCR2 = 0x03;  
}

// Delay Function
void Delay(unsigned long dc){
  
  // While loop to decrement delay
  while(dc > 0){
    
    // Decrementing long
    dc--;
  }
}

// Sonar Start Function
void StartSonar(void){

  // Reset counter of bit 6
  ECT_TFLG1_C6F = 1;
  
  // Reset coutner of bit 7
  ECT_TFLG1_C7F = 1;
  
  // Turn on Sonar Speaker
  PTT = 0x40;
  
}

// Sonar Check Function
void CheckSonar(void){
  
  // Waiting for bit 7 to return low
  while(!(ECT_TFLG1_C7F)){
    ; // Waiting  
  }
  
  // Setting Start val to variable
  start = ECT_TC6;
  
  // Setting Return val to variable
  received = ECT_TC7;
  
  // Calculating the time
  if(start > received){
   
    // adjust count for roll over
    realCount = ((65,535 - start) + received)/2;
   
    
  } 
  
  // Else timer did not roll over 
  else{
    
    // Calculating count
    realCount = (received - start)/2;
    
  }
  
  // Running Conversion Function
  returnDistance = Conversion(realCount);
  
  feet = returnDistance / 12;
  
  sprintf(buffer, "D=% Feet %d Inches", feet, returnDistance);
  
  //sendChar(buffer);
}

// Conversion Function
unsigned int Conversion(volatile unsigned int rc){
  
  time = rc / 1000000;
  
  speed = 1116 * 12;
  
  distance = speed * time;  
  
  return distance;
}