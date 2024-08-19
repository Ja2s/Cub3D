/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:51 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 00:40:39 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	drawer(t_data *data)
{
	while (data->rc.y < data->rc.draw_end)
	{
		data->rc.d = data->rc.y * 256 - data->height * \
		128 + data->rc.line_height * 128;
		data->rc.tex_y = ((data->rc.d * \
		data->textures[data->rc.tex_num].height) / data->rc.line_height) / 256;
		data->rc.color = \
		*(unsigned int *)(data->textures[data->rc.tex_num].addr + \
		(data->rc.tex_y * data->textures[data->rc.tex_num].line_length + \
		data->rc.tex_x * \
		(data->textures[data->rc.tex_num].bits_per_pixel / 8)));
		my_mlx_pixel_put(data, data->rc.x, \
		data->rc.y, data->rc.color);
		data->rc.y++;
	}
}

void	wall_drawer(t_data *data, t_player *player)
{
	if (data->rc.side == 0)
		data->rc.wall_x = player->pos_y + \
		data->rc.perp_wall_dist * data->rc.ray_dir_y;
	else
		data->rc.wall_x = player->pos_x + \
		data->rc.perp_wall_dist * data->rc.ray_dir_x;
	data->rc.wall_x -= floor(data->rc.wall_x);
	data->rc.tex_x = (int)(data->rc.wall_x * \
	(double)(data->textures[data->rc.tex_num].width));
	if (data->rc.side == 0 && data->rc.ray_dir_x > 0)
		data->rc.tex_x = data->textures[data->rc.tex_num].width - \
		data->rc.tex_x - 1;
	if (data->rc.side == 1 && data->rc.ray_dir_y < 0)
		data->rc.tex_x = data->textures[data->rc.tex_num].width - \
		data->rc.tex_x - 1;
	data->rc.y = data->rc.draw_start;
	drawer(data);
}

void	raycasting(t_data *data, t_player *player)
{
	data->rc.x = 0;
	while (data->rc.x < data->width)
	{
		start_and_dir(data, player);
		send_ray_helper(data, player);
		hit_checker(data);
		col_wall_sizer(data, player);
		wall_orientation(data);
		wall_drawer(data, player);
		draw_floor_and_sky(data, data->rc.x, \
		data->rc.draw_start, data->rc.draw_end);
		data->rc.x++;
	}
}
