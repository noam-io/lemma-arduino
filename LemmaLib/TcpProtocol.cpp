#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TcpProtocol.h"

char* TcpProtocol::encode( char const * message )
{
  int messageLength = strlen( message );
  char* result = (char*) malloc( messageLength + 7 );

  sprintf( result, "%06d%s", strlen( message ), message );
  return result;
}

