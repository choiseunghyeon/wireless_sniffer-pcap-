#ifndef FUNCTION_H
#define FUNCTION_H
#include "wirelessframe.h"
#include "pcap.h"

#define user_name 20

typedef struct user{
    char name[user_name];
    uint8_t mac[6];
    int voice_flag;
    int attendance_flag; // 1이면 확인
} user;

extern int USER_NUMBER;
int print_query_count ();
int chkstr(uint8_t *one, user *two);
void chkenv(pcap_if_t *d);
void voice(user *USER);
void reset_voice_flag();

#endif // FUNCTION_H

