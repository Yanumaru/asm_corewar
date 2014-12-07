/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 02:52:06 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/07 17:33:25 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <op.h>
#include <asm.h>
#include <string.h>

int			iscmd(char *str)
{
	int			i;
	char		*tmp;
	extern t_op	op_tab[17];

	i = -1;
	tmp = ft_strsub(str, 0, count(str));
	while (++i < 16)
	{
		if (!ft_strcmp(tmp, op_tab[i].name))
		{
			free(tmp);
			return (OK);
		}
	}
	return (NO_VALID);
}

int			islabel(char *str, int line)
{
	int	i;

	i = -1;
	if (iscmd(str) == OK)
		return (NO_VALID);
	while (str[++i] && str[i] != LABEL_CHAR)
	{
		if (isallow(str[i]) != OK)
			asm_error(BAD_CHAR, line, i);
	}
	if (str[i] != LABEL_CHAR)
		return (NO_VALID);
	return (OK);
}

void		to_write(t_group *all)
{
	int			fd;
	char		*str;
	header_t	head;

	print_meanwhile(all->w);
	str = ft_strjoin(ft_strsub(all->n, 0, ft_strlen(all->n) - 2), ".cor");
	fd = open(str, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG);
	if (fd == -1)
		exit(-1);
	all->fd = fd;
	exec_magic(fd);
	if (all->w)
		strncpy(head.prog_name, all->w->line, ft_strlen(all->w->line));
	if (all->w->next)
		strncpy(head.comment, all->w->next->line, ft_strlen(all->w->next->line));
	print_head(head, fd, all);
	search_cmd(all);
}

static void	continue_work(t_list *label, t_list *list, t_list *tw, char *f_name)
{
	t_list	*tmp;
	t_group	all;

	tmp = list;
	while (tmp)
	{
		if (iscmd(tmp->line) == OK)
		{
			if (check_arg(tmp, label) != OK)
				asm_error(SO_MUCH, tmp->nb_line, 0);
		}
		tmp = tmp->next;
	}
	all.lab = label;
	all.l = list;
	all.w = tw;
	all.n = f_name;
	all.len = count_len(&all);
	to_write(&all);
}

void		work_on(t_list *list, t_list *tw, char *file_name)
{
	t_list	*label;
	t_list	*tmp;
	t_list	*first;
	int		f;

	f = 0;
/*	list = treat_if_same_line(list);*/
	tmp = list;
	while (tmp)
	{
		if (islabel(tmp->line, tmp->nb_line) == OK)
		{
			if (f == 0)
			{
				label = ft_add(tmp->line, tmp->nb_line);
				first = label;
				f++;
			}
			else
			{
				label->next = ft_add(tmp->line, tmp->nb_line);
				label = label->next;
			}
		}
		tmp = tmp->next;
	}
	continue_work(first, list, tw, file_name);
}
