#ifndef UTIL_H
#define UTIL_H 

int getTimeInterval(const char* optarg);

int getLocalAddrinfo();

int getRemoteAddr();

int JudgeIpIsCorrect(const char *ip);

int prase_iproute(const char *optarg,const char *s);

int JudgeScanPortCorrect(const char *arg,int *opt_num);

int prase_scanport(const char *optarg, const char *s);

int read_data(const char *packet, int len);

#endif //UTIL_H
