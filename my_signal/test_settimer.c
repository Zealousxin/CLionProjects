#include "stdio.h"
#include "signal.h"
#include "sys/time.h"
#include "unistd.h"


void handler_sigtime(int signno)
{
    switch (signno) {
        case SIGALRM:
            printf("recv SIGALRM\n");
            break;
        case SIGVTALRM:
            printf("recv SIGVTALRM\n");
            break;
        default:
            break;
    }
}

int main(){
    struct itimerval value;

    signal(SIGALRM, handler_sigtime);
    signal(SIGVTALRM, handler_sigtime);

//    初始化value结构
    value.it_value.tv_sec = 1;//第一次1s触发信号
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 5;//第二次开始每5s触发信号
    value.it_interval.tv_usec = 0;

    //设置定时器
    setitimer(ITIMER_REAL, &value, NULL);
    setitimer(ITIMER_VIRTUAL, &value, NULL);
    while (1)
        ;
    return  0;
}
