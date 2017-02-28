#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"
#include <stdint.h>
#include "function.h"



/* static const char *JSON_STRING =
    "{\"_id\" : \"58a983127cbd81a7cbacd58f\", \"user\" : { \"choi\" : [ f4, 1a, b2, 2a, 4a, 5a ] } }"; */

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
            strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

user json_parse(const char *JSON_STRING){
    int i;
    int r;
    user u; // 초기화.
    jsmn_parser p;
    jsmntok_t t[128]; /* We expect no more than 128 tokens */
    char tmp[2], *end; // for mac
    int cnt=0;
    jsmn_init(&p);

    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d\n", r);
        u.stat=-1;
        return us;
    }

    /* Loop over all keys of the root object */
    // t[i].end-t[i].start == string number && JSON_STRING + t[i].start == strating string.
    for (i = 1; i < r; i++) {
        //printf("%d ",t[i].end-t[i].start);
        //printf("%d.Unexpected key: %.*s\n",i, t[i].end-t[i].start,
                //JSON_STRING + t[i].start); 값이 덮어씌워지는데 왜지?
        if(i==7){
            strncpy(u.name,JSON_STRING + t[i].start,t[i].end-t[i].start);
        } else if(i>=9 && i<=14){
            strncpy(tmp,JSON_STRING + t[i].start,t[i].end-t[i].start);
            u.mac[cnt]=strtol(tmp,&end,16);
            cnt++;
        }
    }
    return us;
}

