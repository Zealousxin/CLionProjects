#include <stdio.h>
#include <unistd.h>
#include "setjmp.h"
#include "signal.h"


#define ENV_UNSAVE 0
#define ENV_SAVE   1

int flag_save_env = ENV_UNSAVE;
jmp_buf env;//保存跳转位置的栈信息
/*
 * 信号SIGRTMIN+15的处理函数
 */
void handler_sigrtmin15(int signo){
#if 0
    printf("recv SIGRTMIN+15\n");
    longjmp(env, 1);//返回env处
#else
    if(flag_save_env == ENV_UNSAVE){
        return;
    }
    printf("recv SIGRTMIN\n");
    sleep(4);
    printf("in %s, after sleep\n",__func__ );
    siglongjmp(env, 1);
#endif
}

/*
 * 信号SIGRTMAX-15的处理函数
 */
void handler_sigrtmax15(int signo){
#if 0
    printf("recv SIGRTMAX-15\n");
    longjmp(env, 2);//返回env处，注意第二个参数
#else
    if(flag_save_env == ENV_UNSAVE){
        return;
    }
    printf("recv SIGRTMAX\n");
    sleep(2);
    printf("in %s, after sleep\n",__func__ );
    siglongjmp(env, 2);
#endif
}


int main(){
    //设置返回点
#if 0
    //switch (setjmp(env)) {
#else
    switch (sigsetjmp(env, 1)) {
#endif
        case 0:
            printf("return 0\n");
            flag_save_env = ENV_SAVE;
            break;
        case 1:
            printf("return from SIGRTMIN\n");
            break;
        case 2:
            printf("return from SIGRTMAX\n");
            break;
        default:
            break;
    }
    //捕捉信号，安装信号处理函数
    signal(SIGRTMIN, handler_sigrtmin15);
    signal(SIGRTMAX, handler_sigrtmax15);
    while (1)
        ;
    return 0;
}
