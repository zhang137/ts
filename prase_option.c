#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#include "util.h"
#include "mydef.h"
#include "prase_option.h"

static struct option long_options[] = 
{
    {"help",no_argument,0,'h'},
    {"version",no_argument,0,'v'},
    {"interval",required_argument,0,'i'},
    {"fast",no_argument,&fast,1},
    {"faster",no_argument,&faster,1},
    {"flood",no_argument,&flood,1},
    {"numeric",no_argument,0,'n'},
    {"quiet",no_argument,0,'q'},
    {"interface",required_argument,0,'I'},
    {"verbose",no_argument,0,'q'},
    {"count",required_argument,0,'c'},
    {"debug",no_argument,0,'D'},
    {"bind",no_argument,0,'z'},
    {"unbind",no_argument,0,'Z'},
    {"beep",no_argument,&beep,1},
//Mode
// tcp default
    {"rawip",no_argument,0,'0'},
    {"icmp",no_argument,0,'1'},
    {"udp",no_argument,0,'2'},
    {"scan",required_argument,0,'8'},
    {"listen",no_argument,0,'9'},
//Ip
    {"spoof",no_argument,0,'a'},
    {"rand-dest",no_argument,&rand_dest,1},
    {"rand-source",no_argument,&rand_source,1},
    {"ttl",required_argument,0,'t'},
    {"id",required_argument,0,'N'},
    {"winid",required_argument,0,'W'},
    {"rel",required_argument,0,'r'},
    {"window",required_argument,0,'w'},
    {"ipproto",required_argument,0,'H'},
    {"frag",no_argument,0,'f'},
    {"morefrag",no_argument,0,'x'},
    {"dontflag",no_argument,0,'y'},
    {"fragoff",required_argument,0,'g'},
    {"mtu",required_argument,0,'m'},
    {"tos",required_argument,0,'o'},
    {"rroute",no_argument,0,'G'},
    {"lsrr",required_argument,0,0},
    {"ssrr",required_argument,0,0},
    {"iptstamp",no_argument,&ip_tstamp,1},
    
//tcp/udp
    {"baseport",required_argument,0,'s'},
    {"destport",required_argument,0,'p'},
    {"keep",no_argument,&keep_port,1},
    {"tcpoff",required_argument,0,'O'},
    {"seqnum",required_argument,0,'Q'},
    {"badcksum",no_argument,0,'b'},
    {"setseq",required_argument,0,'M'},
    {"setack",required_argument,0,'L'},
    {"fin",no_argument,0,'F'},
    {"syn",no_argument,0,'S'},
    {"rst",no_argument,0,'R'},
    {"push",no_argument,0,'P'},
    {"urg",no_argument,0,'A'},
    {"ack",no_argument,0,'U'},
    {"xmas",no_argument,0,'X'},
    {"ymas",no_argument,0,'Y'},
    {"tcpexitcode",required_argument,0,0},
    {"tcp-mss",required_argument,0,0},
    {"tcp-timestamp",no_argument,&tcp_timestamp,1},
    {"tcp-sack-permit",no_argument,&tcp_sack_permit,1},
//icmp    
    {"icmp-type",required_argument, 0,'C'},
    {"icmp-code",required_argument,0,'K'},
    {"force-icmp",no_argument,&force_icmp,1},
    {"icmp-gw",required_argument,&icmp_gw,1},
    {"icmp-ts",no_argument,&icmp_ts,1},
    {"icmp-addr",no_argument,&icmp_addr,1}, 
    {"icmp-help",no_argument,&icmp_help,1},

    {"data",required_argument,0,'d'},
    {"file",required_argument,0,'E'},
    {"dump",no_argument,0,'j'},
    {"sign",required_argument,0,'e'},
    {"print",no_argument,0,'J'},
    {"safe",no_argument,0,'B'},
    {"end",required_argument,0,'u'},
    {"traceroute",no_argument,0,'T'},
    {"tr-stop",no_argument,&tr_stop,1},
    {"tr-keep-ttl",no_argument,&tr_keep_ttl,1},
    {"tr-no-rtt",no_argument,&tr_no_rtt,1},
    {0,0,0,0}
};

void help_usage()
{
    const char *usage = "Same as hping3 usage.";
    fprintf(stdout,"%s",usage);
}

void version_print()
{
    const char *version = "Personal first edition network tools. version number 0.0.1\n";
    fprintf(stdout,"%s",version);
}



int prase_noarg_option(const char* opt_name,const char *optarg)
{
   if(tcp_mode || udp_mode || traceroute_mode 
           || listen_mode || scan_mode)
   {
        
       if(!strcmp(opt_name,"force_icmp")) 
        {
            force_icmp = 0;
        }else if(!strcmp(opt_name,"icmp-gw"))
        {
            icmp_gw = 0;
        }else if(!strcmp(opt_name,"icmp-ts"))
        {
            icmp_ts = 0;
        }else if(!strcmp(opt_name,"icmp-addr"))
        {
            icmp_addr = 0;
        }else if(!strcmp(opt_name,"icmp-help"))
        {
            icmp_help = 0;
        }
   }
   if(icmp_mode || udp_mode || traceroute_mode || listen_mode)
   {
       if(strcmp(opt_name,"tcp-timestamp")) {
             tcp_timestamp = 0;
         }else if(strcmp(opt_name,"tcp-sack-permit")) {
             tcp_sack_permit = 0;
         }
    }

    if(tcp_mode && strcmp(opt_name,"tcp-mss")) {
         tcp_mss= atoi(optarg);
    }        

    if(!listen_mode)
    {
         if(!strcmp(opt_name,"ssrr")) 
         {    
             ssrr_route = string_copy(optarg);
             ssrr = 1;
         }
         else if(!strcmp(opt_name,"lsrr"))
         {
             lsrr_route = string_copy(optarg);
             lsrr = 1;
         }else if(!strcmp(opt_name,"rand-dest"))
         {
             rand_dest = 1;
         }else if(!strcmp(opt_name,"rand-source"))
         {
             rand_source = 1;
         }
    }
   
    if(!strcmp(opt_name,"fast"))
    {
        interval = 10000;
    }else if(!strcmp(opt_name,"faster"))
    {
        interval = 1000;
    }else if(!strcmp(opt_name,"flood"))
    {
        flood = 1;
    }
    return 0;
}

