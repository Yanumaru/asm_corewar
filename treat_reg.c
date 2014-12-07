/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_reg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykichena <ykichena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/06 08:38:42 by ykichena          #+#    #+#             */
/*   Updated: 2014/12/06 12:53:35 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <libft.h>
#include <unistd.h>

void	treat_reg(char *cmd, t_group *all)
{
	int	a;

	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (ft_strchr(cmd, 'r') && !ft_strchr(cmd, '%'))
	{
		a = ft_atoi(cmd + 1);
		if (a == 0)
			asm_error(SO_MUCH, 0 ,0);
		write(all->fd, &a, 1);
	}
}
