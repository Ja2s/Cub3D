/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:32:37 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:51:59 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	res;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	res = 0;
	if (size < len_dst)
		res = len_src + size;
	else
		res = len_dst + len_src;
	while ((len_dst + 1) < size && src[i])
		dst[len_dst++] = src[i++];
	dst[len_dst] = '\0';
	return (res);
}
