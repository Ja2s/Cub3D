/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:43:31 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/28 11:50:11 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fordward(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player.pos_x + \
	data->player.dir_x * data->player.move_speed;
	new_pos_y = data->player.pos_y + \
	data->player.dir_y * data->player.move_speed;
	if (is_wall(data, new_pos_x, data->player.pos_y) == 0)
		data->player.pos_x = new_pos_x;
	if (is_wall(data, data->player.pos_x, new_pos_y) == 0)
		data->player.pos_y = new_pos_y;
}

void	move_back(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player.pos_x - \
	data->player.dir_x * data->player.move_speed;
	new_pos_y = data->player.pos_y - \
	data->player.dir_y * data->player.move_speed;
	if (is_wall(data, new_pos_x, data->player.pos_y) == 0)
		data->player.pos_x = new_pos_x;
	if (is_wall(data, data->player.pos_x, new_pos_y) == 0)
		data->player.pos_y = new_pos_y;
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * \
	cos(0.06) - data->player.dir_y * sin(0.06);
	data->player.dir_y = old_dir_x * \
	sin(0.06) + data->player.dir_y * cos(0.06);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * \
	cos(0.06) - data->player.plane_y * sin(0.06);
	data->player.plane_y = old_plane_x * \
	sin(0.06) + data->player.plane_y * cos(0.06);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * \
	cos(-0.06) - data->player.dir_y * sin(-0.06);
	data->player.dir_y = old_dir_x * \
	sin(-0.06) + data->player.dir_y * cos(-0.06);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * \
	cos(-0.06) - data->player.plane_y * sin(-0.06);
	data->player.plane_y = old_plane_x * \
	sin(-0.06) + data->player.plane_y * cos(-0.06);
}
