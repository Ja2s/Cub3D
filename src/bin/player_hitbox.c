/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:01:31 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 00:06:27 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (data->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	is_wall(t_data *data, double x, double y)
{
	double	offsets[4][2];
	int		i;

	offsets[0][0] = 0.1;
	offsets[0][1] = 0.1;
	offsets[1][0] = -0.1;
	offsets[1][1] = 0.1;
	offsets[2][0] = 0.1;
	offsets[2][1] = -0.1;
	offsets[3][0] = -0.1;
	offsets[3][1] = -0.1;
	i = 0;
	while (i < 4)
	{
		if (check_wall(data, x + offsets[i][0], y + offsets[i][1]))
			return (1);
		i++;
	}
	return (0);
}
