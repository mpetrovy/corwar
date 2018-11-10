/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:28:45 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/21 18:28:49 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *begin;

	begin = lst;
	if (lst == NULL || f == NULL)
		return ;
	while (begin != NULL)
	{
		f(begin);
		begin = begin->next;
	}
}
