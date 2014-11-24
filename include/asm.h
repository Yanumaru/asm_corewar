/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smicaliz <smicaliz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 21:03:17 by smicaliz          #+#    #+#             */
/*   Updated: 2014/11/24 13:09:50 by ykichena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define NO_VALID -1
# define USAGE 0
# define ERR_OPEN 1
# define ERR_ABORT 2
# define ERR_SYNTAX 3
# define U_STRING 4
# define NM_TOO_LONG 5
# define CMT_TOO_LONG 6
# define BAD_CHAR 7
# define SO_MUCH 8
# define OK -2

typedef struct 		s_list
{
	int				nb_line;
	char			*line;
	struct s_list	*next;
}					t_list;

t_list				*advance(t_list *list);
int					check_line(char *str, int line);
int					check_len(int f, char *str, int pos);
int					find_quote(char *str, int pos);
void				asm_error(int err_type, int cursor, int line);
int					avance_comment(char **buf, int fd);
void				parse_inside(t_list *list, char *file_name);
t_list				*ft_add(char *str, int i);
int					isallow(char c);
int					iscmd(char *str);
int					islabel(char *str, int line);

#endif
