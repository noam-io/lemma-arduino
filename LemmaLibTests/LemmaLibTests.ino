#include <aJSON.h>
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#include <ArduinoUnit.h>
#include <Lemma.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Lemma Test Suite...");
  Test::exclude("*");
  Test::include("*Batch1");
}

void loop() {
 Test::run();
}
