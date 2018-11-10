/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:05:57 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:45:54 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	index;

	if (!s1 || !s2)
		return (0);
	index = ft_strncmp((char*)s1, (char*)s2, n);
	if (index == 0)
		return (1);
	return (0);
}
