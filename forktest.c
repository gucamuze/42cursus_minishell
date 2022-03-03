#include "includes/minishell.h"

int main()
{
	int	pid = fork();

	printf("pid = %d\n", pid);
	if (!pid)
	{
		printf("child doing stuff..\n");
		sleep(1);
		return (127);
	}
	else
	{
		int status = 0;
		printf("parent waiting...\n");
		waitpid(0, &status, 0);
		printf("parent done waiting, child exited with status %d\n", status / 256);
	}
}