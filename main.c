#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "prase_option.h"
#include "mydef.h"
#include "protocal.h"
#include "util.h"
#include "icmp.h"
#include "tcp.h"
#include "ip.h"
#include "udp.h"

void sigPort(int signo)
{
    dest_port += 1;
}

void sigTTL(int signo)
{
    ttl += 1;
}

int signal_handler()
{
    int res = 0;
    struct sigaction siga;
    memset(&siga,0,sizeof(siga));

    res = sigemptyset(&siga.sa_mask);
    if(res < 0)
        return -1;

    res = sigaddset(&siga.sa_mask,SIGTSTP);
    if(res < 0)
        return -1;

    if(bind) {
        siga.sa_handler = sigTTL;
    }
    else  { 
        siga.sa_handler = sigPort;
    }

    res = sigblock(siga.sa_mask);
    if(res < 0)
        return -1;

    res = sigaction(SIGTSTP,&siga,NULL);
    if(res < 0)
        return -1;

    return 0;
}

int main(int argc, char **argv)
{

    int res;
    
    res = prase_option(argc,argv);
    if(res < 0)
        exit(-1);
    
    if(!unbind) {
        if(signal_handler())
            exit(-1);
    }
    
    if(need_prase_dns) {
        getRemoteAddr();
    }

    if(rawip_mode) 
    {
        use_rawip_socket();
    }else 
    {
        use_normal_socket();
    }
    
    if(flood) {
        send_packet_flood();
    }
    
    if(listen_mode) {
        wait_client_connect();
    }

    if(scan_mode) {
        scan_host();
    }

    while(1)
    {
        wait_packet();
    }


    return 0;
}

























