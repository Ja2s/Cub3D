/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:08:07 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 10:45:52 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbelement, size_t size)
{
	void		*tmp;
	size_t		n;

	if (nbelement == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / nbelement < size)
		return (NULL);
	n = nbelement * size;
	tmp = (void *)malloc(n);
	if (!tmp)
		return (NULL);
	ft_bzero_lib(tmp, n);
	return (tmp);
}
