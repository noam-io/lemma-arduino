//Copyright (c) 2014, IDEO 

#include "MockUdpClient.h"

MockUdpClient::MockUdpClient() :
    packet( 0 )
{ }


int MockUdpClient::parsePacket()
{
  int result = 0;
  if( 0 != packet )
  {
    return strlen( packet );
  }
  return result;
}

int MockUdpClient::read( char* buffer, size_t length )
{
  int result = parsePacket();
  if( 0 < result )
  {
    strncpy( buffer, packet, length );
    result = result > length ? result : length;
  }

  return result;
}

IPAddress MockUdpClient::remoteIP()
{
  return ip;
}

