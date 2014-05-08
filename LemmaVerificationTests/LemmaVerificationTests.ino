#define LEMMADEBUG
#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Lemma.h>

static const long BAUD_RATE = 19200;
static byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xA9, 0x72 };
static char const * lemma_ID = "ArduinoCertificationSuite";

Lemma lemma( lemma_ID, "lemma_verification" );

void echoHandler ( Message const & message )
{
  lemma.speak("EchoVerify", (const char*)message.stringValue);
}

void plusOneHandler ( Message const & message )
{
  lemma.speak("PlusOneVerify", message.intValue + 1);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Lemma Verification Suite...");
  lemma.hear("Echo", echoHandler);
  lemma.hear("PlusOne", plusOneHandler);

  lemma.begin( MAC );
}

void loop() {
  lemma.run();  //Check for lemma events in the loop
}
