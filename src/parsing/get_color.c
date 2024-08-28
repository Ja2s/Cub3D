/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:14:48 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/26 14:42:47 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_get_blue(t_data *data, char *gnl, int i, char choice)
{
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	while (gnl[i] == ' ')
		i++;
	if (gnl[i] != ',')
		return (ft_perror("rbg ceiling invalid"), -1);
	i++;
	while (gnl[i] == ' ')
		i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (ft_perror("rbg ceiling invalid"), -1);
	if (choice == 'c')
		data->sky.b = ft_atoi(gnl + i);
	else if (choice == 'f')
		data->floor.b = ft_atoi(gnl + i);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	while (gnl[i] == ' ')
		i++;
	if (gnl[i] != '\n')
		return (ft_perror("rbg ceiling invalid"), -1);
	return (0);
}

int	ft_fill_color_f(t_data *data, char *gnl, int i)
{
	if (gnl[i] >= '0' && gnl[i] <= '9')
		data->floor.r = ft_atoi(gnl + i);
	else
		return (ft_perror("rbg floor invalid"), -1);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	while (gnl[i] == ' ')
		i++;
	if (gnl[i] != ',')
		return (ft_perror("rbg floor invalid"), -1);
	i++;
	while (gnl[i] == ' ')
		i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (ft_perror("rbg floor invalid"), -1);
	data->floor.g = ft_atoi(gnl + i);
	if (ft_get_blue(data, gnl, i, 'f') != 0)
		return (-1);
	return (0);
}

//Function	: Recovers the color of the floor
//Param 	: The struct t_data and the line containing the RGB values
//Return	: ERROR --> -1 || SUCCESS --> 0
int	ft_get_color_f(t_data *data, char *gnl)
{
	int	i;

	i = 1;
	if (gnl[0] == 'F' && gnl[1] == ' ')
	{
		if (data->floor.check)
			return (ft_perror("double rgb floor"), -1);
		while (gnl[i] == ' ')
			i++;
		if (ft_fill_color_f(data, gnl, i) != 0)
			return (-1);
		if (data->floor.r < 0 || data->floor.g < 0 || data->floor.b < 0 || \
			data->floor.r > 255 || data->floor.g > 255 || data->floor.b > 255)
			return (ft_perror("rgb floor > 255"), -1);
		data->nb_param = data->nb_param + 1;
		data->floor.check = true;
	}
	return (0);
}

int	ft_fill_color_c(t_data *data, char *gnl, int i)
{
	if (gnl[i] >= '0' && gnl[i] <= '9')
		data->sky.r = ft_atoi(gnl + i);
	else
		return (ft_perror("rbg ceiling invalid"), -1);
	while (gnl[i] >= '0' && gnl[i] <= '9')
		i++;
	while (gnl[i] == ' ')
		i++;
	if (gnl[i] != ',')
		return (ft_perror("rbg ceiling invalid"), -1);
	i++;
	while (gnl[i] == ' ')
		i++;
	if (!(gnl[i] >= '0' && gnl[i] <= '9'))
		return (ft_perror("rbg ceiling invalid"), -1);
	data->sky.g = ft_atoi(gnl + i);
	if (ft_get_blue(data, gnl, i, 'c') != 0)
		return (-1);
	return (0);
}

//Function	: Recovers the color of the sky
//Param 	: The struct t_data and the line containing the RGB values
//Return	: ERROR --> -1 || SUCCESS --> 0
int	ft_get_color_c(t_data *data, char *gnl)
{
	int	i;

	i = 1;
	if (gnl[0] == 'C' && gnl[1] == ' ')
	{
		if (data->sky.check)
			return (ft_perror("double rgb ceiling"), -1);
		while (gnl[i] == ' ')
			i++;
		if (ft_fill_color_c(data, gnl, i) != 0)
			return (-1);
		if (data->sky.r < 0 || data->sky.g < 0 || data->sky.b < 0 || \
			data->sky.r > 255 || data->sky.g > 255 || data->sky.b > 255)
			return (ft_perror("rgb ceiling > 255"), -1);
		data->nb_param = data->nb_param + 1;
		data->sky.check = true;
	}
	return (0);
}
