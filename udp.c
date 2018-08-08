#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "mydef.h"
#include "udp.h"
#include "cksum.h"


uint16_t rand_port()
{
    time_t tm;
    srand(time(&tm));
    
    return (rand() % (2<<15))+ (2<<15);
}


int transmit_udp_packet(const char* packet,int *packet_len)
{
    struct udphdr *udp = (struct udphdr *)packet; 
    
    udp->sport = source_port = source_port ? source_port : rand_port();
    udp->dport = dest_port; 
    udp->len = sizeof(struct udphdr);
    udp->cksum = 0;
    
    *packet_len += udp->len;

    return 0;
}


