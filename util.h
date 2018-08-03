#ifndef UTIL_H
#define UTIL_H 

int strequl(const char *str1, const char *str2);

int getTimeInterval(const char* optarg);

int  getLocalAddrinfo();

int  getRemoteAddr();

int JudgeIpIsCorrect(const char *ip);

int prase_iproute(const char *optarg,const char *s);

int JudgeScanPortCorrect(const char *arg,int *opt_num);

int prase_scanport(const char *optarg, const char *s);

#endif //UTIL_H
