/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:31:30 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:44:27 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	index;

	if (!s1 || !s2)
		return (0);
	index = ft_strcmp((const char*)s1, (const char*)s2);
	if (index == 0)
		return (1);
	return (0);
}
