#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char get_state(int pid) {
    char path[64], line[256];
    char *p;
    FILE *fp;

    sprintf(path, "/proc/%d/stat", pid);
    fp = fopen(path, "r");
    if (fp == NULL)
        return '-';

    fgets(line, sizeof(line), fp);
    fclose(fp);

    p = strrchr(line, ')');
    return p[2];
}

int main() {
    int pids[5];
    int i, status, zombies = 0;
    int pid;

    printf("ZOMBIE PROCESS DEMO\n");
    printf("-------------------\n");
    fflush(stdout);

    for (i = 0; i < 5; i++) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            printf("Child %d created, PID: %d\n", i + 1, getpid());
            exit(i + 1);
        }
        pids[i] = pid;
    }

    sleep(2);

    printf("\nBefore cleanup:\n");
    printf("PID\tSTATE\n");
    for (i = 0; i < 5; i++) {
        char s = get_state(pids[i]);
        printf("%d\t%c\n", pids[i], s);
        if (s == 'Z')
            zombies++;
    }
    printf("Total zombies: %d\n", zombies);

    printf("\nCleaning zombies...\n");
    for (i = 0; i < 5; i++) {
        waitpid(pids[i], &status, 0);
        printf("PID %d cleaned, exit code %d\n", pids[i], WEXITSTATUS(status));
    }

    printf("\nAfter cleanup:\n");
    for (i = 0; i < 5; i++) {
        if (get_state(pids[i]) == '-')
            printf("PID %d removed\n", pids[i]);
        else
            printf("PID %d still exists\n", pids[i]);
    }

    return 0;
}
