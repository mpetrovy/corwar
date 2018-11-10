/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:26:27 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/21 18:26:30 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *search)
{
	int i;
	int j;

	i = 0;
	if (*search == 0)
		return (str + i);
	while (str[i] != '\0')
	{
		j = 0;
		while (search[j] == str[i + j])
		{
			if (search[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
