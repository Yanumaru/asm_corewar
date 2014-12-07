/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 08:41:40 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/06 20:03:09 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <libft.h>
#include <stdlib.h>
#include <string.h>

static t_list	*put_to_write(char *s1, char *s2)
{
	t_list	*tmp;
	t_list	*first;
	int		f;

	first = NULL;
	f = 0;
	if (s1 != NULL)
	{
		tmp = ft_add(s1, 0);
		first = tmp;
		f++;
	}
	if (s2 != NULL)
	{
		if (f)
			tmp->next = ft_add(s2, 0);
		else
		{
			tmp = ft_add(s1, 0);
			first = tmp;
		}
	}
	return (first);
}

static char		*save_sentence(char *str, int i, int pos)
{
	char	*save_name;
	char	*save;
	int		s;

	s = i;
	save = NULL;
	save_name = NULL;
	if (str[i] != ' ' && str[i] != '\t')
		asm_error(ERR_SYNTAX, 0, 0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	save_name = ft_strsub(str, i, ft_strlen(str));
	if (save_name == NULL)
		exit(-1);
	if (find_quote(save_name, pos) == OK && check_len(s, save_name, pos) == OK)
	{
		save = ft_strsub(save_name, 1, ft_strlen(save_name) - 2);
		if (save == NULL)
			exit(-1);
		free(save_name);
	}
	else
		asm_error(ERR_SYNTAX, find_quote(save_name, 0), pos);
	return (save);
}

static char		*ignore_comment(char *str)
{
	char	*comment_1;
	char	*comment_2;
	char	*cpy;

	cpy = NULL;
	comment_1 = ft_strchr(str, COMMENT_CHAR);
	comment_2 = ft_strchr(str, ';');
	if (!comment_1 && !comment_2)
		return (str);
	if (comment_1 && !comment_2)
		cpy = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(comment_1));
	else if (!comment_1 && comment_2)
		cpy = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(comment_2));
	else if (ft_strlen(comment_1) < ft_strlen(comment_2))
		cpy = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(comment_2));
	else if (ft_strlen(comment_1) < ft_strlen(comment_2))
		cpy = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(comment_1));
	if (cpy == NULL)
		exit(-1);
	return (cpy);
}

static t_list	*search_name(t_list *list)
{
	t_list	*tmp;
	char	*str;
	char	*name;
	char	*comment;

	name = NULL;
	comment = NULL;
	tmp = list;
	while (tmp)
	{
		str = ignore_comment(tmp->line);
		if (!ft_strncmp(NAME_CMD_STRING, str, 5))
			name = save_sentence(str, 5, tmp->nb_line);
		if (!ft_strncmp(COMMENT_CMD_STRING, str, 8))
			comment = save_sentence(str, 8, tmp->nb_line);
		if (str != tmp->line && str != NULL)
			free(str);
		tmp = tmp->next;
	}
	return (put_to_write(name, comment));
}

void			parse_inside(t_list *list, char *file_name)
{
	t_list	*to_write;
	t_list	*tmp;
	char	*str;
	char	*str2;

	tmp = list;
	to_write = search_name(list);
	while (tmp)
	{
		str2 = ignore_comment(tmp->line);
		str = ft_strtrim(str2);
		if (str == NULL)
			exit(-1);
		if (str2 && str2 != tmp->line)
			ft_strdel(&str2);
		free(tmp->line);
		tmp->line = NULL;
		tmp->line = str;
		tmp = tmp->next;
	}
	work_on(list, to_write, file_name);
}
