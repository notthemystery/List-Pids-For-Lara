#include <stdio.h>
#include <stdlib.h>
#include "libproc.h"
#include "proc_info.h"
#include <string.h>
#include <signal.h>
#include "processlist.h"

bool run = false;

int main() {
    if (run == true) {
        refresh_processes();
    }
}

void refresh_processes() {

    if (run == true) {

        int bufsize = proc_listallpids(NULL, 0);

        pid_t *pids = malloc(bufsize);

        if (!pids)
            return 1;

        int numberOfPids = proc_listallpids(pids, bufsize);

        FILE *f = fopen("processes.json", "w");

        if (!f) {
            free(pids);
            return 1;
        }

        fprintf(f, "[\n");

        int first = 1;

        for (int i = 0; i < numberOfPids; i++) {

            char name[PROC_PIDPATHINFO_MAXSIZE] = {0};

            if (proc_name(pids[i], name, sizeof(name)) > 0) {

                fprintf(
                    f,
                    "%s  {\"pid\": %d, \"name\": \"%s\"}",
                    first ? "" : ",\n",
                    pids[i],
                    name
                );

                first = 0;
            }
        }

        fprintf(f, "\n]\n");

        fclose(f);

        free(pids);
    }

    return 0;
}

int runcmd(pid_t pid, const char *cmd) {

    if (strcmp(cmd, "unalive") == 0) {
        return kill(pid, SIGKILL);

    } else if (strcmp(cmd, "pause") == 0) {
        return kill(pid, SIGSTOP);

    } else if (strcmp(cmd, "resume") == 0) {
        return kill(pid, SIGCONT);
    }

    return -1;
}


