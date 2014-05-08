#ifndef HOST_LOCATER_H
#define HOST_LOCATER_H

#define UPD_MAX_PACKET_SIZE 128
class EthernetUDP;

class HostLocater
{
private:
  EthernetUDP& udpClient;
  char ip[16];
  const char * guestName;
  const char * roomName;
  uint16_t port;

public:
  HostLocater( EthernetUDP& udpClient, const char * guestName, const char * desiredRoomName );

  void begin();
  void tryLocate();
  bool wasLocated();
  char const * hostIp();
  uint16_t hostPort();

private:
  unsigned long lastBroadcastMillis;
  void sendBroadcast();
  bool locating;
};

#endif

