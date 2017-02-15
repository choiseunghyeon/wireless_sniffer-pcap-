#include "pcap.h"
#include <stdint.h>
#include <wirelessframe.h>
#include <string.h> // for sprintf function.
#include <fcntl.h>
#include <stdlib.h>
#include <function.h>

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
    char interface=(char**)calloc(2,sizeof(char*));
    interface[0]=(char*)calloc(100,sizeof(char));
    interface[1]=(char*)calloc(100,sizeof(char));
    strcpy(interface[1],'./set.sh ');
    sprintf(interface[0],"%s%s",interface[1],d->name);
    fd = open("./set.sh", O_WRONLY | O_CREAT | O_EXCL, S_IRWXU ); //http://amy82.tistory.com/248
    printf("%d",fd);
    if(!(fd==-1)){
        char **script=NULL;                             /* 2중포인터                     */
        script=(char**)malloc(sizeof(char*)*height);              /* http://amy82.tistory.com/248*/
        for(int i=0;i<height;i++)
            script[i]=(char*)malloc(sizeof(char)*1024);        // script+i == script[i]

        strcpy(script[1],"#!/bin/bash\ninterface=$1");
        strcpy(script[2],"\na=`iwconfig $interface | grep Mode | awk 'BEGIN {FS=\":\"}{print $2}' | sudo awk '{print $1==\"Managed\"}'`\n\nif [ $a == '1' ];"
                "\nthen\n\tifconfig $interface down\n\tiwconfig $interface mode monitor\n\tifconfig $interface up\nfi");
        sprintf(script[0],"%s%s%s",script[1],d->name,script[2]);
        write(fd,script[0],strlen(script[0]));
        for(int i=0;i<height;i++)           // http://codeng.tistory.com/8
            free(script[i]);
        free(script);
    }
    close(fd);
    system(interface[0]);
    for(int i=0;i<2;i++){
        free(interface[i]);
    }
    free(interface);
}
// interface shell에서 변수로 받김
