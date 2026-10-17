
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void cleanup(int sig)
{
    printf("\nCleanup: Signal %d received.\n", sig);
    printf("Saving cached state and shutting down gracefully.\n");
    exit(0);
}

int main()
{
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    pid_t pid = fork();

    if (pid == 0) {
        printf("Worker started. PID = %d\n", getpid());
        while (1)
            sleep(1);
    }
    else if (pid > 0) {
        printf("Supervisor started. Worker PID = %d\n", pid);
        sleep(5);

        printf("Watchdog: Terminating worker using kill().\n");
        kill(pid, SIGTERM);

        wait(NULL);
        printf("Worker terminated. Supervisor continues.\n");
    }
    else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
