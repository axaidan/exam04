#include "microshell.h"

int main(int ac, char *av[], char *ep[])
{
    (void)ep;
	int	i;
	int	start;

    replace_smc(ac, av);
    display_args(ac, av);
	i = 1;
	while (i < ac)
	{
		start = i;
		if (is_pipeline(av, &i))
			exec_pipeline(av, start, i, &i);
		else
			exec_simple(av, start, i, &i);
	}
    return (SUCCESS);
}
