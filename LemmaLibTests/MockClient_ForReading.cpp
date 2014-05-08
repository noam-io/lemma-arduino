#include "MockClient_ForReading.h"

MockClient_ForReading::MockClient_ForReading() :
    returnValueIndex( 0 )
{ }

int MockClient_ForReading::read( uint8_t* buffer, size_t size )
{
  char* returnValue = returnValues[ returnValueIndex++ ];

  int nextChunkSize = strlen( returnValue );
  int bytesToCopy = size > nextChunkSize ? nextChunkSize : size;

  strncpy( (char*) buffer, returnValue, nextChunkSize );
  return bytesToCopy;
}
