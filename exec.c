#include "microshell.h"



int		exec_simple(char **av, char **ep)	
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == CHILD)
	{
		if (execve(*av, av, ep) == -1)
		{
			display_error(EXECVE, *av);
			exit(FAILURE);
		}	
	}
	else
		if (waitpid(pid, &status, 0) == -1)
			return (FAILURE);
	return (SUCCESS);
}

int     simple_cmd(char **av, int start, int end, int *i_ptr, char **ep)
{
	(void)end;
//	display_simple(av, start, end);
//	if (strcmp(*(av + start), "cd") == 0)
//	exec_cd(av);
//	else
	exec_simple(av + start, ep);
	(*i_ptr)++;
	return (SUCCESS);
}
