/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:10:28 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 00:12:25 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	start_and_dir(t_data *data, t_player *player)
{
	data->rc.camera_x = 2 * data->rc.x / (double)data->width - 1;
	data->rc.ray_dir_x = player->dir_x + player->plane_x * data->rc.camera_x;
	data->rc.ray_dir_y = player->dir_y + player->plane_y * data->rc.camera_x;
	data->rc.map_x = (int)player->pos_x;
	data->rc.map_y = (int)player->pos_y;
	data->rc.delta_dist_x = fabs(1 / data->rc.ray_dir_x);
	data->rc.delta_dist_y = fabs(1 / data->rc.ray_dir_y);
}

void	send_ray_helper(t_data *data, t_player *player)
{
	if (data->rc.ray_dir_x < 0)
	{
		data->rc.side_dist_x = (player->pos_x - \
		data->rc.map_x) * data->rc.delta_dist_x;
		data->rc.delta_dist_x = -1;
	}
	else
	{
		data->rc.side_dist_x = (data->rc.map_x + 1.0 - \
		player->pos_x) * data->rc.delta_dist_x;
		data->rc.delta_dist_x = 1;
	}
	if (data->rc.ray_dir_y < 0)
	{
		data->rc.side_dist_y = (player->pos_y - \
		data->rc.map_y) * data->rc.delta_dist_y;
		data->rc.delta_dist_y = -1;
	}
	else
	{
		data->rc.side_dist_y = (data->rc.map_y + 1.0 - \
		player->pos_y) * data->rc.delta_dist_y;
		data->rc.delta_dist_y = 1;
	}
}

void	hit_checker(t_data *data)
{
	data->rc.hit = 0;
	while (data->rc.hit == 0)
	{
		if (data->rc.side_dist_x < data->rc.side_dist_y)
		{
			data->rc.side_dist_x += fabs(1 / data->rc.ray_dir_x);
			data->rc.map_x += (int)data->rc.delta_dist_x;
			data->rc.side = 0;
		}
		else
		{
			data->rc.side_dist_y += fabs(1 / data->rc.ray_dir_y);
			data->rc.map_y += (int)data->rc.delta_dist_y;
			data->rc.side = 1;
		}
		if (data->map[data->rc.map_y][data->rc.map_x] == '1')
			data->rc.hit = 1;
	}
}

void	col_wall_sizer(t_data *data, t_player *player)
{
	if (data->rc.side == 0)
		data->rc.perp_wall_dist = (data->rc.map_x - player->pos_x + \
		(1 - (int)data->rc.delta_dist_x) / 2) / data->rc.ray_dir_x;
	else
		data->rc.perp_wall_dist = (data->rc.map_y - player->pos_y + \
		(1 - (int)data->rc.delta_dist_y) / 2) / data->rc.ray_dir_y;
	data->rc.line_height = (int)(data->height / data->rc.perp_wall_dist);
	data->rc.draw_start = -data->rc.line_height / 2 + data->height / 2;
	if (data->rc.draw_start < 0)
		data->rc.draw_start = 0;
	data->rc.draw_end = data->rc.line_height / 2 + data->height / 2;
	if (data->rc.draw_end >= data->height)
		data->rc.draw_end = data->height - 1;
}

void	wall_orientation(t_data *data)
{
	if (data->rc.side == 0 && data->rc.ray_dir_x < 0)
		data->rc.tex_num = 2;
	else if (data->rc.side == 0 && data->rc.ray_dir_x >= 0)
		data->rc.tex_num = 3;
	else if (data->rc.side == 1 && data->rc.ray_dir_y < 0)
		data->rc.tex_num = 1;
	else
		data->rc.tex_num = 0;
}
