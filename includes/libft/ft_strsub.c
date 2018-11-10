/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:24:39 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/21 18:26:46 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, size_t start, size_t len)
{
	char	*arr;
	int		index;

	index = 0;
	if ((arr = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (s != NULL)
	{
		while (len--)
		{
			arr[index] = s[start + index];
			index++;
		}
		arr[index] = '\0';
	}
	return (arr);
}
