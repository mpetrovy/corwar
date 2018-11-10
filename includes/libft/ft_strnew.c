/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:46:05 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 18:38:59 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *arr;

	if ((arr = (char*)malloc(sizeof(*arr) * (size + 1))) == NULL)
		return (NULL);
	ft_memset(arr, '\0', size + 1);
	return (arr);
}
