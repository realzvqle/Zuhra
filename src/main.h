#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED




#include "../raylib/raylib.h"
#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
#include "../naett/naett.h"
#include "../tinycthread/tinycthread.h"


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



#if defined(_WIN32) || defined(_WIN64)
#define _AMD64_
#include <synchapi.h>
inline void cross_platform_sleep(int milliseconds) {
    Sleep(milliseconds * 1000);
}
#else
#include <unistd.h>
inline void cross_platform_sleep(int milliseconds) {
    usleep(milliseconds * 1000);
}
#endif

#define pass(format, ...) printf("[+] " format, ##__VA_ARGS__)
#define fail(format, ...) printf("[-] " format, ##__VA_ARGS__)
#define info(format, ...) printf("[!] " format, ##__VA_ARGS__)


typedef struct _state{
    Font currentFont;
    bool isLoaded;
    Color backgroundColor;
    char* currentFile;
    char buffer[512];
    bool reload;
} state;






#endif