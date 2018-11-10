/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:17:02 by daalexan          #+#    #+#             */
/*   Updated: 2018/02/11 12:17:04 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# define BUFF_SIZE 20
# define END 0
# define OK 1
# define ERROR -1

typedef struct		s_read
{
	int				fd;
	char			*data;
	struct s_read	*next;
}					t_read;

int					get_next_line(const int fd, char **line);

#endif
