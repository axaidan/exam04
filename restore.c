#include "microshell.h"

void	backup_std(int *std_bckp)
{
	std_bckp[STDIN_FILENO] = dup(STDIN_FILENO);
	std_bckp[STDOUT_FILENO] = dup(STDOUT_FILENO);
}

void	restore_std(int *std_bckp)
{
	dup2(std_bckp[STDIN_FILENO], STDIN_FILENO);
	close(std_bckp[STDIN_FILENO]);
	dup2(std_bckp[STDOUT_FILENO], STDOUT_FILENO);
	close(std_bckp[STDOUT_FILENO]);
}
