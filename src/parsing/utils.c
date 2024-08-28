/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:32:15 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/26 13:14:04 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen_cub(char *s, int choice)
{
	int	i;

	i = 0;
	if (choice == 0)
		while (s[i])
			i++;
	else if (choice == 1)
		while (s[i] && !(s[i] >= '0' && s[i] <= '9'))
			i++;
	else if (choice == 2)
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
	return (i);
}

char	*ft_strdup_cub(char *str, int choice)
{
	size_t	i;
	size_t	len_src;
	char	*tmp;

	i = 0;
	len_src = ft_strlen_cub(str, choice);
	tmp = malloc((len_src + 1) * sizeof(char));
	if (tmp == NULL)
		return (tmp);
	while (i < len_src)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin_cub(char *s1, char *s2)
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
	return (s3);
}

int	ft_strcmp_cub(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] == '.' || s1[i] == '/')
		i++;
	while (s2[j] == '.' || s2[j] == '/')
		j++;
	while (s1[i] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return (s1[i] - s2[j]);
}
