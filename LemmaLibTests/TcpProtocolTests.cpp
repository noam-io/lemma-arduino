//Copyright (c) 2014, IDEO 

#include <stdlib.h>
#include <string.h>
#include <ArduinoUnit.h>
#include "TcpProtocol.h"

test( includesLengthOfMessageBatch1 ) {
  char* encoded = TcpProtocol::encode( "abcdefg" );
  assertTrue( 0 == strcmp( "000007abcdefg", encoded ));
  free( encoded );
}

