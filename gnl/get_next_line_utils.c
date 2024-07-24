/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:32:53 by jgavairo          #+#    #+#             */
/*   Updated: 2023/12/20 13:17:53 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;
	size_t		len_1;
	size_t		len_2;

	len_1 = tmp_len(s1, 2);
	len_2 = tmp_len(s2, 1);
	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	s3 = malloc((len_1 + len_2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	while (i < len_1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len_2 && s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

int	tmp_len(char *tmp, int choice)
{
	int	i;

	i = 0;
	if (choice == 1)
	{
		while (tmp[i] != '\n' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '\n')
			i++;
	}
	else if (choice == 2)
	{
		while (tmp[i])
			i++;
	}
	return (i);
}

int	endline_checker(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i] && i < BUFFER_SIZE)
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n, size_t start)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		str[start] = '\0';
		start++;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && s + n > d)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dest);
	}
	if ((d >= s + n) || (s >= d + n) || (d < s && d + n > s))
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
