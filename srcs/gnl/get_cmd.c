/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:14:49 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_return(void)
{
	g_tracking.cmd = ft_strdup(g_tracking.str);
	free(g_tracking.str);
	free(g_tracking.cpaste->line);
	free(g_tracking.cpaste);
	g_tracking.str = NULL;
	cursor_reset();
}

void	test_read(void)
{
	char	c[12];
	int		i;

	i = 0;
	read(STDERR_FILENO, &c, 12);
	while (c[i])
	{
		printf("0x%x\n", c[i]);
		if (i != 6)
			ft_putchar('.');
		else
			ft_putchar('\n');
		i++;
	}
}

void	test_read2(char *str)
{
	int		i;

	i = 0;
	ft_putchar('\n');
	while (str[i])
	{
		printf("0x%x\n", str[i]);
		i++;
	}
}

int		ft_exec_key(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		move_left();
	if (ft_strcmp(str, K_RIGHT) == 0)
		move_right();
	if (ft_strcmp(str, K_WRIGHT) == 0)
		next_word();
	if (ft_strcmp(str, K_WLEFT) == 0)
		prev_word();
	if (ft_strcmp(str, K_LUP) == 0)
		move_up();
	if (ft_strcmp(str, K_LDOWN) == 0)
		move_down();
	if (ft_strcmp(str, K_DEL) == 0)
		rem_from_str_del();
	if (ft_strcmp(str, K_FN1) == 0)
		begin_cpy();
	if (ft_strcmp(str, K_FN3) == 0)
		begin_paste();
	if (ft_strcmp(str, K_UP) == 0)
		history_up();
	if (ft_strcmp(str, K_DOWN) == 0)
		history_down();
	if (ft_strcmp(str, K_ESC) == 0)
		return (6);
	return (6);
}

int		is_cmd(char *str)
{
	unsigned long	i;
	t_list			*tmp;
	int				flag;

	i = ft_strlen(str);
	tmp = g_tracking.key_list->firstelement;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->content, i) == 0)
			flag++;
		if (strlen(tmp->content) == i && ft_strncmp(str, tmp->content, i) == 0)
		{
			return (ft_exec_key(str));
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		return (6);
	return (0);
}
