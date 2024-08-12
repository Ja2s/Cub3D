/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:52:19 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/12 11:35:29 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_data *data)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == 100)
		rotate_right(data);
	else if (keycode == 97)
		rotate_left(data);
	else if (keycode == 119)
		fordward(data);
	else if (keycode == 115)
		move_back(data);
	else if (keycode == 101)
		move_left(data);
	else if (keycode == 113)
		move_right(data);
	raycasting(data, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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

