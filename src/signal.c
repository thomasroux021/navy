/*
** EPITECH PROJECT, 2019
** signal.c
** File description:
** signal
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
