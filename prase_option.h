#ifndef PRASE_OPTION_H
#define PRASE_OPTION_H

int prase_noarg_option(const char* opt_name,const char *optarg);

int prase_mode_option(int opt);

int prase_other_option(int opt,const char *arg);

int prase_option(int argc, char **argv);

#endif //PRASE_OPTION_H

