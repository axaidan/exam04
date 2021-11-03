#include "microshell.h"

int     exec_pipeline(char **av, int start, int end, int *i_ptr)
{
	replace_pipes(av, start, end);
	display_pipeline(av, start, end);
	(*i_ptr)++;
	return (SUCCESS);
}	

int     exec_simple(char **av, int start, int end, int *i_ptr)
{
	display_simple(av, start, end);
	(*i_ptr)++;
	return (SUCCESS);
}
