#ifndef LEMMA_CONFIG_H
#define LEMMA_CONFIG_H

#define LISTEN_PORT 9933 //TCP port the lemma listens on
#define HEARTBEAT_PERIOD_MS 3003 //time in ms between heartbeat messages
#define UPD_MAX_PACKET_SIZE 128 //maximum size for udp marcos and polos
#define TCP_READ_TIMEOUT 1000 //time in ms lemma will wait for full message on tcp read
#define LEMMA_DIALECT "arduino" //dialect or device type of the lemma
#define LEMMA_VERSION "0.3" //dialect or device type of the lemma
#define MARCO_PERIOD 2003

#endif
