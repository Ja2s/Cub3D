/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:31:54 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/17 16:43:49 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

#define M_PI 3.14159265358979323846

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
}

void	map_init(t_data *data)
{
	data->map = malloc(sizeof (char *) * 11);
	int i = 0;
	while (i < 11)
	{
		data->map[i] = malloc(sizeof(char) * 11);
		i++;
	}
	data->map[11] = '\0';
	data->map[0] = "1111111111\0";
	data->map[10] = "1111111111\0";
	data->map[1] = "1000000001\0";
	data->map[2] = "1000000001\0";
	data->map[3] = "10000E0001\0";
	data->map[4] = "1000000001\0";
	data->map[5] = "1000000001\0";
	data->map[6] = "1000000001\0";
	data->map[7] = "1000000001\0";
	data->map[8] = "1000000001\0";
	data->map[9] = "1000000001\0";
}

void	data_init(t_data *data)
{
	data->width = 800;
	data->height = 600;
	map_init(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
}

void	player_init(t_player *player)
{
	player->pos_x = 5;
	player->pos_y = 3;
	player->dir_x = -1;
	player->dir_y = 0;
	player->FOV = 60.0 * M_PI / 180.0;
	player->plane_x = player->dir_x * player->FOV;
	player->plane_y = player->dir_y * player->FOV;
}

void	raycasting(t_data *data, t_player *player)
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double lenght;
	int x;
	
	x = 0;
	while (x < data->width)
	{
		//-------calcul angle des rayons
		camera_x = 2 * x / (double)data->width - 1;
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;
		//------normalisation de la dir sur 1
		lenght = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
		ray_dir_x /= lenght;
		ray_dir_y /= lenght;
		//-------calcul de la distance avant le mur 
		data->raycast.map_x = (int)player->pos_x;
		data->raycast.map_y = (int)player->pos_y;
		data->raycast.hit = 0;
		if (ray_dir_x < 0)
		{
			data->raycast.delta_dist_x = -1;
			data->raycast.side_dist_x = (player->pos_x - data->raycast.map_x);
		}
		else
		{
			data->raycast.delta_dist_x = 1;
			data->raycast.side_dist_x = (data->raycast.map_x + 1.0) * data->raycast.delta_dist_x;
		}
		if (ray_dir_y < 0)
        {
            data->raycast.delta_dist_y = -1;
            data->raycast.side_dist_y = (player->pos_y - data->raycast.map_y) * data->raycast.delta_dist_y;
        }
        else
        {
            data->raycast.delta_dist_y = 1;
            data->raycast.side_dist_y = (data->raycast.map_y + 1.0 - player->pos_y) * data->raycast.delta_dist_y;
        }
		while (data->raycast.hit == 0)
		{
			
		}
		x++;
	}
}

int	main(void)
{
	t_data		data;
	t_player 	player;
	
	player_init(&player);
	data_init(&data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
}



// gcc -Wall -Werror -Wextra main.c -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm