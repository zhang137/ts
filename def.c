#include <string.h>
#include "def.h"

int32_t  tcp_mode = 1;
int32_t  rawip_mode = 0;
int32_t  udp_mode = 0;
int32_t  icmp_mode = 0;
int32_t  scan_mode = 0;
int32_t  listen_mode = 0;
int32_t  traceroute_mode = 0;


int32_t  listen_sockfd;
int32_t  send_sockfd;

int32_t  flood = 0;
int32_t  fast = 1;
int32_t  faster = 0;
int32_t  rand_dest = 0;
int32_t  rand_source = 0;
int32_t  ip_rroute = 0;
int32_t  ip_lsrr = 0;
int32_t  ip_ssrr = 0;
int32_t  ip_tstamp = 0;
int32_t  tcp_seq_num = 0;
int32_t  tcp_ack_num = 0;

int32_t  tcp_timestamp = 0;
int32_t  tcp_sack_permit = 0;
int32_t  icmp_ts = 0;
int32_t  icmp_addr = 0;
int32_t  icmp_help = 0;
int32_t  icmp_gw = 0;
int32_t  force_icmp = 0;

int32_t   beep = 0;
int32_t   verbose = 0;
int32_t   quiet = 0;
int32_t   debug = 0;
int32_t   count = 0;
int32_t   interval = 0;
int32_t   send_count = 0;
int32_t   need_prase_dns = 1;
int32_t   bind = 0;
int32_t   unbind = 0;
int32_t   spoof;
int32_t   win_byte_order = 0;
int32_t   relative_id = 0;
int32_t   show_seq_num_only = 0;
int32_t   keep_port = 0;
int32_t   rand_ipid = 1;

int32_t   ip_frag = 0;
int32_t   ip_mfrag = 0;
int32_t   ip_dfrag = 0;
int32_t   lsrr = 0;
int32_t   ssrr = 0;
int32_t   ip_option = 0;


char *lsrr_route = 0;
char *ssrr_route = 0;
char *ether_name = 0;
char *file_name = 0;
char *host;


u_int8_t ttl = 64;
u_int16_t ip_id = 0;
u_int8_t ip_proto = 6;
u_int16_t ip_fragoff = 0;
u_int16_t mtu = 0;
u_int16_t sys_mtu = 0;
u_int8_t tos = 0;
u_int8_t icmp_type = 8;
u_int8_t icmp_code = 0;
u_int16_t source_port = 0;
u_int16_t dest_port = 0;
u_int16_t tcp_mss = 0;
u_int8_t window = 64;
u_int16_t badcksum = 0;

u_int8_t tcp_offset = 0;

u_int8_t ack = 0;
u_int8_t fin = 0;
u_int8_t push = 0;
u_int8_t rst = 0;
u_int8_t syn = 0;
u_int8_t urg = 0;
u_int8_t cwr = 0;
u_int8_t ece = 0;

off_t data_size;
off_t data_end;

int32_t print_mode = 0;
int32_t dump_mode = 0;

int32_t  tr_stop = 0;
int32_t  tr_keep_ttl = 0;
int32_t  tr_no_rtt = 0;
int32_t  tcp_exitcode;

uint32_t src_addr;
uint32_t dest_addr;
uint32_t redrct_gateway;

uint32_t route_data[8];
uint16_t scanport_data[16];



char* string_copy(const char *source)
{
    return strdup(source);
}




