//
// Created by ZHOUXIN on 2022/5/17.
//

#include <string.h>
#include "stdio.h"
#include "signal.h"
#include "stdlib.h"
#include "sys/types.h"

int main1(int argc, char **argv){
    int i, j;
    int signum = SIGTERM;//默认发送SIGTERM
    pid_t pid;

    //首先检查参数个数
    if (argc != 2 && argc != 4){
        printf("Usage: ./my_kill <-s signum> [PID]\n");
        exit(0);
    }

    //从命令行解析出信号编号
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-s")){
            signum = atoi(argv[i+1]);
            break;
        }
    }

    //解析出进程号
    if (argc == 2){
        pid = atoi(argv[1]);
    } else{
        for (int j = 0; j < argc; ++j) {
            if (j != i && j != i+1){
                pid = atoi(argv[j]);
                break;
            }
        }
    }

    if (kill(pid, signum) < 0){
        perror("kill");
        exit(1);
    }
    return 0;
}
