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

/*	libft.c */
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

/*	error.c */
void	display_error(int error, char *info);

/*  debug.c */
void	display_args(int ac, char **av);
void	display_pipeline(char **av, int start, int end);
void	display_simple(char **av, int start, int end);
void	display_each_pipe(char **av, int *start);

/*  parsing.c */
void    replace_smc(int ac, char **av);
void    replace_pipes(char **av, int start, int end);
int		is_pipeline(char **av, int *i);

/*	pipes.c */
int		pipeline_cmd(char **av, int start, int end, int *i_ptr, char **ep);
int		pipeline_display(char **av, int start, int end, int *i_ptr, char **ep);

/*	exec.c */
int		simple_cmd(char **av, int start, int end, int *i_ptr, char **ep);

/*	restore.c */
void	backup_std(int *std_bckp);
void	restore_std(int *std_bckp);

#endif
