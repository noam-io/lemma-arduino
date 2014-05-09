#include "Heartbeat.h"
#include "config.h"
#include "debug.h"
#include "MessageSender.h"

Heartbeat::Heartbeat(timeFunc_t _timeFunc, MessageSender * sender)
: timeFunc(_timeFunc)
, lastHeartbeat(0)
, sender(sender){

}
void Heartbeat::reset(){
  lastHeartbeat = timeFunc();
};

bool Heartbeat::readyToBeat(){
  if( timeFunc() - lastHeartbeat > HEARTBEAT_PERIOD_MS ){
    reset();
    return true;
  }
  return false;
}

bool Heartbeat::check()
{
  if (readyToBeat())
  {
    return sender->sendHeartbeat();
  }
  return true;
}
