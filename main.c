/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:18:24 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/18 11:43:52 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <stdio.h>

#define M_PI 3.14159265358979323846

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void map_init(t_data *data)
{
	data->map = malloc(sizeof(char *) * 12);
	int i = 0;
	while (i < 11)
	{
		data->map[i] = malloc(sizeof(char) * 11);
		i++;
	}
	data->map[0] = "1111111111";
	data->map[1] = "1010000001";
	data->map[2] = "1010000001";
	data->map[3] = "10100E0001";
	data->map[4] = "1010000001";
	data->map[5] = "1010000001";
	data->map[6] = "1000111001";
	data->map[7] = "1010100001";
	data->map[8] = "1010111001";
	data->map[9] = "1010001001";
	data->map[10] = "1111111111";
	data->map[11] = NULL;
}


void	load_textures(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void data_init(t_data *data)
{
	data->width = 1200;
	data->height = 800;
	map_init(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->floor_color = 0x8B4513;
	data->sky_color = 0x323c43;
	load_textures(data, &data->textures[0], "textures/text1.xpm");
	load_textures(data, &data->textures[1], "textures/text1.xpm");
	load_textures(data, &data->textures[2], "textures/text2.xpm");
	load_textures(data, &data->textures[3], "textures/text2.xpm");
}

void player_init(t_player *player)
{
	player->pos_x = 5;
	player->pos_y = 3;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66; // Ajustement du FOV
	player->move_speed = 0.1;
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_floor_and_sky(t_data *data)
{
	int x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y < data->height / 2)
				my_mlx_pixel_put(data, x, y, data->sky_color);
			else
				my_mlx_pixel_put(data, x, y, data->floor_color);
			x++;
		}
		y++;
	}
}

//permet de checker la case ou nous allons aller pour le prochain deplacement voir si cest un mur
int	is_wall(t_data *data, double x, double y)
{
	int map_x;
	int map_y;
	
	//permet de check un poil plus loin que le player, ce qui permet en quelaque sorte de si;uler une hitbox
	x += data->player.dir_x * 0.07;
	y += data->player.dir_y * 0.07;

	map_x = (int)x;
	map_y = (int)y;
	if (data->map[map_y][map_x] == '1')
		return (-1);
	return (0);
}

void fordward(t_data *data)
{
	double new_pos_x;
	double new_pos_y;

	new_pos_x = data->player.pos_x + data->player.dir_x * data->player.move_speed;
	new_pos_y = data->player.pos_y + data->player.dir_y * data->player.move_speed;
	if (is_wall(data, new_pos_x, new_pos_y) == 0)
	{
		data->player.pos_x = new_pos_x;
		data->player.pos_y = new_pos_y;		
	}
}

void move_back(t_data *data)
{
	double new_pos_x;
	double new_pos_y;
	
	new_pos_x = data->player.pos_x - data->player.dir_x * data->player.move_speed;
	new_pos_y = data->player.pos_y - data->player.dir_y * data->player.move_speed;
	if (is_wall(data, new_pos_x, new_pos_y) == 0)
	{
		data->player.pos_x = new_pos_x;
		data->player.pos_y = new_pos_y;		
	}
}

void rotate_left(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(0.05) - data->player.dir_y * sin(0.05);
	data->player.dir_y = old_dir_x * sin(0.05) + data->player.dir_y * cos(0.05);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(0.05) - data->player.plane_y * sin(0.05);
	data->player.plane_y = old_plane_x * sin(0.05) + data->player.plane_y * cos(0.05);
}

void rotate_right(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-0.05) - data->player.dir_y * sin(-0.05);
	data->player.dir_y = old_dir_x * sin(-0.05) + data->player.dir_y * cos(-0.05);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-0.05) - data->player.plane_y * sin(-0.05);
	data->player.plane_y = old_plane_x * sin(-0.05) + data->player.plane_y * cos(-0.05);
}

void move_left(t_data *data)
{
	double perp_x;
	double perp_y;
	double new_pos_x;
	double new_pos_y;

	perp_x = data->player.dir_y;
	perp_y = -data->player.dir_x;
	new_pos_x = data->player.pos_x + perp_x * (data->player.move_speed / 2);
	new_pos_y = data->player.pos_y + perp_y * (data->player.move_speed / 2);
	if (is_wall(data, new_pos_x, new_pos_y) == 0)
	{
		data->player.pos_x = new_pos_x;
		data->player.pos_y = new_pos_y;		
	}
}

void move_right(t_data *data)
{
	double perp_x;
	double perp_y;
	double new_pos_x;
	double new_pos_y;

	perp_x = -data->player.dir_y;
	perp_y = data->player.dir_x;
	new_pos_x = data->player.pos_x + perp_x * (data->player.move_speed / 2);
	new_pos_y = data->player.pos_y + perp_y * (data->player.move_speed / 2);
	if (is_wall(data, new_pos_x, new_pos_y) == 0)
	{
		data->player.pos_x = new_pos_x;
		data->player.pos_y = new_pos_y;		
	}
}

