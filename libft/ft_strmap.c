/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:06:44 by rsavchak          #+#    #+#             */
/*   Updated: 2017/11/25 13:36:56 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;
	int		j;

	if (s != NULL && f != NULL)
	{
		i = 0;
		j = 0;
		while (s[j] != '\0')
			j++;
		if (!(str = (char *)malloc(sizeof(*str) * (ft_strlen(s) + 1))))
			return (NULL);
		while (s[i] != 0)
		{
			str[i] = f(s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
