/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void my_handler(int sig, siginfo_t *si, void *context)
{
    printf("%d\n", sig);
    if (sig == SIGUSR1)
        printf("despacito\n");
}

int main(int ac, char **av)
{
    char *str;
    char **map = create_map();

    /*if (ac == 1) {
        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = my_handler;
        sigaction(SIGUSR1, &act, NULL);
        pid_t pid = getpid();
        kill(pid, SIGUSR1);
        printf("pid %d\n", pid);
        while(1);
    } else {
        while (kill(atoi(av[1]), SIGUSR1)) {
            printf("wait\n");
            usleep(1500000);
        }
        }*/
    if (ac < 2 || ac > 3 || (ac == 2 && !my_strcmp(av[1], "-h")))
        if (print_help(ac, av) == -1)
            return (84);
    if ((str = parser_file(av[1 + ((ac == 3) ? 1 : 0)])) == NULL || map == NULL)
        return (84);
    if ((map = fill_map(map, str)) == NULL)
        return (84);
}
