#ifndef UDP_H 
#define UDP_H 

#include "def.h"


struct udphdr
{
  u_int16_t sport;
  u_int16_t dport;
  u_int16_t len;
  u_int16_t cksum;
};


int transmit_udp_packet(const char* packet,int *packet_len);


#endif // UDP_H 
