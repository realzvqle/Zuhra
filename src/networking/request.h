#ifndef REQUEST_H_INCLUDED
#define REQUEST_H_INCLUDED




#include "../main.h"



typedef struct _requestData{
    char* result;
    char* url;
    int status;
    bool init;
    bool shouldLoad;
} requestData;


int fetch_lua_script(void* args);

#endif