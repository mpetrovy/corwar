/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:48:09 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:47:34 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*arr;

	if (s != NULL)
	{
		if ((arr = ft_strdup((const char *)s)) == NULL)
			return (0);
		i = 0;
		while (arr[i] != '\0')
		{
			arr[i] = f(i, s[i]);
			i++;
		}
		return (arr);
	}
	return (0);
}
