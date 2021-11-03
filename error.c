#include "microshell.h"

void	display_error(int error, char *info)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	if (error == EXECVE)
	{
		ft_putstr_fd("cannot execute ", STDERR_FILENO);
		ft_putendl_fd(info, STDERR_FILENO);
	}
}
