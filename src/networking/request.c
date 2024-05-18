#include "request.h"




int fetch_lua_script(void* args) {
    requestData* data = (requestData*)args;
    if(!data->shouldLoad){
        data->status = 0;

        return 0;

    }
    if(data->url == NULL){
        fail("Failed At Point 1");
        data->result =  "local color = change_color(255, 0,0,255)\ndraw_text(\"Error\", 10, 10, 255, color)";
        data->status = -1;
        return 1;
    }
    naettReq* req = naettRequest(data->url, naettMethod("GET"), naettHeader("accept", "*/index.lua*"));
    if(req == NULL){
        fail("Failed At Point 3");
        data->status = 1;
        return 1;
    }
    naettRes* res = naettMake(req);

    while (!naettComplete(res)) {
        thrd_yield(); 
    }
    int status = naettGetStatus(res);

    if(status < 0){
        fail("Failed At Point 2");
        fail("Request Failed, Error Code %d\n", status);
        data->result = "local color = change_color(255, 0,0,255)\ndraw_text(\"Error\", 10, 10, 255, color)";
        data->status = -2;
        return 1;
    }
    int bodyLength = 0;
    const char* body = naettGetBody(res, &bodyLength);
    naettClose(res);
    naettFree(req);
    data->result = strdup(body);
    pass("%s\n", data->result);
    data->status = 0;
    data->shouldLoad = false;
    return 0;
}