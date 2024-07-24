/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:00:22 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:49:10 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	i;
	size_t	lensrc;
	char	*tmp;

	i = 0;
	lensrc = ft_strlen(str);
	tmp = malloc(lensrc + 1 * sizeof(char));
	if (tmp == NULL)
		return (tmp);
	while (i < lensrc)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
