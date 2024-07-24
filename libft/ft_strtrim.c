/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:18:22 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:52:19 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	charset(int c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *str, char *set)
{
	size_t	i;
	size_t	len_str;

	i = 0;
	len_str = ft_strlen(str);
	if (!str)
		return (NULL);
	while (charset(str[i], set) == 1)
		i++;
	while (charset(str[len_str - 1], set) == 1)
		len_str--;
	return (ft_substr(str, i, (len_str - i)));
}
