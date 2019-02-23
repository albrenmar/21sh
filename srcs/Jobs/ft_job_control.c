/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/22 12:10:05 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int					rellocate_cmd(t_last *part, int mode)
{
	while (part && part->check == 1)
		part = part->next;
	if (mode == -1)
	{
		while (part && ft_strcmp(part->name, "||") && ft_strcmp(part->name, ";"))
		{
			part->check = 1;
			part = part->next;
		}
		if (!part)
			return (-1);
		else
		{
			part->check = 1;
			return (0);
		}
	}
	else if (mode == 0)
	{
		while (part && ft_strcmp(part->name, "&&") && ft_strcmp(part->name, ";"))
		{
			part->check = 1;
			part = part->next;
		}
		if (!part)
			return (-1);
		else
		{
			part->check = 1;
			return (0);
		}
	}
	return (0);
}

int					cmd_checker(t_last *part, int mode, t_jobs *job)
{
	if (job->startback == 1)
		return (0);
	if (!(ft_strcmp(check_separator(part), ";")))
		return (0);
	while (part && part->check == 1)
		part = part->next;
	if (!part)
		return (-1);
	if (mode == 0)
	{
		if (!(ft_strcmp(check_separator(part), "&&")))
			return (0);
		return (rellocate_cmd(part, mode));
	}
	else
	{
		if (!(ft_strcmp(check_separator(part), "||")))
			return (0);
		return (rellocate_cmd(part, mode));
	}
}
/*
char				*fill_cmd_name(t_last *part)
{
	char			*new;
	int				len;
	int				i;
	t_last			*hold;
	int				count;

	len = 0;
	count = -1;
	while (part->next && part->check == 1 && part->next->check == 1)
		part = part->next;
	part = part->prev;
	while (part->prev != NULL && ft_strcmp(part->name, "||") && ft_strcmp(part->name, ";") &&
		ft_strcmp(part->name, "&&"))
		part = part->prev;
	if (part->prev != NULL)
		part = part->next;
	hold = part;
	while (part->next != NULL && ft_strcmp(part->name, "||") && ft_strcmp(part->name, ";") &&
		ft_strcmp(part->name, "&&"))
	{
		count++;
		len = len + ft_strlen(part->name);
		part = part->next;
	}
	if (!(new = malloc(sizeof(char) * (len + count) + 1)))
		return (NULL);
	len = 0;
	while (hold && ft_strcmp(hold->name, "||") && ft_strcmp(hold->name, ";") &&
		ft_strcmp(hold->name, "&&"))
	{
		i = 0;
		while (hold->name[i])
		{
			new[len] = hold->name[i];
			len++;
			i++;
		}
		new[i++] = ' ';
		hold = hold->next;
	}
	new[i] = '\0';
	return (new);
}

// void				fill_job(t_last *part)
// {
// 	t_jobs			*tmp;
// 	int				hold;

// 	tmp = g_tracking.jobs;
// 	if (tmp->name == NULL)
// 	{
// 		tmp->name = fill_cmd_name(part);
// 		tmp->place = 1;
// 		// tmp->type = 0;
// 		// tmp->jpid = jpid;
// 		tmp->notified = 0;
// 		tmp->next = NULL;
// 	}
// 	else
// 	{
// 		hold = tmp->place;
// 		while (tmp->next)
// 		{
// 			hold = tmp->place;
// 			tmp = tmp->next;
// 		}
// 		if (!(tmp->next = malloc(sizeof(t_jobs))))
// 			return ;
// 		tmp = tmp->next;
// 		tmp->place = hold + 1;
// 	}
	
// }
*/
char				*check_separator(t_last *part)
{
	t_last			*hold;

	while (part && part->check == 1)
	{
		hold = part;
		part = part->next;
	}
	if (part)
		return (part->prev->name);
	else if (hold && ((!(ft_strcmp(hold->name, "||")) ||
		(!(ft_strcmp(hold->name, "&&"))) || (!(ft_strcmp(hold->name, ";"))) ||
		(!(ft_strcmp(hold->name, "&"))))))
		return (hold->name);
	else
		return (NULL);
}
/*
static t_last		*next_cmd(t_last *part)
{
	t_last	*new;
	t_last	*head;
	t_last	*hold;

	while (part && part->check == 1)
		part = part->next;
	if (part == NULL)
		return (NULL);
	if (part->check == 1)
		part = part->next;
	if (!(new = malloc(sizeof(t_last))))
		return (NULL);
	head = new;
	new->prev = NULL;
	while (part && ft_strcmp(part->name, "&&") && ft_strcmp(part->name, "||") &&
		ft_strcmp(part->name, ";") && ft_strcmp(part->name, "&"))
	{
		hold = new;
		new->check = 0;
		new->name = ft_strdup(part->name);
		new->type = part->type;
		part->check = 1;
		if (part->next && ft_strcmp(part->next->name, "&&") &&
			ft_strcmp(part->next->name, "||") &&
			ft_strcmp(part->next->name, ";") && ft_strcmp(part->next->name, "&"))
		{
			if (!(new->next = malloc(sizeof(t_last))))
				return (NULL);
			new->check = 1;
			new = new->next;
			new->prev = hold;
			part = part->next;
		}
		if (new->check == 0 && (part->next == NULL || (!(ft_strcmp(part->next->name, "||")) ||
			(!(ft_strcmp(part->next->name, "&&"))) ||
			(!(ft_strcmp(part->next->name, ";"))) || (!(ft_strcmp(part->next->name, "&"))))))
			break ;
	}
	new->next = NULL;
	new->check = 0;
	if (part->next)
		part->next->check = 1;
	return (head);
}
*/
void		free_last(t_last **cmd)
{
	t_last	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->check = 0;
		tmp->type = 0;
		ft_strdel(&tmp->name);
		tmp->prev = NULL;
		tmp = tmp->next;
	}
}
/*
static t_last		*cmd_to_part(t_last *cmd)
{
	t_last	*new;
	t_last	*head;
	t_last	*hold;

	if (!(new = malloc(sizeof(t_last))))
		return (NULL);
	head = new;
	new->prev = NULL;
	while (cmd)
	{
		hold = new;
		new->check = 0;
		new->type = cmd->type;
		new->name = ft_strdup(cmd->name);
		if (cmd->next)
		{
			if (!(new->next = malloc(sizeof(t_last))))
				return (NULL);
			new = new->next;
			new->prev = hold;
		}
		cmd = cmd->next;
	}
	new->next = NULL;
	return (head);
}

void	print_last(t_last *list)
{
	t_last		*temp;

	temp = list;
	while (list)
	{
		printf("CMD = %s ET TYPE = %d\n", list->name, list->type);
		list = list->next;
	}
	list = temp;
}

void	cmd_manager(t_last *cmd, t_tab_arg *tab_arg)
{
	t_last	*part;
	t_jobs	*job;
	int		foreground;
	
	part = cmd_to_part(cmd);
	print_last(part);
	exit (0);
	free_last(&cmd);
	while ((cmd = next_cmd(part)) != NULL)
	{
		/////////
		tab_arg = convert_to_list_tab(cmd);
		if (ft_strcmp(check_separator(part), "&"))
			foreground = 0;
		else
			foreground = 1;
		job = new_job(part, foreground);
		ft_ast(tab_arg, job);
		if (!g_tracking.interactive)
			wait_for_job(job);
		else if (!foreground)
			put_job_in_foreground(job, 0);
		else
			put_job_in_background(job, 0);
		/////////
		if (g_tracking.fg == 1 || g_tracking.bg == 1)
		{
			if (g_tracking.fg == 1)
				fg_builtin(4);
			else
				bg_builtin(4);
		}
		ORDER = NULL;
		if (g_tracking.lastreturn == 0 && cmd_checker(part, 0, job) == -1)
		{
			free_last(&cmd);
			free_last(&part);
			return ;
		}
		else if (g_tracking.lastreturn != 0 && cmd_checker(part, -1, job) == -1)
		{
			free_last(&cmd);
			free_last(&part);
			return ;
		}
	}
	free_last(&cmd);
	free_last(&part);
}*/
