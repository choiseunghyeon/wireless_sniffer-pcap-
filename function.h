#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

int chgstr(uint8_t *one, uint8_t *two,int len){ // strcmp는 null바이트가 있어야함
    int cnt=0;
    for(int i=0;i<len;i++){
        if(one[i]==two[i])
            cnt++;
    }
    if(cnt==len)
        return 1;
    else
        return 0;
}

#endif // FUNCTION_H

