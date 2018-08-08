#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>

#include "tcp.h"

uint16_t rand_port()
{
    time_t tm;
    srand(time(&tm));
    
    return (rand() % (2<<15))+ (2<<15);
}

u_int32_t get_timestamp()
{
    struct timeval tm;
    gettimeofday(&tm,NULL);

    return tm.tv_sec;
}

void tcp_option(const char *packet, int *option_len)
{
    const char *option = packet;
    if(tcp_mss) {
        struct tcp_maxseg *mseg = (struct tcp_maxseg*)option;
        mseg->type = TCPOPT_MAXSEG;
        mseg->len = sizeof(struct tcp_maxseg);
        mseg->maxlen = tcp_mss;
        
        *option_len = mseg->len;

    }else if(tcp_timestamp) {
        struct tcp_tmstamp *tm_stamp = (struct tcp_tmstamp *)option;
        tm_stamp->type = TCPOPT_TIMESTAMP;
        tm_stamp->len = sizeof(struct tcp_tmstamp);
        tm_stamp->send_stamp = get_timestamp();
        tm_stamp->recv_tstamp = 0;

        *option_len = tm_stamp->len;
    } 

}



int transmit_tcp_packet(const char* packet,int *packet_len)
{
    int option_len = 0;
    struct tcphdr *tcp = (struct tcphdr *)packet;
    
    tcp->th_sport = source_port = source_port ? source_port : rand_port();
    tcp->th_dport = dest_port;

    tcp->th_seq = htonl(tcp_seq_num);
    tcp->th_ack = htonl(tcp_ack_num);

    if(fin)
        tcp->th_flags |= TH_FIN;
    if(syn) 
        tcp->th_flags |= TH_SYN;
    if(rst)
        tcp->th_flags |= TH_RST;
    if(push)
        tcp->th_flags |= TH_PUSH;
    if(ack)
        tcp->th_flags |= TH_ACK;
    if(urg)
        tcp->th_flags |= TH_URG;
    if(ece)
        tcp->th_flags |= TH_ECE;
    if(cwr)
        tcp->th_flags |= TH_CWR;

    tcp_option((const char *)(tcp+1), &option_len);

    tcp->th_win = htons(window);
    tcp->th_urp = htons(0);
    tcp->th_sum = 0;
    
    *packet_len = sizeof(struct tcphdr) + option_len;

    if(tcp_offset) {
        tcp->th_offx2 = tcp_offset<<4;
    }else {
        tcp->th_offx2 = ((*packet_len >> 2)<<4);
    }
    
    return 0;
}
