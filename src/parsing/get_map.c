/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:09 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/21 18:20:16 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_loop_fill_map(t_data *data, char *tmp_s1, char *s2)
{
	char	*s1;
	int		check;

	check = 0;
	while (s2)
	{
		if (s2[0] == '\n')
			check = 1;
		else
		{
			if (check)
				return (ft_perror("map discontinuous"), \
				free(s2), free(tmp_s1), -1);
			s1 = ft_strjoin_cub(tmp_s1, s2);
			if (!s1)
				return (ft_perror("empty map"), free(tmp_s1), free(s2), -1);
			free(tmp_s1);
			tmp_s1 = s1;
		}
		free(s2);
		s2 = get_next_line(data->fd);
	}
	data->m = ft_split(tmp_s1, '\n');
	free(tmp_s1);
	return (0);
}

//Function	: Fill the map into a 2D char table
//Param 	: The struct t_data and the fd of .cub
//Return	: ERROR --> 1 || SUCCESS --> 0
static int	ft_fill_map(t_data *data)
{
	char	*tmp_s1;
	char	*s2;

	tmp_s1 = malloc(1);
	if (!tmp_s1)
		return (-1);
	tmp_s1[0] = '\0';
	s2 = get_next_line(data->fd);
	while (s2 && s2[0] == '\n')
	{
		free(s2);
		s2 = get_next_line(data->fd);
	}
	if (!s2)
		return (ft_perror("empty map"), free(tmp_s1), -1);
	if (ft_loop_fill_map(data, tmp_s1, s2) != 0)
		return (-1);
	return (0);
}

/*	Function	: Check the map's char and get 
				the player's orientation and position
	Param 	: The struct t_data, the line of the map to check, 
		the number of players found and the line number
	Return	: ERROR --> -1 || SUCCESS --> 0*/
int	ft_is_map_char_valid(t_data *data, char *s, int *nb_player, int y)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
		{
			data->player.dir = s[i];
			data->player.pos_x = (i + 0.5);
			data->player.pos_y = (y + 0.5);
			*nb_player = *nb_player + 1;
		}
		if (s[i] != '1' && s[i] != '0' && s[i] != ' ' && \
			s[i] != 'N' && s[i] != 'S' && s[i] != 'W' && s[i] != 'E')
			return (ft_perror("invalid char in map"), -1);
		i++;
	}
	return (0);
}

//Function	: Retrieve and verify map contents
//Param 	: The struc t_data
//Return	: ERROR --> -1 || SUCCESS --> 0
int	ft_get_map(t_data *data)
{
	int	i;
	int	nb_player;

	i = 0;
	nb_player = 0;
	if (ft_fill_map(data) != 0)
		return (-1);
	if (ft_cpy_map(data) != 0)
		return (-1);
	reverse_map(data->map);
	while (data->map[i])
	{
		if (ft_is_map_char_valid(data, data->map[i], &nb_player, i) != 0)
			return (-1);
		i++;
	}
	if (nb_player != 1)
		return (ft_perror("incorrect number of players"), -1);
	if (ft_is_map_enclosed_wall(data) != 0)
		return (-1);
	return (0);
}

int	ft_check_same_texture(t_data *data)
{
	if (ft_strcmp_cub(data->textures[0].path, data->textures[1].path) == 0)
		return (ft_perror("same texture"), -1);
	if (ft_strcmp_cub(data->textures[0].path, data->textures[2].path) == 0)
		return (ft_perror("same texture"), -1);
	if (ft_strcmp_cub(data->textures[0].path, data->textures[3].path) == 0)
		return (ft_perror("same texture"), -1);
	if (ft_strcmp_cub(data->textures[1].path, data->textures[2].path) == 0)
		return (ft_perror("same texture"), -1);
	if (ft_strcmp_cub(data->textures[1].path, data->textures[3].path) == 0)
		return (ft_perror("same texture"), -1);
	if (ft_strcmp_cub(data->textures[2].path, data->textures[3].path) == 0)
		return (ft_perror("same texture"), -1);
	return (0);
}
