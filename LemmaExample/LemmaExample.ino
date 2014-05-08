#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Lemma.h>

static const long BAUD_RATE = 115200;

//set MAC address from sticker on your board
static byte MAC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
static char const * lemma_ID = "ArduinoExample";
Lemma lemma( lemma_ID, "" );

int intValue = 0;
long lastMillis = 0;

void handler1 ( Message const & message )
{
  //Handle One Message
}

void handler2 ( Message const & message )
{
  //Handle Two Message
}

void setup() {
  Serial.begin(BAUD_RATE);
  lemma.hear("One", handler1);
  lemma.hear("Two", handler2);
  lemma.begin( MAC );
}

void loop() {
  lemma.run();
  //avoid calls to delay in loop!  Keep track of time instead
  if (millis() - lastMillis > 2000)
  {
    intValue++;
    lemma.speak("Count", intValue);
    lastMillis = millis();
  }
}

