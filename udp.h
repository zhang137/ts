#ifndef UDP_H 
#define UDP_H 

#include "mydef.h"

__BEGIN_DECLS 

struct udphdr
{
  u_int16_t sport;
  u_int16_t dport;
  u_int16_t len;
  u_int16_t cksum;
};


struct udp_pseudoheader
{
    u_int32_t source;
    u_int32_t dest;
    u_int8_t zero;
    u_int8_t protocol;
    u_int16_t length;
};

__END_DECLS 



int transmit_udp_packet(const char* packet,int *packet_len);


#endif // UDP_H 
