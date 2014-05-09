#include "Lemma.h"
#include <Ethernet.h>
#include "Message.h"
#include "MessageParser.h"
#include "TcpReader.h"

Lemma::Lemma( const char * guestName, const char * desiredRoomName ) :
    server( LISTEN_PORT )
  , udpClient()
  , messageBuilder( guestName )
  , messageSender( guestName, hostConnection )
  , hostLocater( udpClient, guestName, desiredRoomName )
  , _connectedToHost( false )
  , heartbeat(&millis, &messageSender)
{ }

void beginEthernet(unsigned char mac[])
{
  DEBUGWRAP(Serial.println("Obtaining an IP address");)
  int result = Ethernet.begin( mac );
  if( result == 1 )
  {
    DEBUGWRAP(Serial.print("IP address obtained: ");)
    Serial.println(Ethernet.localIP());
  }
  else
  {
    DEBUGWRAP(Serial.println("IP address FAIL");)
  }
}

void Lemma::begin( unsigned char mac[] )
{
  beginEthernet(mac);
  server.begin();
  tryConnectingWithHost();
  updateConnectionStatus();
}

void Lemma::run()
{
  tryConnectingWithHost();
  handleIncomingConnections();
  updateConnectionStatus();
  sendHeartbeat();
}

void Lemma::hear(char * name, handler_t callback)
{
  filter.add(name, callback);
}

void Lemma::tryConnectingWithHost()
{
  if( !isConnected() )
  {
    DEBUGWRAP( Serial.println("Not Connected to Noam server") );
    stopConnection();
    hostLocater.tryLocate();
    if( hostLocater.wasLocated() )
    {
      delay(random(100));
      char const * ip = hostLocater.hostIp();
      unsigned int port = hostLocater.hostPort();
      DEBUGWRAP(Serial.print("Connecting to Noam Host @ ");)
      DEBUGWRAP(Serial.print( ip );)
      DEBUGWRAP(Serial.print( ":" );)
      DEBUGWRAP(Serial.println( port );)
      if( hostConnection.connect( ip, port ) )
      {
        DEBUGWRAP(Serial.println("Connected to Noam server");)
        messageSender.sendRegistration( LISTEN_PORT, filter.getTopicNames(), filter.count(), 0, 0 );
        _connectedToHost = true;
      }
      else
      {
        DEBUGWRAP(Serial.println("Connection to Noam server failed.");)
      }
    }
  }
}

bool Lemma::speak( char const * name, char const * value )
{
  if (!isConnected())
    return false;
  if (!messageSender.sendMessage( name, value ))
  {
    stopConnection();
    return false;
  }
  return postSendMessage();
}

bool Lemma::speak( char const * name, int value )
{
  if (!isConnected())
    return false;
  if (!messageSender.sendMessage( name, value ))
  {
    stopConnection();
    return false;
  }
  return postSendMessage();
}

bool Lemma::speak( char const * name, unsigned long value )
{
  if (!isConnected())
    return false;
  if (!messageSender.sendLongMessage( name, value ))
  {
    stopConnection();
    return false;
  }
  return postSendMessage();
}

bool Lemma::speak( char const * name, double value )
{
  if (!isConnected())
    return false;
  if (!messageSender.sendDoubleMessage( name, value ))
  {
    stopConnection();
    return false;
  }
  return postSendMessage();
}

void Lemma::handleIncomingConnections()
{
  if ( !isConnected() ) {
    return;
  }

  EthernetClient incomingClient = server.available();
  if( incomingClient == true )
  {
    TcpReader reader( incomingClient );
    char* messageBytes = reader.read();
    if (messageBytes != 0)
    {
      Message const & message = MessageParser::parse( messageBytes );
      filter.handle( message );
      free( messageBytes );
    }
  }
}

void Lemma::stopConnection(){
  hostConnection.stop();
  _connectedToHost = false;
}

void Lemma::updateConnectionStatus(){
  _connectedToHost = hostConnection.connected();
}

bool Lemma::isConnected(){
  return _connectedToHost;
}

bool Lemma::postSendMessage(){
  //place to do stuff after successfully sending a message
  heartbeat.reset();
  return true;
}

void Lemma::sendHeartbeat(){
  if( !isConnected() ){
    return;
  }
  if( !heartbeat.check() ){
    stopConnection();
  }
}