int key_press(int keycode, t_data *data)
{
	printf("keycode = %d\n", keycode);
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



void raycasting(t_data *data, t_player *player)
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int 	x;
	int		y;
	int		tex_num;
	int		tex_x;
	int		draw_end;
	int		line_height;
	int		draw_start;
	double	wall_x;
	double	perp_wall_dist;

	x = 0;
	draw_floor_and_sky(data);
	while (x < data->width)
	{
		// Calculer la position de depart et la direction du rayon
		camera_x = 2 * x / (double)data->width - 1;
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;

		// Dans quelle case de la carte nous sommes
		data->raycast.map_x = (int)player->pos_x;
		data->raycast.map_y = (int)player->pos_y;

		// Longueur du rayon depuis la position actuelle jusqu'à la prochaine x ou y-côté
		data->raycast.delta_dist_x = fabs(1 / ray_dir_x);
		data->raycast.delta_dist_y = fabs(1 / ray_dir_y);

		// Calculer le pas et la distance initiale du côté
		if (ray_dir_x < 0)
		{
			data->raycast.side_dist_x = (player->pos_x - data->raycast.map_x) * data->raycast.delta_dist_x;
			data->raycast.delta_dist_x = -1;
		}
		else
		{
			data->raycast.side_dist_x = (data->raycast.map_x + 1.0 - player->pos_x) * data->raycast.delta_dist_x;
			data->raycast.delta_dist_x = 1;
		}
		if (ray_dir_y < 0)
		{
			data->raycast.side_dist_y = (player->pos_y - data->raycast.map_y) * data->raycast.delta_dist_y;
			data->raycast.delta_dist_y = -1;
		}
		else
		{
			data->raycast.side_dist_y = (data->raycast.map_y + 1.0 - player->pos_y) * data->raycast.delta_dist_y;
			data->raycast.delta_dist_y = 1;
		}

		// Effectuer le DDA
		data->raycast.hit = 0;
		while (data->raycast.hit == 0)
		{
			// Passer à la prochaine case de la carte, soit en direction x, soit en direction y
			if (data->raycast.side_dist_x < data->raycast.side_dist_y)
			{
				data->raycast.side_dist_x += fabs(1 / ray_dir_x);
				data->raycast.map_x += (int)data->raycast.delta_dist_x;
				data->raycast.side = 0;
			}
			else
			{
				data->raycast.side_dist_y += fabs(1 / ray_dir_y);
				data->raycast.map_y += (int)data->raycast.delta_dist_y;
				data->raycast.side = 1;
			}
			// Vérifier si le rayon a touché un mur
			if (data->map[data->raycast.map_y][data->raycast.map_x] == '1')
				data->raycast.hit = 1;
		}

		// Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye)
		if (data->raycast.side == 0)
			perp_wall_dist = (data->raycast.map_x - player->pos_x + (1 - (int)data->raycast.delta_dist_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (data->raycast.map_y - player->pos_y + (1 - (int)data->raycast.delta_dist_y) / 2) / ray_dir_y;

		// Calculer la hauteur de la ligne à dessiner sur l'écran
		line_height = (int)(data->height / perp_wall_dist);

		// Calculer les pixels les plus bas et les plus hauts pour remplir la bande actuelle
		draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height)
			draw_end = data->height - 1;
		//calcul coordonnees textures
		if (data->raycast.side == 0 && ray_dir_x < 0)
			tex_num = 0; // Mur vers l'est
		else if (data->raycast.side == 0 && ray_dir_x >= 0)
			tex_num = 1; // Mur vers l'ouest
		else if (data->raycast.side == 1 && ray_dir_y < 0)
			tex_num = 2; // Mur vers le nord
		else
			tex_num = 3; // Mur vers le sud
		if (data->raycast.side == 0)
			wall_x = player->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = player->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * (double)(data->textures[tex_num].width));
		if (data->raycast.side == 0 && ray_dir_x > 0)
			tex_x = data->textures[tex_num].width - tex_x - 1;
		if (data->raycast.side == 1 && ray_dir_y < 0)
			tex_x = data->textures[tex_num].width - tex_x - 1;
		// Dessiner les pixels de la bande en utilisant une boucle while
		y = draw_start;
		while (y < draw_end)
		{
			int d = y * 256 - data->height * 128 + line_height * 128;
			int tex_y = ((d * data->textures[tex_num].height) / line_height) / 256;
			unsigned int color = *(unsigned int*)(data->textures[tex_num].addr + (tex_y * data->textures[tex_num].line_length + tex_x * (data->textures[tex_num].bits_per_pixel / 8)));
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

int main(void)
{
	t_data	data;

	player_init(&data.player);
	data_init(&data);

	raycasting(&data, &data.player);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);

	mlx_loop(data.mlx);
	return (0);
}



// gcc -Wall -Werror -Wextra main.c -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm -o cub3d
