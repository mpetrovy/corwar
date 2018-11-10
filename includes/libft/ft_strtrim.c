/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:37:08 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 19:29:47 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		j;
	char	*arr;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen((char *)s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (!(arr = (char *)malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	while (i <= len)
	{
		arr[j] = s[i];
		i++;
		j++;
	}
	arr[j] = '\0';
	return (arr);
}
