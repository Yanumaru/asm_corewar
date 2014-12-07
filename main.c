/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smicaliz <smicaliz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 21:01:01 by smicaliz          #+#    #+#             */
/*   Updated: 2014/12/02 12:09:10 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <op.h>

t_list			*ft_add(char *str, int l)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		exit(-1);
	tmp->line = str;
	tmp->nb_line = l;
	tmp->next = NULL;
	return (tmp);
}

static void		go_gnl(int fd, char *file_name)
{
	char	*buf;
	t_list	*first;
	t_list	*tmp;
	int		l;

	first = NULL;
	if (get_next_line(fd, &buf))
	{
		l = avance_comment(&buf, fd);
		if (buf[0] != COMMENT_CHAR)
		{
			tmp = ft_add(buf, l++);
			first = tmp;
		}
	}
	while (get_next_line(fd, &buf))
	{
		if (buf[0] != COMMENT_CHAR)
		{
			tmp->next = ft_add(buf, l);
			tmp = tmp->next;
		}
		l++;
	}
	parse_inside(first, file_name);
}

static int		check_name(char *str)
{
	int		fd;
	char	*extend;

	if (((fd = open(str, O_RDONLY)) == -1))
		return (NO_VALID);
	extend = ft_strsub(str, ft_strlen(str) - 2, ft_strlen(str));
	if (ft_strcmp(extend, ".s"))
		fd = NO_VALID;
	free(extend);
	return (fd);
}

static void		display(char *str)
{
	ft_putstr("Assembling ");
	ft_putstr(str);
	ft_putstr(":\n");
}

int				main(int argc, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	if (argc == 1)
		asm_error(USAGE, 0, 0);
	else
	{
		while (argv[++i])
		{
			display(argv[i]);
			if (((fd = check_name(argv[i])) == NO_VALID))
				asm_error(ERR_OPEN, 0, 0);
			go_gnl(fd, argv[i]);
		}
		close(fd);
	}
	return (0);
}
