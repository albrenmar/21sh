# define LEER 0
# define ESCRIBIR 1

void		execute_pipe(void)
{
	pid_t	pid0;
	pid_t	pid1;
	pid_t	pid2;

	pipe(descrf);
	pipe(descrf_two);
	pid0 = fork();
	if (pid0 == 0)
	{
		// dprintf(2, "PID fils = %d\n", getpid());
		close(descrf[0]);
		dup2(descrf[1], 1);
		close(descrf[1]);
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_two();
	}
	else
	{
		close(descrf[1]);
		wait(NULL);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_three();
	}
	else
	{
		close(descrf_two[1]);
		wait(NULL);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_four();
	}
	else
	{
		close(descrf_two[0]);
		wait(NULL);
	}
	close(descrf[0]);
	close(descrf[1]);
	close(descrf_two[0]);
	close(descrf_two[1]);
}

void		execute_pipe(void)
{
	pid_t	pid0;
	pid_t	pid1;
	pid_t	pid2;

	pipe(descrf);
	pipe(descrf_two);
	pid0 = fork();
	if (pid0 == 0)
	{
		// dprintf(2, "PID fils = %d\n", getpid());
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_two();
	}
	else
	{
		close(descrf_two[1]);
		wait(NULL);
	}
	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
	pipe(descrf_two);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_three();
	}
	else
	{
		close(descrf_two[1]);
		wait(NULL);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_four();
	}
	else
	{
		close(descrf_two[0]);
		wait(NULL);
	}
	close(descrf[0]);
	close(descrf[1]);
	close(descrf_two[0]);
	close(descrf_two[1]);
}
