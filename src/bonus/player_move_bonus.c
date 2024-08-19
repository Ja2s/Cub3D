/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:46:22 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 00:06:53 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_left(t_data *data)
{
	double	perp_x;
	double	perp_y;
	double	new_pos_x;
	double	new_pos_y;

	perp_x = -data->player.dir_y;
	perp_y = data->player.dir_x;
	new_pos_x = data->player.pos_x + perp_x * (data->player.move_speed / 2);
	new_pos_y = data->player.pos_y + perp_y * (data->player.move_speed / 2);
	if (is_wall(data, new_pos_x, data->player.pos_y) == 0)
		data->player.pos_x = new_pos_x;
	if (is_wall(data, data->player.pos_x, new_pos_y) == 0)
		data->player.pos_y = new_pos_y;
}

void	move_right(t_data *data)
{
	double	perp_x;
	double	perp_y;
	double	new_pos_x;
	double	new_pos_y;

	perp_x = data->player.dir_y;
	perp_y = -data->player.dir_x;
	new_pos_x = data->player.pos_x + perp_x * (data->player.move_speed / 2);
	new_pos_y = data->player.pos_y + perp_y * (data->player.move_speed / 2);
	if (is_wall(data, new_pos_x, data->player.pos_y) == 0)
		data->player.pos_x = new_pos_x;
	if (is_wall(data, data->player.pos_x, new_pos_y) == 0)
		data->player.pos_y = new_pos_y;
}
