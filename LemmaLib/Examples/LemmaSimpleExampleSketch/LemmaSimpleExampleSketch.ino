/*

 This Arduino project is a demonstration of the Noam platform's Arduino Lemma Library (Ethernet).
 This project was developed on an Arduino Mega 2560 with Ethernet shield.
 When the Arduino is connected to a Noam network, pushing the buttong will send a signal that is echoed and causes the LED to light up while the button is pressed.
 
 When developing Arduino for Noam, it is important to use an event-centric paradigm.  Using software debounce ensures messages are only sent when the button state changes.
 Keeping delays out of the main loop will ensure fast message response, as new messages are polled in the loop.
 
 Author: Evan Shapiro [ IDEO ]
 
 */

#include <Arduino.h>
#include "SPI.h"    //Ethernet shield uses SPI for communication
#include "EthernetServer.h"   //Need to include arduino ethernet server library
#include "aJSON.h"   //aJSON library used for message formatting
#include "Lemma.h"  //Lemma library

#include "Bounce.h"  //Useful library for button debouncing

//function prototype for polling button status
//function prototype for event handler that's called when 'buttonPressed' message is received
void messageHandler();

static byte MAC[] = { 0xA0, 0xA2, 0xDA, 0x01, 0x7E, 0x59 };  // Network MAC address must be unique on network
//There is a sticker with a guaranteed unique MAC on your Ethernet Arduino or shield
const char * guestName = "uniqueLemmaName";  // The Noam network ID, must be unique on Noam network
const char * roomName = "";  // The Noam network ID, must be unique on Noam network

const int buttonPin = 6;  // Input button pin, connect other side of button to GND
int buttonCount = 0;

Lemma lemma( guestName , roomName );  // Initialize the Arduino Noam Lemma with ID <lemma_ID>

Bounce button(buttonPin , 50);

void setup() {
  Serial.begin( 57600 );  // start serial communication for serial monitor output

  Serial.println("Setup");

  lemma.hear( "buttonMessage", messageHandler );  // Register for Noam 'buttonMessage', call buttonHandler() on new event.

  lemma.begin( MAC );  // start listening on Noam network 1030

  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  lemma.run();      // check for new Noam messages
  button.update();    // check for button state change
  if( button.fallingEdge() ){
    lemma.speak( "buttonMessage" , buttonCount++ );
  }
}

// This callback is called when a new Noam 'buttonPressed' message is detected.
// An Event e is passed to the function - 
    //e has e.intValue, e.floatValue, boolValue and e.stringValue, which are interpreted from then message'JSON list
void messageHandler(Message const & message)
{
  Serial.print("button pressed: "); Serial.println( message.intValue );
}


