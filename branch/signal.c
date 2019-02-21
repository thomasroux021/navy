/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** terminals speaking
*/

#include "../include/my.h"

void pos2_hub(char *pid_pos1, char *pos)
{
    int pos1_pid = my_getnbr(pid_pos1);
    pid_t cur_pid = getpid();

    if (pos[0] == 'p' && pos[1] == 'o' && pos[2] == 's' && pos[3] == '2') {
        my_printf("my_pid: %d\n", cur_pid);
        if (kill(pos1_pid, SIGUSR1) == 0)
            my_printf("successfully connected\n");
    } else
        my_printf("Error: incorrect syntax\n");
}

static void sigaction_bis(int sig, siginfo_t *siginfo, void *context) {
    my_printf("enemy connected\n");
}

void pos1_hub(char *pos)
{
    struct sigaction act;
    pid_t cur_pid;

    if (pos[0] == 'p' && pos[1] == 'o' && pos[2] == 's' && pos[3] == '1') {
        cur_pid = getpid();
        my_printf("my_pid: %d\n", cur_pid);
        my_printf("waiting for enemy connection...\n\n");
        act.sa_handler = NULL;
        sigemptyset(&act.sa_mask);
        act.sa_sigaction = &sigaction_bis;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, NULL);
        pause();
    } else
        my_printf("Error: incorrect syntax\n");
}
