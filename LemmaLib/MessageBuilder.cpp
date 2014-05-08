#include "MessageBuilder.h"
#include <aJSON.h>
#include "Arduino.h"
#include "config.h"

static void add(aJsonObject* root, char const * string)
{
  aJsonObject* item = aJson.createItem(string);
  aJson.addItemToArray(root, item);
}

static void add(aJsonObject* root, int number)
{
  aJsonObject* item = aJson.createItem(number);
  aJson.addItemToArray(root, item);
}

static void addLong(aJsonObject* root, unsigned long int number)
{
  unsigned long int tempNum = number;
  aJsonObject* item = aJson.createItem((int)tempNum);
  aJson.addItemToArray(root, item);
}

static void addDouble(aJsonObject* root, double number)
{
  double tempNum = number;
  aJsonObject* item = aJson.createItem(tempNum);
  aJson.addItemToArray(root, item);
}

static void add(aJsonObject* root, char const** values, int size )
{
  aJsonObject* result = aJson.createStringArray( values, size );
  aJson.addItemToArray(root, result);
}

MessageBuilder::MessageBuilder( char const * id) :
  guestName(id)
{
}

char * MessageBuilder::buildMessage(  char const * topicName, char const * value ) const
{
  aJsonObject *  root = aJson.createArray();

  add( root, "event" );
  add( root, guestName );
  add( root, topicName );
  add( root, value );

  char * string = aJson.print(root);
  aJson.deleteItem(root);
  return string;
}

char * MessageBuilder::buildMessage(  char const * topicName, int value ) const
{
  aJsonObject *  root = aJson.createArray();

  add( root, "event" );
  add( root, guestName );
  add( root, topicName );
  add( root, value );

  char * string = aJson.print(root);
  aJson.deleteItem(root);

  return string;
}

char * MessageBuilder::buildLongMessage(  char const * topicName, long unsigned int value ) const
{
  aJsonObject *  root = aJson.createArray();

  add( root, "event" );
  add( root, guestName );
  add( root, topicName );
  addLong( root, value );

  char * string = aJson.print(root);
  aJson.deleteItem(root);
  return string;
}

char * MessageBuilder::buildDoubleMessage(  char const * topicName, double value ) const
{
  aJsonObject *  root = aJson.createArray();

  add( root, "event" );
  add( root, guestName );
  add( root, topicName );
  addDouble( root, value );

  char * string = aJson.print(root);
  aJson.deleteItem(root);
  return string;
}

char * MessageBuilder::buildRegister( int port, char const** hears, int hearsSize, char const** speaks, int speaksSize ) const
{
  aJsonObject* root = aJson.createArray();
  aJsonObject* optionsObj;

  add(root, "register");
  add(root, guestName);
  add(root, port);
  add(root, hears, hearsSize);
  add(root, speaks, speaksSize);
  add(root, LEMMA_DIALECT );
  add(root, LEMMA_VERSION );
  aJson.addItemToObject(root, "optionsObj", optionsObj = aJson.createObject());
  aJson.addNumberToObject(optionsObj, "heartbeat", ((float)HEARTBEAT_PERIOD_MS / 1000) );

  char* string = aJson.print( root );
  aJson.deleteItem(root);

  return string;
}

char * MessageBuilder::buildHeartbeat() const{
  aJsonObject *  root = aJson.createArray();
  add( root, "heartbeat" );
  add( root, guestName );
  char * string = aJson.print(root);
  aJson.deleteItem(root);
  return string;
}

