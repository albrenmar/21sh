#include "sh42.h"

// Save to file with w options
void		hist_save_file_w(char *path)
{
	int fd;
	char **line;
	t_hist *hist;

	hist = g_tracking.mysh->hist;
	
	if (!path)
	{
		path = create_path_hist();
		fd = open(path, O_CREAT | O_APPEND | O_RDWR, 00777);
	}
	else
		fd = open(path, O_CREAT | O_APPEND | O_RDWR, 00777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating history file", 2);
		return;
	}
	if (!hist)
	{
		close(fd);
		return;
	}
	while (hist->previous)
		hist = hist->previous;
	while(hist)
	{
		ft_putendl_fd(hist->line, fd);
		if (hist->next)
			hist = hist->next;
		else
			break;
	}
	close(fd);
}

void		history_builtin_digit(void)
{
	int num;

	num = ft_atoi(g_tracking.g_tab_exec[1]);
		while (g_tracking.mysh->hist->next)
			g_tracking.mysh->hist = g_tracking.mysh->hist->next;
		if (ft_strlen(g_tracking.g_tab_exec[1]) >= 8)
		{
			hist_print(g_tracking.mysh->hist);
			return ;
		}
		while (num > 0 && g_tracking.mysh->hist)
		{
			ft_putnbr(g_tracking.mysh->hist->index);
			ft_putchar(' ');
			ft_putendl(g_tracking.mysh->hist->line);
			g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
			num--;
		}
}

void		history_builtin_p(void)
{
	int i;
	int j;
	// char *tmp;

	i = 1;
	j = 2;
	if (g_tracking.g_tab_exec[j] == NULL)
		return ;
	if (ft_strchr(g_tracking.g_tab_exec[1], 's'))
	{
		history_builtin_s();
		return ;
	}
	else
	{
		while (g_tracking.g_tab_exec[j])
		ft_putendl(g_tracking.g_tab_exec[j++]);
		if (g_tracking.mysh->hist)
			g_tracking.mysh->hist = hist_delete_last(g_tracking.mysh->hist);
	}
}