/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void my_handler(int sig, siginfo_t *si, void *context)
{
    if (!t_pid)
        t_pid = si->si_pid;
    if (t_pid != si->si_pid) {
        my_putstr("wrong PID\n");
        t_pid = -1;
    }
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

int lose(char **map)
{
    int boat = 0;

    for (int i = 0; map[i] != NULL; i += 1) {
        for (int j = 0; map[i][j]; j += 1) {
            (map[i][j] >= 48 && map[i][j] <= 53) ? boat += 1 : 0;
        }
    }
    if (boat)
        return (0);
    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n\n");
    my_putstr("Enemy won\n");
    return (1);
}

char **send_att(char *act, char **e_map, int pid)
{
    struct sigaction sig;
    int res = 0;

    for (int i = 0; i < act[0] - 64; i += 1)
        while (kill(pid, SIGUSR1));
    for (int j = 0; j < act[0] - 48; j += 1)
        while (kill(pid, SIGUSR2));
    while (kill(pid, SIGUSR1));
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = my_handler;
    while (sigaction(SIGUSR2, &sig, NULL))
        if (!sigaction(SIGUSR1, &sig, NULL))
            res += 1;
    if (res == 1) {
        my_putstr(act);
        my_putstr(": hit\n\n");
        e_map[act[0] - 65][act[1] - 49] = 'x';
    }
    if (res == 2) {
        my_putstr(act);
        my_putstr(": missed\n\n");
        e_map[act[0] - 65][act[1] - 49] = 'o';
    }
    if (res == 3) {
        print_map(map, "my positions:\n");
        print_map(e_map, "enemy's positions:\n\n");
        my_putstr("I won\n");
        return (NULL);
    }
    return (e_map);
}

char **e_att(char **map, int pid)
{
    int line = 0;
    int col = 0;
    struct sigaction sig;
    int res;

    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = my_handler;
    my_putstr("waiting for enemy's attack...\n");
    while (1) {
        if (col && !sigaction(SIGUSR1, &sig, NULL))
            break;
        if (!sigaction(SIGUSR1, &sig, NULL))
            line += 1;
        if (!sigaction(SIGUSR2, &sig, NULL))
            col += 1;
    }
    res = (map[line - 1][col - 1] != '.') ? 1 : 2;
    map[line - 1][col - 1] = (map[line - 1][col - 1] != '.') ? 'x' : 'o';
    my_putchar(line + 64);
    my_putchar(col + 48);
    (res == 1) ? my_putstr(": hit\n\n") : my_putstr(": missed\n\n");
    if (lose(map))
        res = 3;
    for (int i = 0; i < res; i += 1)
        while (kill(pid, SIGUSR1));
    while (kill(pid, SIGUSR2));
    return (map);
}

int play(char **map, char **e_map, int pid)
{
    char *act = "ok";
    int tour = (pid == getpid()) ? 0 : 1;

    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n");
    if (!tour) {
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, pid)) == NULL)
            return (0);
        //enemy attack
        if ((map = e_att(map, pid)) == NULL)
            return (1);
    } else {
        //enemy attack
        if ((map = e_att(map, pid)) == NULL)
            return (1);
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, pid)) == NULL)
            return (0);
    }
    return (3);
}

int player(char **map, int pid)
{
    char **e_map = create_map();
    int ret;

    if (pid != getpid())
        t_pid = pid;
    if (e_map == NULL)
        return (84);
    while (1) {
        if (t_pid == -1)
            return (84);
        if ((ret = play(map, e_map, pid)) != 3)
            return (ret);
    }
    return (0);
}

int main(int ac, char **av)
{
    char *str;
    char **map = create_map();
    pid_t pid;

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
    t_pid = 0;
    if (ac < 2 || ac > 3 || (ac == 2 && !my_strcmp(av[1], "-h")))
        if (print_help(ac, av) == -1)
            return (84);
    if ((str = parser_file(av[1 + ((ac == 3) ? 1 : 0)])) == NULL || map == NULL)
        return (84);
    if ((map = fill_map(map, str)) == NULL || (ac > 2 && my_getnbr(av[1]) < 0))
        return (84);
    my_putstr("my_pid: ");
    my_put_nbr(getpid());
    my_putchar('\n');
    pid = (ac == 3) ? my_getnbr(av[1]) : getpid();
    if (player(map, pid) == -1)
        return (84);
}
