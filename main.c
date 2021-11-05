#include "microshell.h"

int main(int ac, char *av[], char *ep[])
{
	int	i;
	int	start;

    replace_smc(ac, av);
    display_args(ac, av);
	i = 1;
	while (i < ac)
	{
		start = i;
		if (is_pipeline(av, &i))
			pipeline_cmd(av, start, i, &i, ep);
		else
			simple_cmd(av, start, i, &i, ep);
	}
    return (SUCCESS);
}
