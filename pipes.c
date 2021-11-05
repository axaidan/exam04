#include "microshell.h"

int		count_cmds(char **av, int start, int end)
{
	int	i;
	int	cmds;

	i = start;
	cmds = 0;
	while (i <= end)
	{
		if (av[i] == NULL)
			cmds++;
		i++;
	}
	return (cmds);
}

int		wait_all_pids(int *pids, int cmds_n)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmds_n)
		waitpid(pids[i++], &status, 0);
	return (SUCCESS);
}

void	assign_in_out_tbc(int i, int cmds_n, int *in_out_tbc, int *fds)
{
	if (i < cmds_n - 1)
	{
		in_out_tbc[OUT] = fds[1];
		in_out_tbc[TBC] = fds[0];
	}
	else
	{
		in_out_tbc[OUT] = STDOUT_FILENO;
		in_out_tbc[TBC] = -1;
	}
}

int	add_child_proc(int *in_out_tbc, char **av, char **ep, int i_av)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		write(STDERR_FILENO, "error fork\n", 11);
	else if (pid == CHILD)
	{
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		if (dup2(in_out_tbc[IN], STDIN_FILENO) == -1
			|| dup2(in_out_tbc[OUT], STDOUT_FILENO) == -1)
		{
			write(STDERR_FILENO, "error dup2\n", 11);
			exit(FAILURE);
		}
		if (execve(*(av + i_av), av + i_av, ep) == -1)
		{
			write(STDERR_FILENO, "error exec\n", 11);
			exit(FAILURE); // display_cmd_not_found
		}
	}
	return (pid);
}

int     pipeline_cmd(char **av, int start_of_pipe, int end_of_pipe, int *i_ptr, char **ep)
{
	int	std_bckp[2];
	int fds[2];
	int	in_out_tbc[3];
	int	i;
	int	cmds_n;
	int	cmds_i;
	int	*pids;

	replace_pipes(av, start_of_pipe, end_of_pipe);
	in_out_tbc[IN] = STDIN_FILENO;
	i = start_of_pipe;
	cmds_n = count_cmds(av, start_of_pipe, end_of_pipe);
	pids = malloc(sizeof(int) * cmds_n); // check return;
	cmds_i = 0;
	backup_std(std_bckp);
	while (i < end_of_pipe)
	{
		if (cmds_i < cmds_n - 1)
		{
			if (pipe(fds) == -1)
			{
				write(STDERR_FILENO, "error pipe\n", 11);
				return (FAILURE);	// display fatal error;
			}
		}
		assign_in_out_tbc(cmds_i, cmds_n, in_out_tbc, fds);
		pids[cmds_i] = add_child_proc(in_out_tbc, av, ep, i);
		close(in_out_tbc[IN]);
		if (cmds_i < cmds_n - 1)
			close(fds[1]);
		in_out_tbc[IN] = fds[0];
		while (av[i] != NULL)
			i++;
		i++;
		cmds_i++;
	}
	close(fds[0]);
	restore_std(std_bckp);
	wait_all_pids(pids, cmds_n);
	// free(pids);
	(*i_ptr)++;
	return (SUCCESS);
}

int     pipeline_display(char **av, int start, int end, int *i_ptr, char **ep)
{
	(void)ep;
	int	i;

	replace_pipes(av, start, end);
	display_pipeline(av, start, end);
	i = start;
	while (i < end)
	{
		display_each_pipe(av, &i);
	}
	(*i_ptr)++;
	return (SUCCESS);
}
