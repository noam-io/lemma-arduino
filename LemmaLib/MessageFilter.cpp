#include "MessageFilter.h"
#include "Message.h"
#include <stdlib.h>
#include <string.h>

MessageFilter::MessageFilter() : nFilters(0)
{
}

MessageFilter::~MessageFilter()
{
  for(int i = 0; i < nFilters; i++)
  {
    free(filters[i].topicName);
  }
}

void MessageFilter::add(char * topicName, handler_t callback)
{
  int filterNumber = nFilters++;
  filters[filterNumber].topicName = (char *)malloc(strlen(topicName) + 1);
  strcpy(filters[filterNumber].topicName, topicName);
  filters[filterNumber].callback = callback;

  topicNames[filterNumber] = filters[filterNumber].topicName;
}

void MessageFilter::handle(Message const & message)
{
  for(int i = 0; i < nFilters; i++)
  {
    if (strcmp(message.topicName, filters[i].topicName) == 0)
    {
      filters[i].callback(message);
    }
  }
}

int MessageFilter::count()
{
  return nFilters;
}

char const** MessageFilter::getTopicNames()
{
  return topicNames;
}

