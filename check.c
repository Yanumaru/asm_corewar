/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 08:03:46 by ykichena          #+#    #+#             */
/*   Updated: 2014/11/28 11:50:29 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>
#include <op.h>

static void	epur_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		tab[i] = ft_strtrim(tab[i]);
}

static int	count_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

static int	isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int			isallow(char c)
{
	int	i;

	i = -1;
	while (LABEL_CHARS[++i])
	{
		if (c == LABEL_CHARS[i])
			return (OK);
	}
	return (NO_VALID);
}

int			check_arg(t_list *list, t_list *label)
{
	extern	t_op	op_tab[17];
	char			*str;
	char			**tab;
	int				len;
	int				i;

	len = -1;
	i = -1;
	if (!ft_strchr(list->line, ' ') && !ft_strchr(list->line, '\t'))
		asm_error(SO_MUCH, list->nb_line, 0);
	while (++i < 16)
	{
		if (!ft_strncmp(op_tab[i].name, list->line, ft_strlen(op_tab[i].name)))
		{
			str = list->line + len;
			tab = ft_strsplit(str, SEPARATOR_CHAR);
			epur_tab(tab);
			if (count_tab(tab) != op_tab[i].nb_params)
				asm_error(SO_MUCH, list->nb_line, 0);
			return (OK);
		}
	}
	return (NO_VALID);
}
