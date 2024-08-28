/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:52 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/21 18:21:01 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*	Function	: Check around each char in the map
				if it is not next to a space or end of map (\0)
	Param 	:  Struct t_data, index i et j to check
	Return	: ERROR --> -1 || SUCCESS --> 0*/
static int	ft_check_around_char(t_data *data, int i, int j)
{
	if (i == 0 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (ft_perror("map open"), -1);
	if (i == data->size_y - 1 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (ft_perror("map open"), -1);
	if (j == 0 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (ft_perror("map open"), -1);
	if (j > 0 && i > 0)
	{
		if (data->m[i][j] == '0' || data->m[i][j] == 'N' || \
		data->m[i][j] == 'S' || data->m[i][j] == 'E' || \
		data->m[i][j] == 'W')
		{
			if (data->m[i - 1][j] == ' ' || data->m[i - 1][j] == '\0')
				return (ft_perror("map open"), -1);
			if (data->m[i + 1][j] == ' ' || data->m[i + 1][j] == '\0')
				return (ft_perror("map open"), -1);
			if (data->m[i][j - 1] == ' ' || data->m[i][j - 1] == '\0')
				return (ft_perror("map open"), -1);
			if (data->m[i][j + 1] == ' ' || data->m[i][j + 1] == '\0')
				return (ft_perror("map open"), -1);
		}
	}
	return (0);
}

/*	Function 	: Check if the map is surrounded by walls
	Param 		: La struct data
	Return		: ERROR --> -1 || SUCCESS --> 0*/
int	ft_is_map_enclosed_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->m[i])
	{
		j = 0;
		while (data->m[i][j])
		{
			if (ft_check_around_char(data, i, j) != 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ft_get_map_size(t_data *data)
{
	int	i;
	int	len_actual;

	i = 0;
	data->size_x = 0;
	while (data->m[i])
	{
		len_actual = ft_strlen(data->m[i]);
		if (data->size_x < len_actual)
			data->size_x = len_actual;
		i++;
	}
	data->size_y = i;
}

static int	ft_alloc_map(t_data *data)
{
	int	i;

	i = 0;
	data->map = malloc((data->size_y + 1) * (sizeof(char *)));
	if (!data->map)
		return (ft_perror("malloc failed"), -1);
	while (i < data->size_y)
	{
		data->map[i] = malloc((data->size_x + 1) * (sizeof(char)));
		if (!data->map)
			return (ft_perror("malloc failed"), -1);
		i++;
	}
	return (0);
}

//Function	: Copy the map into a 2D array with spaces
//Param 	: The struct t_data
//Return	: ERROR --> -1 || SUCCESS --> 0
int	ft_cpy_map(t_data *data)
{
	int	i;
	int	j;

	ft_get_map_size(data);
	if (ft_alloc_map(data) != 0)
		return (-1);
	i = 0;
	while (data->m[i])
	{
		ft_strcpy(data->map[i], data->m[i]);
		j = ft_strlen(data->m[i]);
		while (j < data->size_x)
		{
			data->map[i][j] = ' ';
			j++;
			data->map[i][j] = 0;
		}
		i++;
	}
	data->map[i] = 0;
	return (0);
}
