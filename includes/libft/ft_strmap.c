/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:46:34 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:46:37 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	int		i;

	if (s != NULL)
	{
		if ((str = ft_strdup(s)) == NULL)
			return (NULL);
		i = 0;
		while (str[i] != 0)
		{
			str[i] = f(s[i]);
			i++;
		}
		return (str);
	}
	return (0);
}
