/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 15:02:36 by rsavchak          #+#    #+#             */
/*   Updated: 2017/12/09 16:14:08 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int words;
	int check;
	int i;

	i = 0;
	words = 0;
	check = 0;
	while (s[i] != '\0')
	{
		if (check == 1 && s[i] == c)
		{
			check = 0;
		}
		if (check == 0 && s[i] != c)
		{
			check = 1;
			words++;
		}
		i++;
	}
	return (words);
}

static int	ft_len(char const *s, char c)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		words;
	char	**ar;

	if (!s)
		return (NULL);
	i = 0;
	words = ft_words((const char *)s, c);
	if (!(ar = (char **)malloc(sizeof(*ar) * (ft_words((char *)s, c) + 1))))
		return (NULL);
	if (words == 0)
	{
		ar[0] = NULL;
		return (ar);
	}
	while (words--)
	{
		while (*s == c && *s != '\0')
			s++;
		ar[i] = ft_strsub((char *)s, 0, (ft_len((char *)s, c)));
		s = s + ft_len(s, c);
		i++;
	}
	ar[i] = NULL;
	return (ar);
}
