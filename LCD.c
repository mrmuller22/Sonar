#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "protos.h"

/*
Name: Matthew Muller
Date: 2/14/23
Lab 06
*/

// Function Bodies

// Display Port Initialization
void DisplayPortInit(){

   // Function to inatialize the ports as outputs
   DDRK |= 0xff;
   
   
   DDRD |= 0xe0;
   

}

// Display Initialization
void DisplayInit(){

   // Variables
   unsigned char arrayInit[7] = {0x30, 0x30, 0x30, 0x38,
                                 0x0f, 0x01, 0x06};
                                
   unsigned long delayCount = 100;
   unsigned char i; 
   
   // For loop to loop through array
   for(i = 0; i < 7; i++){
    
      // Sending array value to function
      SendCommand(arrayInit[i]);
      
      // Calling Delay Function
      Delay(delayCount);
      
   }
   
}

// Send Command Body
void SendCommand(unsigned char cmd){
 
 // Sending Data to PORTK  
 PORTK = cmd;
 
 // Setting Bit6 and Bit5 low of PORTD
 PORTD &= ~0x60;
 
 // Setting Bit7 of PORTD high
 PORTD &= ~0x80;
 
 // Setting Bit7 of PORTD low
 PORTD ^= 0x80;
 
}

// Send Data Body
void SendData(char data){ 

 Delay(20000);

 // Setting Bit5 high of PORTD
 PORTD |= 0x20;

 // Sending Data to PORTK  
 PORTK = data;
 
 // Setting Bit6 low
 PORTD &= 0x40;
 
 // Setting Bit7 of PORTD high
 PORTD &= ~0x80;
 
 // Setting Bit7 of PORTD low
 PORTD ^= 0x80;
 
 Delay(20000);
 
}

// Send Character Body
void SendChar(char *var){

   // While loop to loop through string
   while(*var){
    
    // Calling send data function with char
    SendData(*var++);
      
   }

}