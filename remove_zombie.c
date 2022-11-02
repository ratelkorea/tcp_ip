#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);       // 자식 프로세스 종료 확인 , 실패하면 -1 반환
    if(WIFEXITED(status))   // true
    {
        printf("Removed proc id %d \n",id);                   // 프로세스 id 출력
        printf("Child send: %d \n", WEXITSTATUS(status));    // 종료코드
    }
}

int main(int argc, char * argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;   
    sigemptyset(&act.sa_mask);           // 0 으로 초기화
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);         // 자식 프로세스가 종료 되면 함수 실행

    pid = fork();
    if(pid == 0)
    {
        puts("Hi ! I'm child process");
        sleep(10);
        return 12;
    }
    else
    {
        printf("Child proc id: %d \n", pid);
        pid = fork();
        if(pid == 0)
        {
            puts("Hi! i,m child process");
            sleep(10);
            exit(24);
        }
        else
        {
            printf("Child proc id: %d \n", pid);
            for(int i = 0; i < 5; i++)
            {
                puts("wait....");
                sleep(5);
            }
        }
    }
    return 0;
    
}