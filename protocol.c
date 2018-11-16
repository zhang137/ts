#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "def.h"
#include "util.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"
#include "cksum.h"
#include "protocol.h"

void use_rawip_socket()
{
    send_sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_IP);
    if(send_sockfd < 0) {
        exit(-1);
    }
    
    int rawip = 1;
    if(setsockopt(send_sockfd,SOL_IP,IP_HDRINCL,&rawip,sizeof(rawip))) {
        exit(-1);
    }
    
}

void use_normal_socket()
{
    if(udp_mode) {
        send_sockfd = socket(AF_INET,SOCK_DGRAM,0);
    }
    else {
        send_sockfd = socket(AF_INET,SOCK_STREAM,0);
    }
}


void send_packet_flood()
{
    
    while(1)
    {
        
    }

}

void wait_client_connect()
{
    

}

void scan_host()
{
    

}

void send_packet(int sockfd,const char *buf, int packet_len,
                 int ip_len, int proto_len, int flag)
{
    int ret=0;
    struct sockaddr_in addr;
    memset(&addr, 0,sizeof(addr));

    addr.sin_port = dest_port;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = src_addr;

    if(!icmp_mode) {
        struct pseudoheader pserudo;
        pserudo.source = source_port;
        pserudo.dest = dest_port;
        pserudo.length = sizeof(struct pseudoheader)+ proto_len;
        pserudo.zero = 0;
        if( tcp_mode ) {

            struct tcphdr *tcp = (struct tcphdr *)(buf + ip_len);
            pserudo.protocol = TCP;
        
            tcp->th_sum = cksum((uint16_t *)tcp, pserudo.length);
        }else if(udp_mode) {
            struct udphdr *udp = (struct udphdr *)(buf + ip_len);
            pserudo.protocol = UDP;
        
            udp->cksum = cksum((uint16_t *)udp, pserudo.length);
        }
    } 
   
    struct iphdr *ip = (struct iphdr *)buf;
    ip->iph_off = flag;
    ip->iph_len = packet_len;

    sendto(sockfd,buf, packet_len, 0 , (struct sockaddr*)&addr, sizeof(addr) );
}

int prepare_packet(int sockfd)
{
    int ret = 0;
    int ip_len = 0,proto_len = 0,head_len = 0;
    int fd = 0,data_len = 0,packet_len = 0,send_len=0;
    char packet[BUFSIZ],data_buf[BUFSIZ];

    memset(packet, 0, BUFSIZ);
    memset(data_buf, 0, BUFSIZ);
    
    parcel_ip_packet(packet,&ip_len);
    
    parcel_proto_packet(packet+ip_len, &proto_len);
    
    head_len = packet_len = proto_len + ip_len;

    if(file_name) {
        fd = open_file();
        data_len = getfiledata(fd, data_buf);
        if(data_len < 0) {
            return -1;
        }
    }
    
    if(mtu && data_len + head_len > mtu) 
    {
        send_len = mtu - head_len;
        uint16_t flag = (1<<13);
        while ( data_len > send_len ) {
            
            memcpy(packet + head_len, data_buf, send_len);
            proto_len += send_len;
            packet_len += send_len;
            send_packet(sockfd,packet, packet_len, ip_len, proto_len, 
                        (flag |(packet_len -head_len)));
            data_len -= send_len;
        }
        
        send_packet(sockfd, packet, packet_len, ip_len, proto_len,
                    (0 | (packet_len-head_len)));

    }else  {
        send_packet(sockfd, packet, packet_len, ip_len, proto_len, 0);
    }
}


int parcel_proto_packet(const char *pack_data,int *proto_len)
{ 
    const char *head_data = pack_data;
    int *len = proto_len;

    if(head_data == NULL || len == NULL) {
        return -1;
    }

    if(icmp_mode) {
        transmit_icmp_packet(head_data,proto_len);
    }
    else if(udp_mode) {
        transmit_udp_packet(head_data,proto_len);
    }
    else {
        transmit_tcp_packet(head_data,proto_len);
    }

    return 0;
}

void wait_packet()
{

}





