#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include "icmp.h"
#include "cksum.h"

#define DATALEN 56
#define PING_TYPE 8
#define DEFAULT_CODE 0

int32_t gettimestamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);

    return tv.tv_sec;
}


int transmit_icmp_packet(const char *packet,int *packet_len)
{

    struct icmphdr *icmp = (struct icmphdr*)packet;
    int data_len = DATALEN;

    if(icmp_gw) {
        icmp->type = ICMP_REDIRECT;
        icmp->code = ICMP_REDIR_HOST;
        icmp->un.gateway = redict_gateway;

    }else if(icmp_ts) {
        icmp->type = ICMP_TIMESTAMP;
        icmp->code = DEFAULT_CODE;

        icmp->un.echo.id = getpid();
        icmp->un.echo.sequence = sequence;

        int32_t tstamp = gettimestamp();
        memcpy((unsigned char*)icmp + sizeof(struct icmphdr),&tstamp,sizeof(tstamp));
        
        data_len = data_len -sizeof(tstamp);

    }else if(icmp_addr) {
        icmp->type = ICMP_ADDRESS;
        icmp->code = DEFAULT_CODE;

        icmp->un.echo.id = getpid();
        icmp->un.echo.sequence = sequence;

    }else if(icmp_type != PING_TYPE){
        icmp->type = icmp_type;
        icmp->code = icmp_code;
    } else {
        
        icmp->un.echo.id = getpid();
        icmp->un.echo.sequence = sequence; 
    }
        
    memset((unsigned char*)icmp + sizeof(struct icmphdr),0x5c,sizeof(data_len));
    *packet_len += sizeof(struct icmphdr) + data_len;

    icmp->checksum = 0;
    icmp->checksum = cksum((uint16_t *)icmp,
            *packet_len);

}


