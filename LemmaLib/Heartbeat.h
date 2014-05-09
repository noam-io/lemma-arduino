#ifndef HEARTBEAT_H
#define HEARTBEAT_H

class MessageSender;

class Heartbeat
{
  public:
    typedef long unsigned int (* timeFunc_t)();
    Heartbeat(timeFunc_t timeFunc, MessageSender * sender = 0);
    bool readyToBeat();
    void reset();
    bool check();

  private:
    timeFunc_t timeFunc;
    long unsigned int lastHeartbeat;
    MessageSender * sender;
};

#endif
