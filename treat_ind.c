/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_ind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/06 12:57:03 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/06 14:28:23 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <op.h>
#include <libft.h>
#include <unistd.h>

void	treat_ind(char *arg, t_group *all)
{
	int	i;
	int	hex;
	int	n;

	i = -1;
	while (arg[++i] == ' ' || arg[i] == '\t')
		;
	if (ft_isdigit(arg[i]))
	{
		n = ft_atoi(arg + i);
		hex = (n & 0xFF00) >> 8;
		write(all->fd, &hex, 1);
		hex = (n & 0xFF);
		write(all->fd, &hex, 1);
	}
}
