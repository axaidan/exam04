#include "pipex.h"

static int	wait_all_pids(t_config *c)
{
	int		i;
	int		status;
	int		return_value;

	i = 0;
	return_value = 0;
	while (i < c->nb_cmd)
	{
		if (waitpid(c->pids[i++], &status, 0) == -1)
			close_config_and_exit(c, "waitpid", strerror(errno));
		if (WIFEXITED(status))
			return_value = WEXITSTATUS(status);
	}
	return (return_value);
}

static int	add_child_proc(int *in_out_tbc, char **envp, t_config *c, int i)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (display_err_ret_false("fork", strerror(errno)));
	else if (pid == 0)
	{
		if (in_out_tbc[IN] == -1 || in_out_tbc[OUT] == -1)
			close_config_exit_error(c, 1, NULL, NULL);
		if (in_out_tbc[TBC] >= 0)
			close(in_out_tbc[TBC]);
		if (dup2(in_out_tbc[IN], STDIN_FILENO) == -1
			|| dup2(in_out_tbc[OUT], STDOUT_FILENO) == -1)
			close_config_exit_error(c, errno, "pipe", strerror(errno));
		if (c->cmds_status[i] == FALSE)
			close_config_exit_error(c, 127, c->cmds[i][0], E_NO_CMD);
		if (execve(c->cmds[i][0], c->cmds[i], envp) == -1)
			close_config_exit_error(c, errno, c->cmds[i][0], strerror(errno));
	}
	return (pid);
}

static void	assign_in_out_tbc(t_config *c, int i, int *in_out_tbc, int *fds)
{
	if (i < c->nb_cmd - 1)
	{
		in_out_tbc[OUT] = fds[1];
		in_out_tbc[TBC] = fds[0];
	}
	else
	{
		in_out_tbc[OUT] = c->fd_out;
		in_out_tbc[TBC] = -1;
	}
}

int	execution(t_config *c, char **envp)
{
	int		fds[2];
	int		return_code;
	int		i;
	int		in_out_tbc[3];

	in_out_tbc[IN] = c->fd_in;
	i = 0;
	while (i < c->nb_cmd)
	{
		if (i < c->nb_cmd - 1)
		{
			if (pipe(fds) == -1)
				close_config_and_exit(c, "pipe", strerror(errno));
		}
		assign_in_out_tbc(c, i, in_out_tbc, fds);
		c->pids[i] = add_child_proc(in_out_tbc, envp, c, i);
		close(in_out_tbc[IN]);
		if (i < c->nb_cmd - 1)
			close(fds[1]);
		in_out_tbc[IN] = fds[0];
		i++;
	}
	close(fds[0]);
	return_code = wait_all_pids(c);
	return (return_code);
}
