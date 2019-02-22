/*
** EPITECH PROJECT, 2019
** attack.c
** File description:
** send/get attack
*/

#include "my.h"

char **sig_send_att(char **e_map, char *act)
{
    struct sigaction sig;
    struct sigaction sig_two;

    sig.sa_flags = SA_SIGINFO;
    sig_two.sa_flags = SA_SIGINFO;
    sig_two.sa_sigaction = &my_sig_two;
    sig.sa_sigaction = &my_sig;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig_two, NULL);
    while (!glob->end)
        pause();
    if (glob->res == 1 || glob->res == 3) {
        my_printf("%s: hit\n\n", act);
        e_map[act[1] - 49][act[0] - 65] = 'x';
    }
    if (glob->res == 2) {
        my_printf("%s: missed\n\n", act);
        e_map[act[1] - 49][act[0] - 65] = 'o';
    }
    return (e_map);
}

char **send_att(char *act, char **e_map, int pid, char **map)
{
    for (int i = 0; i < act[0] - 64; i += 1) {
        kill(pid, SIGUSR1);
        usleep(100);
    }
    kill(pid, SIGUSR2);
    for (int j = 0; j < act[1] - 48; j += 1) {
        kill(pid, SIGUSR1);
        usleep(100);
    }
    kill(pid, SIGUSR2);
    glob->res = 0;
    glob->end = 0;
    e_map = sig_send_att(e_map, act);
    if (glob->res == 3) {
        print_map(map, "my positions:\n");
        print_map(e_map, "enemy's positions:\n");
        my_putstr("I won\n");
        return (NULL);
    }
    return (e_map);
}

char **msg_e_att(char **map, int pid, char **e_map)
{
    int res;

    while (glob->end != 2)
        pause();
    res = (map[glob->col - 1][glob->line - 1] != '.') ? 1 : 2;
    map[glob->col - 1][glob->line - 1] = (map[glob->col - 1][glob->line - 1] !=
        '.') ? 'x' : 'o';
    my_putchar(glob->line + 64);
    my_putchar(glob->col + 48);
    (res == 1) ? my_putstr(": hit\n\n") : my_putstr(": missed\n\n");
    if (lose(map, e_map))
        res = 3;
    for (int i = 0; i < res; i += 1) {
        kill(pid, SIGUSR1);
        usleep(100);
    }
    kill(pid, SIGUSR2);
    if (res == 3)
        return (NULL);
    return (map);
}

char **e_att(char **map, int pid, char **e_map)
{
    struct sigaction sig;
    struct sigaction sig_two;

    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = &my_sig_act;
    sig_two.sa_flags = SA_SIGINFO;
    sig_two.sa_sigaction = &my_sig_two_act;
    glob->col = 0;
    glob->line = 0;
    glob->end = 0;
    my_putstr("waiting for enemy's attack...\n");
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig_two, NULL);
    return (msg_e_att(map, pid, e_map));
}

char *attack(void)
{
    char *act;

    my_putstr("attack: ");
    if ((act = get_next_line(0)) == NULL)
        return (NULL);
    if (my_strlen(act) != 2 || act[0] < 65 || act[0] > 72 ||
        act[1] < 49 || act[1] > 56) {
        my_putstr("wrong position\n");
        return (attack());
    }
    return (act);
}
