#include "microshell.h"

void    display_args(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		printf("av[%3d]\t\t=\t\"%30.30s\"\n", i, av[i]);
		i++;
	}
	printf("av[%3d]\t\t=\t\"%30.30s\"\n\n", i, av[i]);
}

void	display_pipeline(char **av, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (av[i] == NULL)
			printf("pipeline[%3d]\t=\t\"%30.30s\"\n", i/* - start*/, "(NULL)");
		else
			printf("pipeline[%3d]\t=\t\"%30.30s\"\n", i/* - start*/, av[i]);
		i++;
	}
	if (av[i] == NULL)
		printf("pipeline[%3d]\t=\t\"%30.30s\"\n\n", i/* - start*/, "(NULL)");
	else
		printf("pipeline[%3d]\t=\t\"%30.30s\"\n\n", i/* - start*/, av[i]);
}

void	display_simple(char **av, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (av[i] == NULL)
			printf("simple_c[%3d]\t=\t\"%30.30s\"\n", i - start, "(NULL)");
		else
			printf("simple_c[%3d]\t=\t\"%30.30s\"\n", i - start, av[i]);
		i++;
	}
	if (av[i] == NULL)
		printf("simple_c[%3d]\t=\t\"%30.30s\"\n\n", i - start, "(NULL)");
	else
		printf("simple_c[%3d]\t=\t\"%30.30s\"\n\n", i - start, av[i]);
}

void	display_each_pipe(char **av, int *start_of_pipe)
{
	int	i;

	i = *start_of_pipe;
	while (av[i] != NULL)
	{
		if (av[i] == NULL)
			printf("pipe[%3d]\t=\t\"%30.30s\"\n", i/* - start*/, "(NULL)");
		else
			printf("pipe[%3d]\t=\t\"%30.30s\"\n", i/* - start*/, av[i]);
		i++;
	}
	if (av[i] == NULL)
		printf("pipe[%3d]\t=\t\"%30.30s\"\n\n", i/* - start*/, "(NULL)");
	else
		printf("pipe[%3d]\t=\t\"%30.30s\"\n\n", i/* - start*/, av[i]);
	*start_of_pipe = i + 1;

}
