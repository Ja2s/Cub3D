/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:32:55 by jgavairo          #+#    #+#             */
/*   Updated: 2023/12/20 14:01:09 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	static_buff[BUFFER_SIZE + 1] = "\0";
	char		*res;

	res = malloc(1 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(static_buff, &res), NULL);
	if (ft_move_static(static_buff, &res) == -1)
		return (ft_free(static_buff, &res), NULL);
	if (ft_read_file(fd, static_buff, &res) == -1)
		return (ft_free(static_buff, &res), NULL);
	if (ft_back_static(static_buff) == -1)
		return (ft_free(static_buff, &res), NULL);
	return (res);
}

int	ft_move_static(char static_buff[], char **res)
{
	if (static_buff[0] != '\0' && endline_checker(static_buff) == 0)
	{
		*res = ft_strjoin(*res, static_buff);
		if (*res == NULL)
			return (-1);
		return (0);
	}
	return (0);
}

int	ft_read_file(int fd, char static_buff[], char **res)
{
	int		ret;
	char	*tmp;

	ret = 1;
	if (endline_checker(static_buff) == 0)
	{
		while (endline_checker(static_buff) == 0 && ret > 0)
		{
			ret = read(fd, static_buff, BUFFER_SIZE);
			if ((ret == -1) || (ret == 0 && *res[0] == '\0'))
				return (-1);
			static_buff[ret] = '\0';
			tmp = ft_strjoin(*res, static_buff);
			if (tmp == NULL)
				return (-1);
			*res = tmp;
		}
	}
	else if (endline_checker(static_buff) == 1)
	{
		*res = ft_strjoin(*res, static_buff);
		if (*res == NULL)
			return (-1);
	}
	return (0);
}

int	ft_back_static(char static_buff[])
{
	char		*tmp;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	if (static_buff[BUFFER_SIZE] == '\n')
		static_buff[0] = '\0';
	else if (static_buff[0] != '\0')
	{
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (-1);
		tmp[BUFFER_SIZE] = '\0';
		while (static_buff[i] && static_buff[i] != '\n')
			i++;
		i++;
		while (static_buff[i])
			tmp[j++] = static_buff[i++];
		ft_bzero(tmp, BUFFER_SIZE - j, j);
		ft_memmove(static_buff, tmp, BUFFER_SIZE);
		free (tmp);
	}
	return (0);
}

void	ft_free(char static_buff[], char **res)
{
	free(*res);
	*res = NULL;
	ft_bzero(static_buff, BUFFER_SIZE, 0);
}
