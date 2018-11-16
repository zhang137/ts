#ifndef MYDEF_H
#define MYDEF_H 

#include <sys/types.h>
#include <stdint.h>


//#define __BEGIN_DECLS extern "C" {
//#define __END_DECLS }

#define MAX_ARGUMENT_LEN 200
#define TCP 6
#define ICMP 1
#define UDP 17

static int sequence;

extern int32_t tcp_mode;
extern int32_t rawip_mode;
extern int32_t udp_mode;
extern int32_t icmp_mode;
extern int32_t scan_mode;
extern int32_t listen_mode;
extern int32_t traceroute_mode;

extern int32_t  listen_sockfd;
extern int32_t  send_sockfd;

extern int32_t  beep;
extern int32_t  flood;
extern int32_t  fast;
extern int32_t  faster;
extern int32_t  rand_dest;
extern int32_t  rand_source;
extern int32_t  keep_port;
extern int32_t  ip_rroute;
extern int32_t  ip_lsrr;
extern int32_t  ip_ssrr;
extern int32_t  ip_tstamp;

extern int32_t  tcp_timestamp;
extern int32_t  tcp_sack_permit;
extern int32_t  tcp_exitcode;
extern int32_t  tr_stop;
extern int32_t  tr_keep_ttl;
extern int32_t  tr_no_rtt;
extern int32_t  icmp_ts;
extern int32_t  icmp_addr;
extern int32_t  icmp_help;
extern int32_t  icmp_gw;
extern int32_t  force_icmp;

extern int32_t  verbose;
extern int32_t  quiet;
extern int32_t  debug;
extern int32_t  send_count;
extern int32_t  interval;
extern int32_t  tcp_seq_num;
extern int32_t  tcp_ack_num;
extern int32_t  keep_port;


extern int32_t  need_prase_dns;
extern int32_t  bind;
extern int32_t  unbind;
extern int32_t  spoof;
extern int32_t  win_byte_order;
extern int32_t  relative_id;
extern int32_t  ip_frag;
extern int32_t  ip_mfrag;
extern int32_t  ip_dfrag;
extern int32_t  show_seq_num_only;
extern int32_t  rand_ipid;

extern int32_t  lsrr;
extern int32_t  ssrr;
extern int32_t  ip_option;

extern char *lsrr_route;
extern char *ssrr_route;
extern char *host;
extern char *ether_name;
extern char *file_name;

extern u_int8_t ttl;
extern u_int16_t ip_id;
extern u_int8_t ip_proto;
extern u_int16_t ip_fragoff;
extern u_int16_t mtu;
extern u_int16_t sys_mtu;
extern u_int8_t tos;
extern u_int8_t icmp_type;
extern u_int8_t icmp_code;
extern u_int16_t source_port;
extern u_int16_t dest_port;
extern u_int16_t tcp_mss;
extern u_int8_t window;
extern u_int16_t badcksum;

extern u_int8_t tcp_offset;
extern u_int8_t tcp_ack;
extern u_int8_t ack;
extern u_int8_t fin;
extern u_int8_t push;
extern u_int8_t rst;
extern u_int8_t syn;
extern u_int8_t urg;
extern u_int8_t cwr;
extern u_int8_t ece;
extern off_t data_size;
extern off_t data_end;
extern int32_t print_mode;
extern int32_t dump_mode;

extern uint32_t src_addr;
extern uint32_t dest_addr;
extern uint32_t redict_gateway;



extern uint32_t route_data[8];
extern uint16_t scanport_data[16];

struct pseudoheader
{
    u_int32_t source;
    u_int32_t dest;
    u_int8_t zero;
    u_int8_t protocol;
    u_int16_t length;
};

char *string_copy(const char *source);

#endif //MYDEF_H 
