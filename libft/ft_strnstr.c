/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:16:33 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:52:14 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == 0)
		return ((char *)&big[i]);
	while (i < len && big[i])
	{
		while (little[j] == big[i + j])
		{
			j++;
			if (little[j] == 0 && (i + j) <= len)
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (0);
}
