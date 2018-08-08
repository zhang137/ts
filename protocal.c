#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "mydef.h"
#include "util.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"
#include "protocal.h"

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

void send_packet()
{
    
    int packet_len = 0;
    int ret = 0;
    char packet[BUFSIZ];

    parcel_ip_packet(packet,&packet_len);
    
    parcel_proto_packet(packet+packet_len, &packet_len);
    
    if(file_name) {
        ret = read_data(packet + packet_len, data_size);
    }

}

int parcel_proto_packet(const char *pack_data,int *proto_len)
{ 
    
    if(icmp_mode) {
        transmit_icmp_packet(pack_data,proto_len);
    }
    else if(udp_mode) {
        transmit_udp_packet(pack_data,proto_len);
    }
    else {
        transmit_tcp_packet(pack_data,proto_len);
    }

    return 0;
}

void wait_packet()
{

}





