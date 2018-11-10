/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:44:00 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:44:02 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*res;

	len = ft_strlen((char*)s1) + 1;
	res = malloc(len);
	if (res == NULL)
		return (NULL);
	return ((char*)ft_memcpy(res, s1, len));
}
