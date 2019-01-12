
char	*test_exist_fonction_ft(char *str, t_env *st_env)
{
	int		i;
	char	**tab_path;
	char	*next_str;

	i = 0;
	tab_path = NULL;
	tab_path = create_tab_path_ft(tab_path, st_env->env);
	while (tab_path && tab_path[i])
	{
		next_str = ft_strjoin(tab_path[i], str);
		if (access(next_str, X_OK) == 0)
		{
			return (next_str);
		}
		else
		{
			free(next_str);
			i++;
		}
	}
	return (str);
}

int		test_pipe(char **left, char **right)
{
	pid_t	pid1;
	pid_t	pid2;
	int		descrf[2];

	pipe(descrf);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(descrf[ESCRIBIR], 1);
		close(descrf[LEER]);
		execve(left[0], left, NULL);
		perror(left[0]);
		return (1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(descrf[LEER], 0);
		close(descrf[ESCRIBIR]);
		execve(right[0], right, NULL);
		perror(right[0]);
		return (1);
	}
	close(descrf[0]);
	close(descrf[1]);
	wait(&pid1);
	wait(&pid2);
	return (0);
}
void	free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree->str1);
	free(tree->str2);
	free(tree->symbol);
	free(tree);
}

void	ft_ast(t_tree *tree, t_env *st_env)
{
	char	**tab_left;
	char	**tab_right;

	tab_left = ft_strsplit(tree->str1, ' ');
	tab_right = ft_strsplit(tree->str2, ' ');
	tab_left[0] = test_exist_fonction_ft(tab_left[0], st_env);
	tab_right[0] = test_exist_fonction_ft(tab_right[0], st_env);
	if (ft_strcmp(tree->symbol, "|") == 0)
	{
		test_pipe(tab_left, tab_right);
	}
}

char	**create_tab_path_ft(char **tab_path, char **env)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		str = ft_strndup(env[i], 5);
		if (ft_strcmp(str, "PATH=") == 0)
		{
			free(str);
			tab_path = ft_strsplit(&env[i][5], ':');
			while (tab_path[j])
			{
				str = ft_strjoin(tab_path[j], "/");
				free(tab_path[j]);
				tab_path[j++] = str;
			}
			return (tab_path) ;
		}
		else
			free(str);
	}
	tab_path = NULL;
	return (tab_path);
}