int prase_mode_option(int opt,const char *optarg)
{
    int res = 0;
    tcp_mode = 0;
    switch(opt)
    {
    case '0':
        rawip_mode = 1;
        break;
    case '1':
        icmp_mode = 1;
        rawip_mode = 1;
        break;
    case '2':
        udp_mode = 1;
        break;
    case '8':
        scan_mode = 1;
        rawip_mode = 1;
        res = prase_portrange(optarg);
        break;
    case '9':
        listen_mode = 1;
        break;
    default:
        return -1;
    }
    return 0;
}

int prase_other_option(int opt,const char *arg)
{
    int arg_len = strlen(arg);

    if(arg_len > MAX_ARGUMENT_LEN)
    {
        fprintf(stderr,"Option %c's argument is too big\n",opt);
        return -1;
    }

    switch(opt)
    {
        case'h':
            help_usage();
            break;
        case'v':
            version_print();
            break;
        case'c':
            send_count = atoi(arg);
            break;
        case'i':
            interval = getTimeInterval(arg);
            if(interval < 0)
                return -1;
            break;
        case'n':
            host = string_copy(arg);
            need_prase_dns = 0;
            break;
        case'q':
            quiet = 1;
            break;
        case'I':   
            ether_name = string_copy(arg);
            break;
        case'V':
            verbose = 1;
            break;
        case'D':
            debug = 1;
            break;
        case'z':
            bind = 1;
            break;
        case'Z':
            unbind = 1;
            break;
        case'a':
            spoof = 1;
            break;
        case't':
            ttl = atoi(arg);
            break;
        case'N':
            ip_id = atoi(arg);
            rand_ipid = 0;
            break;
        case'W':
            win_byte_order = 1;
            break;
        case'r':
            relative_id = 1;
            break;
        case'f':
            ip_frag = 1;
            break;
        case'x':
            ip_mfrag = 1;
            break;
        case'y':
            ip_dfrag = 1;
            break;
        case'g':
            ip_fragoff = atoi(arg);
            break;
        case'm':
            mtu = atoi(arg);
            break;
        case'o':
            tos = atoi(arg);
            break;
        case'G':
            ip_rroute = 1;
            break;
        case'H':
            ip_proto = atoi(arg);
            break;
        case'C':
            icmp_type = atoi(arg);
            break;
        case'K':
            icmp_code = atoi(arg);
            break;
        case's':
            source_port = atoi(arg);
            break;
        case'p':
            dest_port = atoi(arg);
            break;
        case'k':
            keep_port = 1;
            break;
        case'w':
            window  = atoi(arg);
            break;
        case'O':
            tcp_offset = atoi(arg);
            break;
        case'Q':
            show_seq_num_only = 1;
            break;
        case'b':
            badcksum = atoi(arg);
            break;
        case'M':
            tcp_seq_num = atoi(arg);
            break;
        case'L':
            tcp_ack_num = atoi(arg);
            break;
        case'F':
            fin = 1;
            break;
        case'S':
            syn = 1;
            break;
        case'R':
            rst = 1;
            break;
        case'P':
            push = 1;
            break;
        case'A':
            ack = 1;
            break;
        case'U':
            urg = 1;
            break;
        case'X':
            cwr = 1;
            break;
        case'Y':
            ece = 1;
            break;
        case'd':
            data_size = atoi(arg);
            break;
        case'E':
            file_name = string_copy(arg);
            break;
        case'e':
            break;
        case'j':
            dump_mode = 1;
            break;
        case'J':
            print_mode = 1;
            break;
        case'B':
            break;
        case'u':
            data_end = atoi(arg);
            break;
        case'T':
            traceroute_mode = 1;
            bind = 1;
            ttl = 1;
            break;
        default:
            return -1;
    }
    return 0;
}



int prase_option(int argc, char **argv)
{
    int indexptr,opt,res = 0;
    const char *short_optiuon = "H:v:c:i:n:qI:VDzZ01289at:Nwrf:xyg:m:o:G:H:C:K:s:p:kw:O:Q:b:M:L:F:S:R:P:A:U:d:E:jJBu:T";
    
    while((opt = getopt_long_only(argc,argv,short_optiuon,long_options,&indexptr)) != -1)
    {
    
        if(!opt) 
        {
            res = prase_noarg_option(long_options[indexptr].name,optarg);        
            if(res < 0)
                return -1;
        } 
        else if(isdigit(opt))
        {
            res = prase_mode_option(opt);
            if(res < 0)
                return -1;
        }
        else if(opt == '?')
        {
            if(strchr(short_optiuon,optopt)) {
                fprintf(stderr, "Option %c need a argument\n",optopt);
            }
            else if(isprint(optopt)) {
                fprintf(stderr, "Unknow Option %c\n",optopt);
            }
            else 
            {
                fprintf(stderr,"Unknown Error 0x%08x\n",optopt);
            }
        }
        else
        {
            res = prase_other_option(opt,optarg);
            if(res < 0)
                return -1;
        }
    }

    while( optind < argc)
    {
        
        fprintf(stderr, "Unknow Option %s\n",argv[optind++]);
    }
    return 0;
}















