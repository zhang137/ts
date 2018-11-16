#ifndef TCP_H 
#define TCP_H 

#include "def.h"

__BEGIN_DECLS 

typedef u_int tcp_seq;

struct tcphdr {
	u_short th_sport;               /* source port */
	u_short th_dport;               /* destination port */
	tcp_seq th_seq;                 /* sequence number */
	tcp_seq th_ack;                 /* acknowledgement number */
/*
#if __BYTE_ORDER == __BIG_ENDIAN
    u_char th_off:4;
    u_char th_res:4;
#endif 
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_char th_res:4;
    u_char th_off:4;
#endif 
*/
    u_char  th_offx2;        
#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
	u_char  th_flags;
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_ECE  0x40  //ECN-Echo
#define TH_CWR  0x80  //Congestion Window Reduced  (34 35 2 field is ECE(Explicit Congestion Notification))
#define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win;                 /* window */
	u_short th_sum;                 /* checksum */
	u_short th_urp;                 /* urgent pointer */
};


/*
struct tcpheadr
{
    u_int16_t tch_source;
    u_int16_t tch_dest;
    u_int32_t tch_seqnum;
    u_int32_t tch_acknum;
#if __BYTE_ORDER == __BIG_ENDIAN 
    u_int16_t tch_doff:4;
    u_int16_t tch_res1:4;
    u_int16_t tch_res2:2;
    u_int16_t tch_urg:1;
    u_int16_t tch_ack:1;
    u_int16_t tch_psh:1;
    u_int16_t tch_rst:1;
    u_int16_t tch_syn:1;
    u_int16_t tch_fin;1;
#endif
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int16_t tch_res1:4;
    u_int16_t tch_doff:4;
    u_int16_t tch_fin:1;
    u_int16_t tch_syn:1;
    u_int16_t tch_rst:1;
    u_int16_t tch_psh:1;
    u_int16_t tch_ack:1;
    u_int16_t tch_urg:1;
    u_int16_t tch_res2:2;
#endif
    u_int16_t tch_win;
    u_int16_t tch_ckm;
    u_int16_t tch_purg;
};*/



enum
{
  TCP_ESTABLISHED = 1,
  TCP_SYN_SENT,
  TCP_SYN_RECV,
  TCP_FIN_WAIT1,
  TCP_FIN_WAIT2,
  TCP_TIME_WAIT,
  TCP_CLOSE,
  TCP_CLOSE_WAIT,
  TCP_LAST_ACK,
  TCP_LISTEN,
  TCP_CLOSING   /* now a valid state */
};

# define TCPOPT_EOL		0
# define TCPOPT_NOP		1
# define TCPOPT_MAXSEG		2
# define TCPOLEN_MAXSEG		4
# define TCPOPT_WINDOW		3
# define TCPOLEN_WINDOW		3
# define TCPOPT_SACK_PERMITTED	4		/* Experimental */
# define TCPOLEN_SACK_PERMITTED	2
# define TCPOPT_SACK		5		/* Experimental */
# define TCPOPT_TIMESTAMP	8
# define TCPOLEN_TIMESTAMP	10
# define TCPOLEN_TSTAMP_APPA	(TCPOLEN_TIMESTAMP+2) /* appendix A */

# define TCPOPT_TSTAMP_HDR	\
    (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_TIMESTAMP<<8|TCPOLEN_TIMESTAMP)

/*
 * Default maximum segment size for TCP.
 * With an IP MSS of 576, this is 536,
 * but 512 is probably more convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof (struct tcpiphdr)).
 */
# define TCP_MSS	512

# define TCP_MAXWIN	65535	/* largest value for (unscaled) window */

# define TCP_MAX_WINSHIFT	14	/* maximum window shift */

# define SOL_TCP		6	/* TCP level */


# define TCPI_OPT_TIMESTAMPS	1
# define TCPI_OPT_SACK		2
# define TCPI_OPT_WSCALE	4
# define TCPI_OPT_ECN		8


#define TCP_MSS_DEFAULT		 536U	/* IPv4 (RFC1122, RFC2581) */
#define TCP_MSS_DESIRED		1220U	/* IPv6 (tunneled), EDNS0 (RFC3226) */

struct tcp_eol 
{
    u_int8_t type;
};

struct tcp_nop 
{
    u_int8_t type;
};

struct tcp_maxseg 
{
    u_int8_t type;
    u_int8_t len;
    u_int16_t maxlen;
};

struct tcp_winscale
{
    u_int8_t type;
    u_int8_t len;
    u_int8_t scale;
}__attribute__((packed));

struct tcp_tmstamp 
{
    u_int8_t type;
    u_int8_t len;
    u_int32_t send_stamp;
    u_int32_t recv_tstamp;
}__attribute__((packed));

struct tcp_sack_permitted 
{
    u_int8_t type;
    u_int8_t len;
};

struct tcp_sack 
{
    u_int8_t type;
    u_int8_t len;
    u_int32_t sack_num[9];
}__attribute__((packed));

__END_DECLS


int transmit_tcp_packet(const char* packet,int *packet_len);


#endif //TCP_H
