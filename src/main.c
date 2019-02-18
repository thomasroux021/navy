/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void my_handler(int sig)
{
    printf("%d\n", sig);
    if (sig == SIGUSR1)
        printf("despacito\n");
}

int main(int ac, char **av)
{
    /*if (ac == 1) {
        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = my_handler;
        sigaction(SIGUSR1, &act ,NULL);
        pid_t pid = getpid();
        kill(pid, SIGUSR1);
        printf("pid %d\n", pid);
        while(1);
    } else {
        while (kill(atoi(av[1]), SIGUSR1)) {
            printf("%s\n", av[2]);
            usleep(150000);
        }
        }*/
    if (ac < 2 || ac > 3 || (ac == 2 && !my_strcmp(av[1], "-h")))
        if (print_help(ac, av) == -1)
            return (84);
    if (parser_file(av[1 + ((ac == 3) ? 1 : 0)]) == -1)
        return (84);
}
