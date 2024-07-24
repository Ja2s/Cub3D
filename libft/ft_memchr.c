/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:49:56 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:51:17 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int c, size_t n)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = (char *)str;
	while (i < n)
	{
		if (tmp[i] == (char)c)
			return ((void *)tmp + i);
		i++;
	}
	return (NULL);
}
