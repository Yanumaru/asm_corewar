/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 11:00:37 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/06 17:22:03 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>
#include <op.h>
#include <unistd.h>

void	exec_magic(int fd)
{
	unsigned int	magic_num;

	magic_num = (COREWAR_EXEC_MAGIC & 0xFF000000) >> 24;
	write(fd, &magic_num, 1);
	magic_num = (COREWAR_EXEC_MAGIC & 0xFF0000) >> 16;
	write(fd, &magic_num, 1);
	magic_num = (COREWAR_EXEC_MAGIC & 0xFF00) >> 8;
	write(fd, &magic_num, 1);
	magic_num = (COREWAR_EXEC_MAGIC & 0xFF);
	write(fd, &magic_num, 1);
}

void	print_len(int fd, int len)
{
	int	hex;

	hex = (len & 0xFF000000) >> 24;
	write(fd, &hex, 1);
	hex = (len & 0xFF0000) >> 16;
	write(fd, &hex, 1);
	hex = (len & 0xFF00) >> 8;
	write(fd, &hex, 1);
	hex = (len & 0xFF);
	write(fd, &hex, 1);
}

void	print_head(header_t head, int fd, t_group *all)
{
	int	i;
	int	hex;

	i = -1;
	head = head;
	while (++i < PROG_NAME_LENGTH + 4)
	{
		if (i < ft_strlen(all->w->line))
			write(fd, &all->w->line[i], 1);
		else
			write(fd, "\0", 1);
	}
	print_len(fd, all->len);
	i = -1;
	while (++i < COMMENT_LENGTH + 4)
	{
		if (i < ft_strlen(all->w->next->line))
			write(fd, &all->w->next->line[i], 1);
		else
			write(fd, "\0", 1);
	}
}

void	print_meanwhile(t_list *list)
{
	if (list)
	{
		write(1, "\t", 1);
		write(1, list->line, ft_strlen(list->line));
		write(1, "\n", 1);
	}
	if (list->next)
	{
		write(1, "\t", 1);
		write(1, list->next->line, ft_strlen(list->next->line));
		write(1, "\n", 1);
	}
}
