/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:52:19 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/17 15:08:29 by jgavairo         ###   ########.fr       */
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
    else if (keycode == 113)
        data->keys.q = 1;
    else if (keycode == 101)
        data->keys.e = 1;
	else if (keycode == 65505)
        data->player.move_speed = 0.065;
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
    else if (keycode == 113)
        data->keys.q = 0;
    else if (keycode == 101)
        data->keys.e = 0;
	else if (keycode == 65505)
        data->player.move_speed = 0.04;
    return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

