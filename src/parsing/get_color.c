/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:14:48 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/24 11:06:14 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_fill_color_c(t_data *data, char *gnl, int i)
{
	if (gnl[i] >= '0' && gnl[i] <= '9')
		data->sky.r = ft_atoi(gnl + i);
	else
		return (printf("Error\nC iNvalid format\n"), -1);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != ',')
		return (printf("Error\nC inValid format\n"), -1);
	i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (printf("Error\nC invAlid format\n"), -1);
	data->sky.g = ft_atoi(gnl + i);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != ',')
		return (printf("Error\nC invaLid format\n"), -1);
	i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (printf("Error\nC invaliD format\n"), -1);
	data->sky.b = ft_atoi(gnl + i);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != '\n')
		return (printf("Error\nC invalid FormaT\n"), -1);
	return (0);
}

int	ft_fill_color_f(t_data *data, char *gnl, int i)
{
	if (gnl[i] >= '0' && gnl[i] <= '9')
		data->floor.r = ft_atoi(gnl + i);
	else
		return (printf("Error\nF iNvalid format\n"), -1);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != ',')
		return (printf("Error\nF inValid format\n"), -1);
	i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (printf("Error\nF invAlid format\n"), -1);
	data->floor.g = ft_atoi(gnl + i);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != ',')
		return (printf("Error\nF invaLid format\n"), -1);
	i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (printf("Error\nF invaliD format\n"), -1);
	data->floor.b = ft_atoi(gnl + i);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	if (gnl[i] != '\n')
		return (printf("Error\nF invalid FormaT\n"), -1);
	return (0);
}

//atoi(gnl + i) i etant au premier int
int	ft_get_color_c(t_data *data, char *gnl)
{
	int	i;

	i = 1;
	if (gnl[0] == 'C' && gnl[1] == ' ')
	{
		if (data->sky.check)
			return (printf("Error\ndouble C\n"), -1);
		while (gnl[i] == ' ' || gnl[i] == '\t')
			i++;
		if (ft_fill_color_c(data, gnl, i) != 0)
			return (-1);
		data->nb_param = data->nb_param + 1;
		data->sky.check = true;
	}
	return (0);
}

//atoi(gnl + i) i etant au premier int
int	ft_get_color_f(t_data *data, char *gnl)
{
	int	i;

	i = 1;
	if (gnl[0] == 'F' && gnl[1] == ' ')
	{
		if (data->floor.check)
			return (printf("Error\ndouble F\n"), -1);
		while (gnl[i] == ' ' || gnl[i] == '\t')
			i++;
		if (ft_fill_color_f(data, gnl, i) != 0)
			return (-1);
		data->nb_param = data->nb_param + 1;
		data->floor.check = true;
	}
	return (0);
}
