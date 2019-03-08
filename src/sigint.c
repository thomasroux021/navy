/*
** EPITECH PROJECT, 2019
** sigint.c
** File description:
** handke sigint
*/

#include "my.h"

int miss(char c)
{
    if (c == 'o')
        return (0);
    if (c != '.')
        return (1);
    return (0);
}

void handle_sigint(int sig)
{
    usleep(100);
    kill(glob->t_pid, SIGUSR2);
    glob->t_pid = -2;
}

void my_sigint(int sig, siginfo_t *si, void *context)
{
    if (glob->t_pid == 0)
        glob->t_pid = si->si_pid;
    else if (glob->t_pid != si->si_pid && glob->t_pid != -2)
        glob->t_pid = -1;
    else
        glob->t_pid = -2;
}

char **check_col(char **e_map, char *act)
{
    if (glob->res == 1 || glob->res == 3) {
        my_printf("%s: hit\n\n", act);
        e_map[act[1] - 49][act[0] - 65] = 'x';
    }
    if (glob->res == 2) {
        my_printf("%s: missed\n\n", act);
        if (e_map[act[1] - 49][act[0] - 65] != 'x')
            e_map[act[1] - 49][act[0] - 65] = 'o';
    }
    return (e_map);
}

char **check_win(char **map, char **e_map)
{
    if (glob->res == 3 && e_map != NULL) {
        print_map(map, "my positions:\n");
        print_map(e_map, "enemy's positions:\n");
        my_putstr("I won\n\n");
        return (NULL);
    }
    return (e_map);
}
