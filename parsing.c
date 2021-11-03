#include "microshell.h"

int		is_pipeline(char **av, int *i)
{
	int	ret;
	
	ret = FALSE;
	while (av[*i] != NULL)
	{
		if (strcmp(av[*i], "|") == 0)
			ret = TRUE;
		*i = *i + 1;
	}
	return (ret);
}

void    replace_smc(int ac, char **av)
{
    int i;

    i = 0;
    while (i != ac)
    {
        if (strcmp(av[i], ";") == 0)
            av[i] = NULL;
        i++;
    }
}

void	replace_pipes(char **av, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (strcmp(av[i], "|") == 0)
			av[i] = NULL;
		i++;
	}
}
