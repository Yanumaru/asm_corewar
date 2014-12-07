/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 18:38:33 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/06 14:47:56 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <asm.h>
#include <op.h>

t_hextab	g_hextab[17] =
{
	{"live", 0x01},
	{"ld", 0x02},
	{"st", 0x03},
	{"add", 0x04},
	{"sub", 0x05},
	{"and", 0x06},
	{"or", 0x07},
	{"xor", 0x08},
	{"zjmp", 0x09},
	{"ldi", 0x0a},
	{"sti", 0x0b},
	{"fork", 0x0c},
	{"lld", 0x0d},
	{"lldi", 0x0e},
	{"lfork", 0x0f},
	{"aff", 0x10},
	{NULL, 0}
};

int		count(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != ' ' && str[i] != '\t')
		;
	return (i);
}

void	treat_cmd(char *cmd, t_group *all, int line)
{
	int		i;
	int		tw;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strcmp(g_hextab[i].cmd, ft_strsub(cmd, 0, count(cmd))))
		{
			tw = g_hextab[i].hex & 0xFF;
			write(all->fd, &tw, 1);
			treat_arg(cmd, all, line);
			return ;
		}
	}
}

void	search_cmd(t_group *all)
{
	t_list	*tmp;

	tmp = all->l;
	while (tmp)
	{
		if (iscmd(tmp->line))
			treat_cmd(tmp->line, all, tmp->nb_line);
		tmp = tmp->next;
	}
}
