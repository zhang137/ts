#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <errno.h>

#include "def.h"
#include "util.h"
#include "ip.h"

#define FILE_DATA_SIZE 4096

int getTimeInterval(const char* optarg)
{
    size_t slen = sizeof(optarg);
    if(slen < 2) {
        return -1;
    }

    if(optarg[0] != 'u' || !isdigit(*(optarg+2))) {
        return -1;
    }

    return atoi(optarg+1);
}

int JudgeIpIsCorrect(const char *ip)
{
    int slen = strlen(ip);
    int delim_num = 0;
    char *pdelim = NULL;
    const char *temp = ip;

    if(slen > INET_ADDRSTRLEN || slen < 7) {
        return 0;
    }

    while ( (pdelim = strchr(temp,'.')) != NULL) {
        delim_num ++;
        temp = pdelim + 1;
    }

    if(delim_num != 3) {
        return 0;
    }

    char *ip_data = strdup(ip);
    *(ip_data + slen) = '.';

    while((pdelim = strchr(ip_data,'.')) != NULL)
    {
        *pdelim = 0;
        if(*ip_data == '\0') {
            return 0;
        }

        char *temp = ip_data;
        while(temp != pdelim)
        {
            if(!isdigit(*temp))
                return 0;
        }

        int subfield = atoi(ip_data);
        if(subfield < 0 || subfield > 255) {
            return 0;
        }

        ip_data = pdelim + 1;
    }
    
    return 1;
}

int prase_iproute(const char *optarg,const char *s)
{
    int argnum = 0;
    const char *pdata = NULL;
    const char *temp = NULL; 
    const char *data = optarg;

    if(!data) {
        return 0;
    }

    while((temp = strtok_r(data,s,&pdata)) != NULL)
    {
        if(!JudgeIpIsCorrect(temp))
        {
            return -1;    
        }
        route_data[argnum++] = inet_addr(temp); 
        data = NULL;
    }

    if(!argnum) return -1;
    
    return 0;
}

int JudgeScanPortCorrect(const char *arg,int *opt_num)
{        
    int slen = strlen(arg);
    int delim_num = 0;

    char *pdelim = NULL;
    const char *temp = arg;

    if(slen > 11 || slen < 3) {
        return 0;
    }

    while ( (pdelim = strchr(temp,'-')) != NULL) {
        delim_num ++;
        temp = pdelim + 1;
    }

    if(delim_num != 1)
        return 0;

    char *port_data = strdup(arg);
    *(port_data + slen) = '-';

    while((pdelim = strchr(port_data,'-')) != NULL)
    {
        *pdelim = 0;
        if(*port_data == '\0') {
            return 0;
        }

        char *temp = port_data;
        while(temp != pdelim)
        {
            if(!isdigit(*temp)) {
                return 0;
            }
        }

        int port = atoi(port_data);
        if(port < 0 || port > 65535) {
            return 0;
        }

        scanport_data[(*opt_num)++] = port;
        port_data = pdelim + 1;
    }

    return 1;
}


int prase_scanport(const char *optarg, const char *s)
{
    int argnum = 0;
    const char *pdata = NULL;
    const char *temp = NULL;
    const char *data = optarg;
    
    if(!data)
        return -1;

    while((temp = strtok_r(data,s,&pdata)) != NULL)
    {
        if(!JudgeScanPortCorrect(optarg,&argnum))
        {
            return -1;    
        }
         
        data = NULL;
    }

    if(argnum % 2 != 0) scanport_data[argnum]= 0;
    
    return 0;
}


int getLocalAddrinfo()
{
    struct  ifaddrs addr,*paddr;
    struct  ifconf conf;
    struct  ifreq  *req;

    char buffer[BUFSIZ];
    char *ether;

    int32_t res,tempfd; 
    u_int32_t source_addr;
    
    res = getifaddrs(&&addr);
    if(res < 0) {
        return -1;
    }

    for(paddr = &addr; paddr != NULL; paddr = paddr->ifa_next)
    {
        if(paddr->ifa_addr->sa_family == AF_INET) 
        {
            if((ether_name && strstr(paddr->ifa_name,ether_name)) 
                    || !strstr(paddr->ifa_name,"lo")) 
            {
                if(!ether_name) {
                    ether_name = string_copy(paddr->ifa_name);
                }
                source_addr = ((struct sockaddr_in*)paddr->ifa_addr)->sin_addr.s_addr;
                break;
            }
        }
    }

    freeifaddrs(&addr);

    tempfd = socket(AF_INET,SOCK_STREAM,0);
    if(tempfd < 0) {
        return -1;
    }

    conf.ifc_len = BUFSIZ;
    conf.ifc_buf = buffer;

    strcpy(conf.ifc_req->ifr_name,ether_name);

    res = ioctl(tempfd,SIOCGIFCONF,&conf);
    if(res < 0) {
        return -1;
    }
    
    close(tempfd); 
    
    sys_mtu = conf.ifc_req->ifr_mtu; 
    return 0;
}


int getRemoteAddr()
{
    int32_t res = 0,dest_addr;
    struct addrinfo addr,*result,*paddr;

    memset(&addr,0,sizeof(addr));
    addr.ai_family = AF_INET;

    res = getaddrinfo(host,NULL,&addr,&result);
    if(res < 0) {
        return -1;
    }

    for(paddr = result; paddr != NULL; paddr = paddr->ai_next) {
        dest_addr = ((struct sockaddr_in *)paddr->ai_addr)->sin_addr.s_addr;
        break;
    }
    freeaddrinfo(paddr);

    return 0;
}




int open_file()
{
    int fd = 0;

    if(access(file_name,R_OK | F_OK)) {
        return -1; 
    }
   
    fd = open(file_name,O_RDONLY);
    if(fd < 0) {
        exit(-1);
    }
    return fd;
}

int getfiledata(int fd, char *buffer) 
{
    int ret = 0;
    int saved_errno;
    if(!data_size) {
        data_size = FILE_DATA_SIZE;
    }

    do {
        saved_errno = 0;
        ret = read(fd, buffer, data_size)) 
        if(ret < 0) {
            saved_errno = (errno == EINTR) ? errno : 0;
        }   
    }while (saved_errno == EINTR);
    
    return ret;
}













