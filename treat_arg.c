/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 12:31:17 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/07 15:12:55 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <asm.h>
#include <op.h>

void	continue_encod(int tab[], int t, int fd)
{
	int 	hex;

	if (t < 1 || t > 4)
		asm_error(SO_MUCH, 0, 0);
	if (t == 1)
		hex = (tab[0] << 2) | 0b00;
	else if (t == 2)
	{
		hex = (tab[0] << 2) | tab[1];
		hex = (hex << 2) | 0b00;
	}
	else
	{
		hex = (tab[0] << 2) | tab[1];
		hex = (hex << 2) | tab[2];
		hex = (hex << 2) | 0b00;
	}
	write(fd, &hex, 1);
}

void	encod(char **argv, t_group *all)
{
	int	i;
	int	t;
	int	tab[3];

	i = -1;
	t = 0;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '%'))
			tab[t++] = 0b10;
		else if (ft_strchr(argv[i], 'r'))
			tab[t++] = 0b01;
		else
			tab[t++] = 0b11;
	}
	continue_encod(tab, t,  all->fd);
}

void	continue_treat_tdir(char *str, t_group *all, int line)
{
	if (*str == ':')
	{
		str++;
		if (islabel(str, 0) == NO_VALID)
			asm_error(SO_MUCH, 0, 0);
/*		search_addr(str, all, line);*/
	}
	else
		asm_error(SO_MUCH, 0 , 0);
}

void	treat_tdir(char *arg, t_group *all, int line)
{
	int		i;
	int		n;
	int		hex;

	i = -1;
	while (arg[++i] && arg[i] != '%')
		;
	if (!arg[i])
		return ;
	if (ft_isdigit(arg[i + 1]))
	{
		n = ft_atoi(arg + i + 1);
		hex = (n & 0xFF000000) >> 24;
		write(all->fd, &hex, 1);
		hex = (n & 0xFF0000) >> 16;
		write(all->fd, &hex, 1);
		hex = (n & 0xFF00) >> 8;
		write(all->fd, &hex, 1);
		hex = (n & 0xFF);
		write(all->fd, &hex, 1);
	}
	else
		continue_treat_tdir(arg + i + 1, all, line);
}

void	treat_arg(char *cmd, t_group *all, int line)
{
	int			i;
	int			ib;
	extern t_op	op_tab[17];
	char		**arg;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strcmp(ft_strsub(cmd, 0, count(cmd)), op_tab[i].name))
		{
			ib = -1;
			arg = ft_strsplit(cmd + count(cmd), ',');
			encod(arg, all);
			while (arg[++ib] && ib < op_tab[i].nb_params)
			{
				treat_tdir(arg[ib], all, line);
				treat_reg(arg[ib], all);
				treat_ind(arg[ib], all);
			}
			free_tab(arg);
			return ;
		}
	}
}
