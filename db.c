
#include <bson.h>
#include <mongoc.h>
#include <stdio.h>
#include "function.h"

int addflag=0;

struct ch{
    char a[2];
};

db(){
    mongoc_client_t *client; // db address
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    const char *str;
    int cnt=0,parse_cnt=0;
    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017");
    collection = mongoc_client_get_collection (client, "attendance", "userlist");
    query = bson_new ();
    cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);
    printf("\nif you want to add some user then input 1 :  ");
    scanf("%d",&addflag);
    if(addflag==1)
        if(adduser(collection))
             printf("success\n");
    printf("user list\n");
    cnt=print_query_count (collection, query);
    user list[cnt];

    while (mongoc_cursor_next (cursor, &doc)) {
       str = bson_as_json (doc, NULL);
       printf ("%s\n", str);
       list[parse_cnt]=json_parse(str);
       bson_free (str);
    }
    //printf("%s",list[0]->name);
    bson_destroy (query);
    mongoc_cursor_destroy (cursor);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

    return 0;
 }

 int adduser(mongoc_collection_t *collection){
     bson_t *userdoc;
     bson_error_t error;
     char name[20];
     struct ch usermac0, usermac1, usermac2, usermac3, usermac4, usermac5;
     int number,flag=0;

     printf("how many user do you input?? : ");
     scanf("%d",&number);
     while(number>0){
         printf("input new user name and usermac\n");
         // ex. choi 8f 1b 2b 3b 4b 5b
         scanf("%s %s %s %s %s %s %s", name, &usermac0,&usermac1,&usermac2,&usermac3,&usermac4,&usermac5);
         printf("are you sure? %s %s %s %s %s %s %s\n1 is ok\n2 is fail\n",
                name,usermac0.a,usermac1.a,usermac2.a,usermac3.a,usermac4.a,usermac5.a);
         scanf("%d",&flag);
         if(flag==2)
             continue;
         // "user\" : { \"choi\" : [ f4, 1a, b2, 2a, 4a, 5a ] } }
         userdoc = BCON_NEW( "user", "{",name,"[",
                            BCON_UTF8(&usermac0),BCON_UTF8(&usermac1),BCON_UTF8(&usermac2),
                            BCON_UTF8(&usermac3),BCON_UTF8(&usermac4),BCON_UTF8(&usermac5)
                            ,"]","}" );
         if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, userdoc, NULL, &error)) {
             fprintf (stderr, "%s\n", error.message);
             return -1;
         }
         number--;
     }
     bson_destroy(userdoc);
     return 1;
 }

 int print_query_count (mongoc_collection_t *collection, bson_t *query)
 {
    bson_error_t error;
    int count;

    count = mongoc_collection_count (
       collection, MONGOC_QUERY_NONE, query, 0, 0, NULL, &error);

    if (count < 0) {
       fprintf (stderr, "Count failed: %s\n", error.message);
       return -1;
    } else {
       return count;
    }
 }
