
void	execute_pipe_two(t_ast *ast_cmd, int *prev_descrf)
{
	pid_t	pid1;
	pid_t	pid2;
	char	**tab_cmd;
	int		descrf[2];
	int		descrf_two[2];
	int		i;
	char	*path;
	char	**tablist;

	i = 0;
	path = get_env_string("PATH");
	tablist = ft_strsplit(path, ':');
	pipe(descrf);
	pipe(descrf_two);
	if (ast_cmd && (ast_cmd->next_token == 1))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[ESCRIBIR], 1);
			close(descrf[LEER]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
	}
	close(descrf[ESCRIBIR]);
	if (ast_cmd && (ast_cmd->next_token == 1))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[LEER], 0);
			dup2(descrf_two[ESCRIBIR], 1);
			close(descrf_two[LEER]);
			close(descrf[ESCRIBIR]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
	}
	descrf[LEER] = descrf_two[LEER];
	close(descrf_two[ESCRIBIR]);
	pipe(descrf_two);
	if (ast_cmd && (ast_cmd->next_token == 1))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[LEER], 0);
			dup2(descrf_two[ESCRIBIR], 1);
			close(descrf_two[LEER]);
			close(descrf[ESCRIBIR]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
	}
	close(descrf_two[ESCRIBIR]);
	if (ast_cmd && (ast_cmd->next_token == 0))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(descrf_two[LEER], 0);
			//close(descrf[ESCRIBIR]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		close(descrf_two[0]);
		close(descrf_two[1]);
		close(descrf[0]);
		close(descrf[1]);
		wait(&pid2);
	}
}
