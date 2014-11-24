/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 08:19:52 by ykichena          #+#    #+#             */
/*   Updated: 2014/11/23 12:03:17 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <libft.h>

void	asm_error(int err_type, int cursor, int line)
{
	cursor = cursor + 1;
	line = line + 1;
	if (err_type == USAGE)
		ft_error("Usage :\n./asm filename[.s]");
	if (err_type == ERR_OPEN)
		ft_error("Cannot open file");
	if (err_type == ERR_ABORT)
		ft_error("Aborting");
	if (err_type == U_STRING)
		ft_error("unterminated string");
	if (err_type == ERR_SYNTAX)
		ft_error("error1");
	if (err_type == U_STRING)
		ft_error("error2");
	if (err_type == CMT_TOO_LONG)
		ft_error("error3");
	if (err_type == NM_TOO_LONG)
		ft_error("error4");
}

int		check_len(int f, char *str, int pos)
{
	if (f == 5)
	{
		if (ft_strlen(str) >= PROG_NAME_LENGTH)
			asm_error(NM_TOO_LONG, 0, pos);
	}
	if (f == 8)
	{
		if (ft_strlen(str) >= COMMENT_LENGTH)
			asm_error(CMT_TOO_LONG, 0, pos);
	}
	return (OK);
}

int		find_quote(char *str, int pos)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str[i++] != '"')
		asm_error(ERR_SYNTAX, 0, pos);
	while (str[i])
	{
		if (str[i] == ';')
			asm_error(U_STRING, 0, pos);
		if (str[i] == '"' && i != len - 1)
			asm_error(ERR_SYNTAX, i, pos);
		i++;
	}
	return (OK);
}

t_list	*advance(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int		avance_comment(char **buf, int fd)
{
	int	i;

	i = 1;
	if (buf[0][0] == COMMENT_CHAR)
	{
		while (buf[0][0] == COMMENT_CHAR && get_next_line(fd, buf))
			i++;
	}
	return (i);
}
