//
// Created by ZHOUXIN on 2022/5/17.
//
#include "signal.h"
#include "stdio.h"
void handler_sigint(int signo){
    printf("recv SIGINT\n");
}

int main1(){
    signal(SIGINT, handler_sigint);
    while (1)
        ;
    return 0;
}
