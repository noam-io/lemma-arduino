#include <Arduino.h>
#include "HostLocater.h"
#include <EthernetUdp.h>
#include <string.h>
#include "MessageParser.h"
#include "debug.h"
#include "config.h"

HostLocater::HostLocater( EthernetUDP& udpClient, const char * lemmaId, const char * desiredRoomName ) :
    udpClient( udpClient )
  , guestName(lemmaId)
  , roomName(desiredRoomName)
  , port( 0 )
  , locating( false )
{
  ip[0] = 0;
  lastBroadcastMillis = 0;
}

void HostLocater::begin()
{
  ip[0] = 0;
  port = 0;
  udpClient.begin(1032);
  locating = true;
}

void HostLocater::sendBroadcast()
{
    char marcoMessage[UPD_MAX_PACKET_SIZE]; //128
    snprintf(marcoMessage, UPD_MAX_PACKET_SIZE, "[\"marco\", \"%s\", \"%s\", \"ard_mega\", \"1.1\"]", guestName, roomName);
    DEBUGWRAP( Serial.print("Sending Marco message: "));
    DEBUGWRAP( Serial.println( marcoMessage ));
    IPAddress ipAddr( 255 , 255 , 255 , 255 );
    int messageSize = strlen(marcoMessage);
    udpClient.beginPacket( ipAddr , 1030 );
      int totalSent = udpClient.write((uint8_t*)&marcoMessage[0], messageSize);
      if (totalSent != messageSize) { DEBUGWRAP( Serial.println("Failed to send marco") ); }
    udpClient.endPacket();
}

void HostLocater::tryLocate()
{
  if (!locating) { begin(); }

  if (millis() - lastBroadcastMillis > MARCO_PERIOD) {
    sendBroadcast();
    lastBroadcastMillis = millis();
  }

  if( udpClient.parsePacket() )
  {
    char packet[UPD_MAX_PACKET_SIZE];
    size_t bytesRead = udpClient.read( packet, UPD_MAX_PACKET_SIZE );
    packet[bytesRead] = 0;

    DEBUGWRAP( Serial.print("raw datagram: ") );
    DEBUGWRAP( Serial.println(packet) );

    char name[32]; //Name isn't use other than debug print.  Could save the memory
    if ( MessageParser::parsePolo( &packet[0], name, 32, port ) )
    {
      IPAddress address = udpClient.remoteIP();
      sprintf( ip, "%d.%d.%d.%d", address[0], address[1], address[2], address[3] );

      DEBUGWRAP( Serial.print("Joining room: ") );
      DEBUGWRAP( Serial.println(name) );
      DEBUGWRAP( Serial.print("Host IP: ") );
      DEBUGWRAP( Serial.println(ip) );
      DEBUGWRAP( Serial.print("Host TCP port: ") );
      DEBUGWRAP( Serial.println(port) );
    }
    else
    {
      DEBUGWRAP( Serial.println("not a valid UDP datagram from Noam server broadcast") );
      port = 0;
    }
    locating = false;
    udpClient.stop();
  }
}

bool HostLocater::wasLocated()
{
  return ip[0] != 0;
}

char const * HostLocater::hostIp()
{
  return ip;
}

uint16_t HostLocater::hostPort()
{
  return port;
}
