#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#include "mydef.h"
#include "ip.h"



int rand_ip_id()
{
    time_t tm;
    srand(time(&tm));

    return rand()%65536;
}


uint32_t rand_ipaddr(int type)
{

    return 0; 
}

int ip_opt(const char *ip_opt, int *opt_len)
{
    const char *data = ip_opt;
    
    struct ip_noop *noop = (struct ip_noop*)data;
    noop->type = IPOPT_NOP;

    if(ip_rroute)
    {
        struct ip_rr *rr = (struct ip_rr*)(noop+1);
        memset(rr,0,sizeof(struct ip_rr));

        rr->ipr_type = IPOPT_RR;
        rr->ipr_len = sizeof(struct ip_rr);
        rr->ipr_ptr = 4;
        *opt_len = rr->ipr_len + sizeof(struct ip_noop);    
   
    }else if(lsrr_route)
    {
        int arg_num = 0;
        struct ip_lsrr *lsrr_option = (struct ip_lsrr*)(noop+1);
        lsrr_option->ipl_type = IPOPT_LSRR;
        lsrr_option->ipl_ptr = 4;
        
        while(route_data[arg_num])
        {
            lsrr_option->ipl_data[arg_num] = route_data[arg_num];
            arg_num++;
        }
        lsrr_option->ipl_len = 3 + arg_num *sizeof(uint32_t);
        *opt_len = lsrr_option->ipl_len + sizeof(struct ip_noop);    
    }else if(ssrr_route)
    {
        int arg_num = 0;
        struct ip_ssrr *ssrr_option = (struct ip_ssrr*)(noop+1);
        ssrr_option->ips_type = IPOPT_LSRR;
        ssrr_option->ips_ptr = 4;
        
        while(route_data[arg_num])
        {
            ssrr_option->ips_data[arg_num] = route_data[arg_num];
            arg_num++;
        }
        
        ssrr_option->ips_len = 3 + arg_num *sizeof(uint32_t);
        *opt_len = ssrr_option->ips_len + sizeof(struct ip_noop);    

    }
    return 0;
}



void parcel_ip_packet(const char *packet,int *packet_len)
{
    int opt_len,ip_len;
    struct iphdr *ip = (struct iphdr *)packet;
    ip->iph_version = 4;
    
    ip->iph_id = rand_ipid ? rand_ip_id() : ip_id;
    if( ip->iph_id < 0 || ip->iph_id > 65535)
    {
        if(debug)
        {
            ;
        }
        ip->iph_id = rand_ip_id();
    }

    ip->iph_ttl = (ttl > MAXTTL && ttl <  1) ? IPDEFTTL : ttl;
    
    if(tcp_mode || scan_mode)
        ip->iph_proto = TCP;
    else if(icmp_mode)
        ip->iph_proto = ICMP;
    else 
        ip->iph_proto = UDP;
   
    ip->iph_tos = tos;
    ip->iph_cksum = 0;

    ip->iph_dst = dest_addr = rand_dest ? rand_ipaddr(1): dest_addr;
    ip->iph_src = src_addr = rand_source ? rand_ipaddr(0) : src_addr;

    ip_len = sizeof(struct iphdr);

    if(ip_option) {
        ip_opt((const char *)(ip + ip_len), &opt_len);
    }
    
    *packet_len = ip_len = ip_len + opt_len;
    ip->iph_ihl = ip_len >> 2;
    
}



