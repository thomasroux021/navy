/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void handle_sigint(void)
{
    if (glob->t_pid && glob->t_pid != -1)
        kill(glob->t_pid, SIGINT);
}

void req_co(pid_t pid)
{
    while (kill(pid, SIGUSR2));
    my_putstr("successfully connected\n\n");
}

void send_co(void)
{
    struct sigaction act;

    my_putstr("waiting for enemy connection...\n\n");
    act.sa_flags = SA_SIGINFO;
    act.sa_handler = NULL;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = &my_handler;
    sigaction(SIGUSR2, &act, NULL);
    pause();
    my_putstr("enemy connected\n\n");
}

int main(int ac, char **av)
{
    char *str;
    char **map = create_map();
    pid_t pid;
    int tour = (ac == 3) ? 1 : 0;

    if (ac < 2 || ac > 3 || (ac == 2 && !my_strcmp(av[1], "-h")))
        if (print_help(ac, av) == -1)
            return (84);
    if ((str = parser_file(av[1 + ((ac == 3) ? 1 : 0)])) == NULL ||
        map == NULL || (glob = malloc(sizeof(t_glob))) == NULL)
        return (84);
    if ((map = fill_map(map, str)) == NULL || (ac > 2 && my_getnbr(av[1]) < 0))
        return (84);
    glob->t_pid = 0;
    my_printf("my_pid: %d\n", getpid());
    pid = (ac == 3) ? my_getnbr(av[1]) : getpid();
    (ac == 3) ? req_co(pid) : send_co();
    return (player(map, pid, tour, glob));
}
