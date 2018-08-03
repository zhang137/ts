#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include "icmp.h"

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

int32_t gettimestamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);

    return tv.tv_sec;
}


void transmit_icmp_packet(const char *packet,int *packet_len)
{

    struct icmphdr *icmp = (struct icmphdr*)packet;
    int data_len = 56;

    if(icmp_gw)
    {
        icmp->type = ICMP_REDIRECT;
        icmp->code = ICMP_REDIR_HOST;
        icmp->un.gateway = redict_gateway;
        
        memset((unsigned char*)icmp + sizeof(struct icmphdr),0x5,sizeof(data_len));

    }else if(icmp_ts)
    {
        icmp->type = ICMP_TIMESTAMP;
        icmp->code = 0;

        int32_t tstamp = gettimestamp();
        memcpy((unsigned char*)icmp + 4,&tstamp,sizeof(int32_t));
        
        memset((unsigned char *)icmp+sizeof(struct icmphdr),0x5,data_len - 8);

    }else if(icmp_addr)
    {
        icmp->type = ICMP_ADDRESS;
        icmp->code = 0;

        icmp->un.echo.id = getpid();
        icmp->un.echo.sequence = 0;
        
        memset((unsigned char *)icmp + sizeof(struct icmphdr),0x5,data_len);

    }else{
        icmp->type = icmp_type;
        icmp->code = icmp_code;

        

    }
    
    *packet_len = sizeof(struct icmphdr) + data_len;

    icmp->checksum = 0;
    icmp->checksum = cksum((uint16_t *)icmp,
            *packet_len);

}


