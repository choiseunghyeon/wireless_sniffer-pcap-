#ifndef FUNCTION_H
#define FUNCTION_H


#define USER_NUMBER 1 //number of users
extern int user_voice_flag[USER_NUMBER]; // user_mac과 같은 배열 번호에 return값을 반환
extern uint8_t user_mac[USER_NUMBER][MAC_LEN];

int chkstr(uint8_t *one, uint8_t *two);
void chkenv(pcap_if_t *d);
void voice(int *flag);
void reset_voice_flag();

#endif // FUNCTION_H

