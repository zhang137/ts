#include <stdio.h>
#include <unistd.h>
#include "udp.h"

uint16_t cksum(uint16_t *packet, int size_len)
{
    uint32_t sum = 0;
    
    while(size_len > 1)
    {
        sum += *packet++;
        size_len --;
    }

    if(size_len == 1)
    {
        sum += *((uint8_t *)packet); 
    }

    sum += (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return ~(uint16_t)sum;
}

void transmit_udp_packet(const char* packet,int *packet_len)
{

}
