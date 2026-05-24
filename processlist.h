#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <stdbool.h>
#include <sys/types.h>

extern bool run;

int runcmd(pid_t pid, const char *cmd);
void refresh_processes(void);

#endif

