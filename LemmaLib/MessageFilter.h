#ifndef MESSAGE_FILTER_H
#define MESSAGE_FILTER_H
class Message;
typedef void(*handler_t)(Message const &);

class MessageFilter
{
public:
  MessageFilter();
  ~MessageFilter();

  void add(char * topicName, handler_t callback);
  void handle(Message const &);
  int count();
  char const** getTopicNames();

private:
  char const* topicNames[64];

  typedef struct {
    char * topicName;
    handler_t callback;
  } filter_t;

  filter_t filters[64];
  int nFilters;
};
#endif

