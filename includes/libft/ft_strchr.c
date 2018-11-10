/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:27:27 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/21 18:27:29 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	arr;

	i = -1;
	arr = (const char)c;
	while (s[++i] != arr && s[i] != '\0')
		;
	if (s[i] == arr)
		return ((char*)&s[i]);
	return (NULL);
}
