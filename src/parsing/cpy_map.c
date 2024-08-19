/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:52 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/19 18:15:51 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*	Function	: Verifie autour de chaque char dans la map 
s'il nest pas a cote d'un espace ou d'une fin de map (\0)
	Param 	: La struct data, l'indice i et j a verifier
	Return	: ERROR --> -1 || SUCCESS --> 0*/
static int	ft_check_around_char(t_data *data, int i, int j)
{
	if (i == 0 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (printf("Error\nOpen map\n"), -1);
	if (i == data->size_y - 1 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (printf("Error\nOpen map\n"), -1);
	if (j == 0 && (data->m[i][j] != '1' && data->m[i][j] != ' '))
		return (printf("Error\nOpen map. Forbidden character at j == 0\n"), -1);
	if (j > 0 && i > 0)
	{
		if (data->m[i][j] == '0' || data->m[i][j] == 'N' || \
		data->m[i][j] == 'S' || data->m[i][j] == 'E' || \
		data->m[i][j] == 'W')
		{
			if (data->m[i - 1][j] == ' ' || data->m[i - 1][j] == '\0')
				return (printf("Error\nOpen map. Char at up\n"), -1);
			if (data->m[i + 1][j] == ' ' || data->m[i + 1][j] == '\0')
				return (printf("Error\nOpen map. Char at down\n"), -1);
			if (data->m[i][j - 1] == ' ' || data->m[i][j - 1] == '\0')
				return (printf("Error\nOpen map. Char at left\n"), -1);
			if (data->m[i][j + 1] == ' ' || data->m[i][j + 1] == '\0')
				return (printf("Error\nOpen map. Char at right\n"), -1);
		}
	}
	return (0);
}

//Function	: Verifie si la map est bien entourer par des murs
//Param 	: La struct data
//Return	: ERROR --> -1 || SUCCESS --> 0
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
		return (printf("Error\nMalloc m\n"), -1);
	while (i < data->size_y)
	{
		data->map[i] = malloc((data->size_x + 1) * (sizeof(char)));
		if (!data->map)
			return (printf("Error\nMalloc m[i]\n"), -1);
		i++;
	}
	return (0);
}

//Function	: Copy la map dans un tableau 2d avec des espaces
//Param 	: La struct data
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
