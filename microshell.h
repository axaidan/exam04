#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include "structures.h"
# include "defines.h"

/*  debug.c */
void	display_args(int ac, char **av);
void	display_pipeline(char **av, int start, int end);
void	display_simple(char **av, int start, int end);

/*  parsing.c */
void    replace_smc(int ac, char **av);
void    replace_pipes(char **av, int start, int end);
int		is_pipeline(char **av, int *i);

/*	exec.c */
int		exec_pipeline(char **av, int start, int end, int *i_ptr);
int		exec_simple(char **av, int start, int end, int *i_ptr);

#endif
