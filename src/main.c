/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void my_handler(int sig, siginfo_t *si, void *context)
{
    if (!glob->t_pid)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
}

/*void my_handler(int sig, siginfo_t *si, void *context)
{
    if (!t_pid)
        t_pid = si->si_pid;
    if (t_pid != si->si_pid)
        t_pid = -1;
}
*/

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
    pause();
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
    usleep(300);
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

int play(char **map, char **e_map, t_glob *glob, int tour)
{
    char *act = "ok";

    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n");
    if (!tour) {
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid)) == NULL)
            return (0);
        //enemy attack
        if ((map = e_att(map, glob->t_pid)) == NULL)
            return (1);
    } else {
        //enemy attack
        if ((map = e_att(map, glob->t_pid)) == NULL)
            return (1);
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid)) == NULL)
            return (0);
    }
    return (3);
}

int player(char **map, int pid, int tour, t_glob *glob)
{
    char **e_map = create_map();
    int ret;

    (pid != getpid()) ? (glob->t_pid = pid) : (pid = glob->t_pid);
    if (e_map == NULL)
        return (84);
    while (1) {
        if (glob->t_pid == -1)
            return (84);
        if ((ret = play(map, e_map, glob, tour)) != 3)
            return (ret);
    }
    return (0);
}

void req_co(pid_t pid)
{
    kill(pid, SIGUSR2);
    my_putstr("successfully connected\n\n");
}

void send_co(void)
{
    struct sigaction act;

    my_putstr("waiting for enemy connection...\n\n");
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = my_handler;
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
    t_glob *glob = malloc(sizeof(t_glob));

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
    if ((str = parser_file(av[1 + ((ac == 3) ? 1 : 0)])) == NULL ||
        map == NULL || glob == NULL)
        return (84);
    if ((map = fill_map(map, str)) == NULL || (ac > 2 && my_getnbr(av[1]) < 0))
        return (84);
    glob->t_pid = 0;
    my_putstr("my_pid: ");
    my_put_nbr(getpid());
    my_putchar('\n');
    pid = (ac == 3) ? my_getnbr(av[1]) : getpid();
    (ac == 3) ? req_co(pid) : send_co();
    if (player(map, pid, tour, glob) == -1)
        return (84);
}
