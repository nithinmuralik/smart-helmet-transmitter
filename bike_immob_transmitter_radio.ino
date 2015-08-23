/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
 * which responds by sending the value back.  The ping node can then see how long the whole cycle
 * took.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(9,10);

// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const int role_pin = 7;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role;
unsigned long previousMillis = 0;  const long interval = 100; int ledState = LOW;         

void setup(void)
{
  //
  // Role
  //

  // set up the role pin
  pinMode(role_pin, INPUT);
  digitalWrite(role_pin,HIGH);
  delay(20); // Just to get a solid reading on the role pin
pinMode(8, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);


digitalWrite(8,1); digitalWrite(4,1); digitalWrite(3,1); 

   digitalWrite(8,0); delay(50);
 
   digitalWrite(8,1); delay(50);
   digitalWrite(4,0); delay(50);
   digitalWrite(4,1); delay(50);

   
   digitalWrite(3,0); delay(50);
   digitalWrite(3,1); delay(50);
   
   digitalWrite(3,0); delay(50);
   digitalWrite(3,1); delay(50);

   digitalWrite(4,0); delay(50);
   digitalWrite(4,1); delay(50);

      digitalWrite(8,0); delay(50);
    digitalWrite(8,1); delay(50);
  // read the address pin, establish our role
  if ( ! digitalRead(role_pin) )
    role = role_ping_out;
  else
    role = role_pong_back;

  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/pingpair/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setPayloadSize(8);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time
  //


    // First, stop listening so we can talk.
    radio.stopListening();

    // Take the time, and send it.  This will block until complete
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    bool ok = radio.write( &time, sizeof(unsigned long) );
    
 
 unsigned long currentMillis = millis();
  
  // put your main code here, to run repeatedly:


////////////////////////////////////////////////////////////////////////////////////low brake
if(analogRead(A2)<=480){




  
     digitalWrite(8,0);digitalWrite(3,0);digitalWrite(4,0);}
else{digitalWrite(8,1);digitalWrite(3,1);digitalWrite(4,1);}

///////////////////////////////////////////////////////////////////////////////////////highbrake
if(analogRead(A2)<=450){





  if(currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:    digitalWrite(ledPin, ledState);
   digitalWrite(8,ledState);digitalWrite(4,ledState);digitalWrite(4,ledState);   
  }

  
}



if(analogRead(A2)<=5){
digitalWrite(8,0);digitalWrite(3,0);digitalWrite(4,0);
  delay(5000);}
  if(analogRead(A1)<=5){
digitalWrite(8,0);digitalWrite(3,0);digitalWrite(4,0);
  delay(5000);}
  if(analogRead(A0)<=5){
digitalWrite(8,0);digitalWrite(3,0);digitalWrite(4,0);
  delay(5000);}
  

 
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
