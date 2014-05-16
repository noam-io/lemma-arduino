//Copyright (c) 2014, IDEO 

#ifndef MOCK_CLIENT_FOR_READING
#define MOCK_CLIENT_FOR_READING

#include <EthernetClient.h>

class MockClient_ForReading : public EthernetClient
{
public:
  char* returnValues[4];
  int returnValueIndex;

  MockClient_ForReading();

  virtual int read( uint8_t* buffer, size_t size );
};

#endif

