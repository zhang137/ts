#ifndef UDP_H 
#define UDP_H 

#include "mydef.h"

__BEGIN_DECLS 

struct udphdr
{
  u_int16_t source;
  u_int16_t dest;
  u_int16_t len;
  u_int16_t check;
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



void transmit_udp_packet(const char* packet,int *packet_len);


#endif // UDP_H 
