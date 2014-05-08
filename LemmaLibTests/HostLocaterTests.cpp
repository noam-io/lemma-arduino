#include <Arduino.h>
#include <ArduinoUnit.h>
#include "HostLocater.h"
#include "MockUdpClient.h"

/* TODO: Update these tests to work with new discover protocol */
test( findsHost )
{
  MockUdpClient client;
  client.ip = IPAddress( 4, 3, 6, 8 );
  client.packet = "[Host@9029]";
  HostLocater locater( client, "guest", "room" );
  locater.tryLocate();

  assertTrue( locater.wasLocated() );
  assertTrue( 0 == strcmp( "4.3.6.8", locater.hostIp() ));
  assertTrue( (uint16_t) 9029 == locater.hostPort() );
}

test( doesNotFindHost )
{
  MockUdpClient client;
  HostLocater locater( client, "guest", "room" );
  locater.tryLocate();

  assertTrue( !locater.wasLocated() );
  assertTrue( 0 == strcmp( "", locater.hostIp() ));
  assertTrue( 0 == locater.hostPort() );
}

test( ignoresBadDatagrams )
{
  MockUdpClient client;
  client.packet = "[Host@11";
  HostLocater locater( client, "guest", "room" );
  locater.tryLocate();

  assertTrue( !locater.wasLocated() );
  assertTrue( 0 == strcmp( "", locater.hostIp() ));
  assertTrue( 0 == locater.hostPort() );
}

test( losesHost )
{
  MockUdpClient client;
  client.packet = "[Host@9029]";
  HostLocater locater( client, "guest", "room" );
  locater.tryLocate();
  client.packet = "";
  locater.tryLocate();

  assertTrue( !locater.wasLocated() );
  assertTrue( 0 == strcmp( "", locater.hostIp() ));
  assertTrue( (uint16_t) 0 == locater.hostPort() );
}

