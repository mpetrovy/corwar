/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:27:40 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/21 18:27:42 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *list;

	if (alst == NULL || del == NULL || *alst == NULL)
		return ;
	{
		list = *alst;
		while (list != NULL)
		{
			current = list->next;
			del(list, list->content_size);
			list = current;
		}
		*alst = NULL;
	}
}
