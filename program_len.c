/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/06 16:41:34 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/07 17:42:19 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <libft.h>
#include <stdlib.h>

t_opc	g_opc[17] =
{
	{"live", 0, 4},
    {"ld", 1, 4},
    {"st", 1, 0},
    {"add", 1, 0},
    {"sub", 1, 0},
    {"and", 1, 4},
    {"or", 1, 4},
    {"xor", 1, 4},
    {"zjmp", 0, 2},
    {"ldi", 1, 2},
    {"sti", 1, 2},
    {"fork", 0, 2},
    {"lld", 1, 4},
    {"lldi", 1, 2},
    {"lfork", 0, 2},
    {"aff", 1, 4},
    {NULL, 0, 0}
};

void	free_tab(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		free(arg[i]);
		arg[i] = NULL;
	}
	free(arg);
	arg = NULL;
}

int		count_tdirop(char *str, int *l, int *len)
{
	int		i;
	int		res;
	char	*tmp;

	i = -1;
	tmp = ft_strsub(str, 0, count(str));
	while (++i < 16)
	{
		if (!ft_strcmp(tmp, g_opc[i].nm))
		{
			*l = g_opc[i].tdir;
			*len += g_opc[i].op - 1;
			free(tmp);
			return (1);
		}
	}
	return (0);
}

int		count_len(t_group *all)
{
	t_list	*tmp;
	char	*str;
	char	**arg;
	int		len;
	int		i;
	int		l;

	len = 0;
	tmp = all->l;
	while (tmp)
	{
		if (iscmd(tmp->line) == OK)
		{
			i = -1;
			str = tmp->line + count(tmp->line);
			str = ft_strtrim(str);
			arg = ft_strsplit(str, ',');
			len += 2;
			count_tdirop(tmp->line, &l, &len);
			while (arg[++i])
			{
				if (!ft_strchr(arg[i], 'r'))
					len += l;
				else
					len += 1;
			}
			free_tab(arg);
			free(str);
		}
		tmp = tmp->next;
	}
	return (len);
}
