#include <ArduinoUnit.h>
#include "TcpReader.h"
#include "MockClient_ForReading.h"

test( zeroLengthBatch1 ) {
  MockClient_ForReading client;
  TcpReader reader( client );
  client.returnValues[0] = "000000";

  char* actual = reader.read();
  assertTrue( 0 == strcmp( "", actual ));
  free( actual );
}

test( lengthOneBatch1 ) {
  MockClient_ForReading client;
  TcpReader reader( client );
  client.returnValues[0] = "000001";
  client.returnValues[1] = "a";

  char* actual = reader.read();
  assertTrue( 0 == strcmp( "a", actual ));
  free( actual );
}

test( readsChunksBatch1 ) {
  MockClient_ForReading client;
  TcpReader reader( client );
  client.returnValues[0] = "00";
  client.returnValues[1] = "0012";
  client.returnValues[2] = "Hello";
  client.returnValues[3] = " there!";

  char* actual = reader.read();
  assertTrue( 0 == strcmp( "Hello there!", actual ));
  free( actual );
}

