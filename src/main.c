/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

void my_handler(int sig, siginfo_t *si, void *context)
{
    if (glob->t_pid == 0)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
}

void my_sig(int sig, siginfo_t *si, void *context)
{
    if (!glob->t_pid)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
    glob->res += 1;
}

void my_sig_two(int sig, siginfo_t *si, void *context)
{
    if (!glob->t_pid)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
    glob->end += 1;
}

void my_sig_act(int sig, siginfo_t *si, void *context)
{
    if (!glob->t_pid)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
    if (!glob->end)
        glob->line += 1;
    else if (glob->end == 1)
        glob->col += 1;
}

void my_sig_two_act(int sig, siginfo_t *si, void *context)
{
    if (!glob->t_pid)
        glob->t_pid = si->si_pid;
    if (glob->t_pid != si->si_pid)
        glob->t_pid = -1;
    glob->end += 1;
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

int lose(char **map, char **e_map)
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
    print_map(e_map, "enemy's positions:\n");
    my_putstr("Enemy won\n");
    return (1);
}

char **send_att(char *act, char **e_map, int pid, char **map)
{
    struct sigaction sig;
    struct sigaction sig_two;

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
    if (glob->res == 3) {
        print_map(map, "my positions:\n");
        print_map(e_map, "enemy's positions:\n");
        my_putstr("I won\n");
        return (NULL);
    }
    return (e_map);
}

char **e_att(char **map, int pid, char **e_map)
{
    struct sigaction sig;
    struct sigaction sig_two;
    int res;

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

int play(char **map, char **e_map, t_glob *glob, int tour)
{
    char *act = "ok";

    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n");
    if (!tour) {
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid, map)) == NULL)
            return (0);
        if ((map = e_att(map, glob->t_pid, e_map)) == NULL)
            return (1);
    } else {
        if ((map = e_att(map, glob->t_pid, e_map)) == NULL)
            return (1);
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid, map)) == NULL)
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
    return (84);
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
