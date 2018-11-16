#ifndef IP_H 
#define IP_H 

#include <sys/types.h>

typedef u_int32_t in_addr_t;
struct in_addr
{
    in_addr_t s_addr;
};

struct iphdr {
#if __BYTE_ORDER == __LITTLE_ENDIAN 
    unsigned int iph_ihl:4;
    unsigned int iph_version:4;
#endif
#if __BYTE_ORDER == __BIG_ENDIAN 
    unsigned int iph_version:4;
    unsigned int iph_ihl:4;
#endif 
	u_char  iph_tos;                 /* type of service */
	u_short iph_len;                 /* total length */
	u_short iph_id;                  /* identification */
	u_short iph_off;                 /* fragment offset field */
#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    u_char  iph_ttl;                 /* time to live */
	u_char  iph_proto;              /* protocol */
	u_short iph_cksum;                 /* checksum */
    in_addr_t iph_src,iph_dst;  /* source and dest address */
};

/*
struct ipheadr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN 
    unsigned int iph_ihl:4;
    unsigned int iph_version:4;
#endif
#if __BYTE_ORDER == __BIG_ENDIAN 
    unsigned int iph_version:4;
    unsigned int iph_ihl:4;
#endif 
    u_int8_t  iph_tos;
    u_int16_t iph_tlh;
    u_int16_t iph_id;
    u_int16_t iph_flag_off;
    u_int8_t  iph_ttl;
    u_int8_t  iph_protocol;
    u_int16_t iph_cknum;
    u_int32_t iph_source;
    u_int32_t iph_dest;
};*/

struct ip_timestamp
{
    u_int8_t ipt_type;			/* IPOPT_TS */
    u_int8_t ipt_len;			/* size of structure (variable) */
    u_int8_t ipt_ptr;			/* index of current entry */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ipt_flg:4;		/* flags, see below */
    unsigned int ipt_oflw:4;		/* overflow counter */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned int ipt_oflw:4;		/* overflow counter */
    unsigned int ipt_flg:4;		/* flags, see below */
#endif
    u_int32_t data[9];
};// The timestamp option is not copied upon fragmentation.  It iscarried in the first fragment.  Appears at most once in a datagram.

struct ip_noop 
{
    u_int8_t type;
};
// May be copied, introduced, or deleted on fragmentation, or for any other reason.

struct ip_rr 
{
    u_int8_t   ipr_type;
    u_int8_t   ipr_len;
    u_int8_t   ipr_ptr;
    u_int32_t  ipr_data[9];
}__attribute__((packed));// not copied on fragmentation,goes in first fragment only,Appears at most once in datagram


struct ip_lsrr
{
    u_int8_t   ipl_type;
    u_int8_t   ipl_len;
    u_int8_t   ipl_ptr;
    u_int32_t  ipl_data[9];
}__attribute__((packed));

struct ip_ssrr
{

    u_int8_t   ips_type;
    u_int8_t   ips_len;
    u_int8_t   ips_ptr;
    u_int32_t  ips_data[9];
}__attribute__((packed));//fragment must copy

struct ip_sid
{
    u_int8_t ipsid_type;
    u_int8_t ipsid_len;
    u_int16_t ipsid_sid;
};
// This option provides a way for the 16-bit SATNET stream identifier to be carried through networks that do not support the stream concept.
// Must be copied on fragmentation.  Appears at most once in a datagram.

struct ip_scurity 
{
};


#define	IPVERSION	4               /* IP version number */
#define	IP_MAXPACKET	65535		/* maximum packet size */

#define	IPTOS_TOS_MASK		0x1E
#define	IPTOS_TOS(tos)		((tos) & IPTOS_TOS_MASK)
#define	IPTOS_LOWDELAY		0x10
#define	IPTOS_THROUGHPUT	0x08
#define	IPTOS_RELIABILITY	0x04
#define	IPTOS_LOWCOST		0x02
#define	IPTOS_MINCOST		IPTOS_LOWCOST


#define	IPOPT_EOL		0		/* end of option list */
#define	IPOPT_END		IPOPT_EOL
#define	IPOPT_NOP		1		/* no operation */
#define	IPOPT_NOOP		IPOPT_NOP

#define	IPOPT_RR		7		/* record packet route */
#define	IPOPT_TS		68		/* timestamp */
#define	IPOPT_TIMESTAMP		IPOPT_TS
#define	IPOPT_SECURITY		130		/* provide s,c,h,tcc */
#define	IPOPT_SEC		IPOPT_SECURITY
#define	IPOPT_LSRR		131		/* loose source route */
#define	IPOPT_SATID		136		/* satnet id */
#define	IPOPT_SID		IPOPT_SATID
#define	IPOPT_SSRR		137		/* strict source route */
#define	IPOPT_RA		148		/* router alert */

#define IPOPT_OPTVAL   0
#define	IPOPT_OLEN		1		/* option length */
#define	IPOPT_OFFSET		2		/* offset within option */
#define	IPOPT_MINOFF		4		/* min value of above */

#define	MAX_IPOPTLEN		40

/* flag bits for ipt_flg */
#define	IPOPT_TS_TSONLY		0		/* timestamps only */
#define	IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	IPOPT_TS_PRESPEC	3		/* specified modules only */

#define	MAXTTL		255		/* maximum time to live (seconds) */
#define	IPDEFTTL	64		/* default ttl, from RFC 1340 */
#define	IPFRAGTTL	60		/* time to live for frags, slowhz */
#define	IPTTLDEC	1		/* subtracted when forwarding */

#define	IP_MSS		576		/* default maximum segment size */


void parcel_ip_packet(const char *packet,int *packet_len);

#endif //IP_H
