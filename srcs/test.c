#include "../libft/libft.h"

int			get_nb_char(unsigned char c)
{
	int		i;

	if (c >= 0xF0 && c <= 0xF4)
		return (3);
	if (c >= 0xE0 && c <= 0xEF)
		return (2);
	if (c >= 0xC0 && c <= 0xDF)
		return (1);
	else
		return (0);
}

int	can_move(int c)
{
	if (c >= 0x80 && c <= 0xBF)
		return (1);
	return (0);
}

int			how_long(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
    {
        if ((str[i] & 0xC0) != 0x80)
		    a++;
        i++;
    }
	return (a);
}

int			utf_goto(char *str, int j)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (a != j)
	{
		i += get_nb_char(str[i]);
		i++;
		a++;
	}
	return (i);
}

int			utf_strlen(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if ((str[i] & 0xC0) != 0x80)
			a++;
		i++;
	}
	return (a);
}

char	*remfrom(char *s2, int j)
{
	int		i;
	int		a;
	int		b;
	char	*start;
	char	*end;

	if (s2 != NULL)
	{
		a = utf_goto(s2, (j - 1));
		b = utf_goto(s2, j);
		start = ft_strsub(s2, 0, a, 0);
		end = ft_strsub(s2, b, ft_strlen(s2), 0);
		s2 = ft_strjoin(start, end, 3);
	}
	return s2;
}

void	split_to_lst(char *str)
{
		int		end;
		int		a;
		int		i;
		int		j;

		a = 0;
		i = 7;
		j = 0;
		end = ft_strlen(str);
		while (str[j])
		{
			while (a < i && str[j])
			{
				a -= get_nb_char(str[j]);
				ft_putchar(str[j]);
				j++;
				a++;
			}
			ft_putchar('\n');
			a = 0;
		}
}

void	printlist(t_lstcontainer *new)
{
	t_list	*tmp;

	tmp = ft_lstgetfirst(new->firstelement);
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

char	*addto(char *str, char *s2, int j)
{
	int		i;
	int		a;
	char	*start;
	char	*end;

	if (str != NULL)
	{
		i = utf_strlen(str);
		if (!s2)
			s2 = ft_strdup(str);
		else
		{
			start = ft_strsub(s2, 0, a, 0);
			end = ft_strsub(s2, a, ft_strlen(s2), 0);
			start = ft_strjoin(start, str, 3);
			free(s2);
			s2 = ft_strjoin(start, end, 3);
		}
		return s2;
	}
}

char	*memjoin(char *test, char *str, int i)
{
	int		j;
	int		k;

	j = ft_strlen(str);
	k = ft_strlen(test) - i;
	memmove(test+(i), str+i , k);
	while (str[j])
	{
		test[i] = str[j];
		i++;
		j++;
	}
	return (test);
}

int		main(int argc, char **argv)
{
    int i;
    char *str;
	char *test;
	char c[4];


	str = ft_strdup("Demain, dès l'aube, à l'heure où blanchit la campagne, Je partirai. Vois-tu");
	test = ft_strdup("new string de plus de 10 caracteres hahaha");
	i = 10;
	test = memjoin(test, str, 10);
	ft_putendl(test);
	return (0);
}
