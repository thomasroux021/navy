/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H
#define MY_H

#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../src/lib/my/lib.h"

#ifndef READ_SIZE
#define READ_SIZE 1
#endif

typedef struct s_glob
{
    int t_pid;
    int res;
    int end;
    int col;
    int line;
} t_glob;

t_glob *glob;

void handle_sigint(int sig);
void my_sigint(int sig, siginfo_t *si, void *context);
char **check_win(char **map, char **e_map);
char **check_col(char **e_map, char *act);

int hit(char c);
char *parser_file(char *file);
int len_boat(char **map);
char **create_map(void);

int print_help(int ac, char **av);
void print_map(char **map, char *str);

char **fill_map(char **map, char *str);

char *get_next_line(int fd);

void my_sig_two_act(int sig, siginfo_t *si, void *context);
void my_sig_act(int sig, siginfo_t *si, void *context);
void my_sig_two(int sig, siginfo_t *si, void *context);
void my_sig(int sig, siginfo_t *si, void *context);
void my_handler(int sig, siginfo_t *si, void *context);

char *attack(void);
char **e_att(char **map, int pid, char **e_map);
char **send_att(char *act, char **e_map, int pid, char **map);

int lose(char **map, char **e_map);
int player(char **map, int pid, int tour, t_glob *glob);
#endif
