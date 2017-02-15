#ifndef FUNCTION_H
#define FUNCTION_H

#include "pcap.h"
#include <stdint.h>
#include <wirelessframe.h>
#include <string.h> // for sprintf function.
#include <fcntl.h>
#include <stdlib.h>
#define USER_NUMBER 1 //number of users

int user_voice_flag[USER_NUMBER]; // user_mac과 같은 배열 번호에 return값을 반환
uint8_t user_mac[USER_NUMBER][MAC_LEN]={0xf4,0x42,0x8f,0x2c,0x70,0x53};

int chgstr(uint8_t *one, uint8_t *two){ // strcmp는 null바이트가 있어야함
    int cnt=0;
    for(int i=0;i<MAC_LEN;i++){
        if(one[i]!=two[i])
            return 0;
        cnt++;
    }
    if(cnt==MAC_LEN)
        return 1;

}


void voice(int *flag){
    if(*flag==1){
        system("play /home/choi/Desktop/jarvis_voice/welcome.wav");
        *flag+=1;
    }
    return 0;
        /* voice : http://superuser.com/questions/276596/play-mp3-or-wav-file-via-linux-command-line */
}

void reset_voice_flag(){
    for(int i;i<USER_NUMBER;i++){
        user_voice_flag[i]=1;
    }

}

void chkenv(pcap_if_t *d){

    int fd,height=3;

    fd = open("./set.sh", O_WRONLY | O_CREAT | O_EXCL, S_IRWXU ); //http://amy82.tistory.com/248
    printf("%d",fd);
    if(!(fd==-1)){
        char **script=NULL;                             /* 2중포인터                     */
        script=(char**)malloc(sizeof(char*)*height);              /* http://amy82.tistory.com/248*/
        for(int i=0;i<height;i++)
            script[i]=(char*)malloc(sizeof(char)*1024);        // script+i == script[i]

        script[1]="#!/bin/bash\ninterface=";
        script[2]="\na=`iwconfig $interface | grep Mode | awk 'BEGIN {FS=\":\"}{print $2}' | sudo awk '{print $1==\"Managed\"}'`\n\nif [ $a == '1' ];"
                "then\n\tifconfig $interface down\n\tiwconfig $interface mode monitor\n\tifconfig $interface up\nfi";
        sprintf(script[0],"%s%s%s",script[1],d->name,script[2]);
        write(fd,script[0],strlen(script[0]));
        close(fd);
        //script와 script[0]이 왜 같을까..
        //for(int i=0;i<height;i++)           // http://codeng.tistory.com/8
          //  free(script[i]);
        free(script[0]);
        free(script[1]);
        free(script[2]);
        free(script);
    }
    system("./set.sh");
}


#endif // FUNCTION_H

