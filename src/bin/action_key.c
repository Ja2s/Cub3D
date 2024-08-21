/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:55:28 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/21 16:30:31 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	else if (keycode == 97)
		data->keys.a = 1;
	else if (keycode == 115)
		data->keys.s = 1;
	else if (keycode == 100)
		data->keys.d = 1;
	else if (keycode == 65361)
		data->keys.q = 1;
	else if (keycode == 65363)
		data->keys.e = 1;
	else if (keycode == 65505)
		data->player.move_speed = 0.065;
	else if (keycode == 65307)
		close_window(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	else if (keycode == 97)
		data->keys.a = 0;
	else if (keycode == 115)
		data->keys.s = 0;
	else if (keycode == 100)
		data->keys.d = 0;
	else if (keycode == 65361)
		data->keys.q = 0;
	else if (keycode == 65363)
		data->keys.e = 0;
	else if (keycode == 65505)
		data->player.move_speed = 0.04;
	return (0);
}

int	close_window(t_data *data)
{
	ft_free_data(2, *data);
	exit(0);
}
