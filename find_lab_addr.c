/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lab_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/06 14:37:28 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/07 01:16:44 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <libft.h>

void	count_pos(t_group *all, int line)
{
	t_list *tmp;
	int		n;

	tmp = all->l;
	while (tmp)
	{
		if (tmp->nb_line == line1)
		{
			while (tmp->nb_line != line2)
			{
				count_len();
				display_len();
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
}

void	search_addr(char *str, t_group *all, int line)
{
	t_list			*tmp;
	extern t_opc	g_opc[17]

	tmp = all->l;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, str, count(str)))
		{
			if (tmp->nb_line > line)
				count_pos(all, line)
			if (line > tmp->nb_line)
				count_pos(all, line,);
			return ;
		}
		tmp = tmp->next;
	}
}
