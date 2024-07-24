/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:03:01 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:51:51 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != (unsigned char)c && str[i])
		i++;
	if (str[i] == (unsigned char)c)
		return ((char *)str + i);
	else
		return (NULL);
}
