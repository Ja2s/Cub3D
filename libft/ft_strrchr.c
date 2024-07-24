/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:01:30 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:52:16 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	lenstr;

	lenstr = 0;
	while (str[lenstr])
		lenstr++;
	while (lenstr >= 0)
	{
		if (str[lenstr] == (unsigned char)c)
			return ((char *)str + lenstr);
		lenstr--;
	}
	return (NULL);
}
