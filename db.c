
#include <bson.h>
#include <mongoc.h>
#include <stdio.h>

/*int addflag=0;

db(){
   mongoc_client_t *client; // db address
   mongoc_collection_t *collection;
   mongoc_cursor_t *cursor;
   bson_t *doc;
   bson_t *checkdoc;
   bson_t *query;
   char *str;
   mongoc_init ();
   userdoc = BCON_NEW(
               "name",BCON_UTF8(&user));
   client = mongoc_client_new ("mongodb://localhost:27017");
   collection = mongoc_client_get_collection (client, "attendance", "userlist");
   query = bson_new ();
   BSON_APPEND_UTF8(query,"hello", "world"); //
   cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);

   while (mongoc_cursor_next (cursor, &doc)) {
      str = bson_as_json (doc, NULL);
      printf ("%s\n", str);
      bson_free (str);
   }
   printf("if you want to add some user then input 1");
   scanf("%d",&addflag);
   if(addflag==1)
       if(adduser())
           printf("add fail");
   bson_destroy (query);
   mongoc_cursor_destroy (cursor);
   mongoc_collection_destroy (collection);
   mongoc_client_destroy (client);
   mongoc_cleanup ();

   return 0;
}

bool adduser(){
    bson_t *userdoc;
    char *user;
    int flag;
    while(1){
    printf("input new user\n");
    scanf("%s",user);
    printf("are you sure? %s\n 1 is ok\n2 is fail\n", user);
    scanf("%d",&flag);
    if(flag==1)
        break;
    }
    userdoc = BCON_NEW( "name",BCON_UTF8(&user) );
    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, userdoc, NULL, &error)) {
    fprintf (stderr, "%s\n", error.message);
    return -1;
    }
    return 1;
}
*/
