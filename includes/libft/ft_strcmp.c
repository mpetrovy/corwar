/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:43:33 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:43:34 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	size1;
	size_t	size2;
	size_t	result;

	size1 = ft_strlen((char*)s1) + 1;
	size2 = ft_strlen((char*)s2) + 1;
	size1 = (size1 <= size2) ? size1 : size2;
	result = ft_memcmp(s1, s2, size1);
	return (result);
}
