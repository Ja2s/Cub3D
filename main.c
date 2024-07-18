/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:18:24 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/18 16:28:30 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

#define M_PI 3.14159265358979323846

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	map_init(t_data *data)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * 12);
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
	texture->img = mlx_xpm_file_to_image(data->mlx, \
	path, &texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, \
	&texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	data_init(t_data *data)
{
	data->width = 1200;
	data->height = 800;
	map_init(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, \
	data->height, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	data->floor_color = 0x8B4513;
	data->sky_color = 0x323c43;
	load_textures(data, &data->textures[0], "textures/text1.xpm");
	load_textures(data, &data->textures[1], "textures/text1.xpm");
	load_textures(data, &data->textures[2], "textures/text2.xpm");
	load_textures(data, &data->textures[3], "textures/text2.xpm");
}

void	player_init(t_player *player)
{
	player->pos_x = 5;
	player->pos_y = 3;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66; // Ajustement du FOV
	player->move_speed = 0.1;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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

void	fordward(t_data *data)
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

void	move_back(t_data *data)
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

void	rotate_left(t_data *data)
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

void	rotate_right(t_data *data)
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

void	move_left(t_data *data)
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

void	move_right(t_data *data)
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

int	key_press(int keycode, t_data *data)
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

void	start_and_dir(t_data *data, t_player *player)
{
	// Calculer la position de depart et la direction du rayon
	data->rc.camera_x = 2 * data->rc.x / (double)data->width - 1;
	data->rc.ray_dir_x = player->dir_x + player->plane_x * data->rc.camera_x;
	data->rc.ray_dir_y = player->dir_y + player->plane_y * data->rc.camera_x;
	// Dans quelle case de la carte nous sommes
	data->rc.map_x = (int)player->pos_x;
	data->rc.map_y = (int)player->pos_y;
	// Longueur du rayon depuis la position actuelle jusqu'au prochain bord de case ( fabs pour passer en valeur absolue dans le cas ou nous nous orientons vers le negatif de la carte)
	data->rc.delta_dist_x = fabs(1 / data->rc.ray_dir_x);
	data->rc.delta_dist_y = fabs(1 / data->rc.ray_dir_y);
}

void	send_ray_helper(t_data *data, t_player *player)
{
	// Calculer la distance entre le joueur et la premiere ligne vertical ou horizontal que le rayon vas toucher (side dist, cest pour calculer le bord de la map ou le bord de la case ou nous sommes?) 
	if (data->rc.ray_dir_x < 0)
	{
		data->rc.side_dist_x = (player->pos_x - data->rc.map_x) * data->rc.delta_dist_x;
		data->rc.delta_dist_x = -1;
	}
	else
	{
		data->rc.side_dist_x = (data->rc.map_x + 1.0 - player->pos_x) * data->rc.delta_dist_x;
		data->rc.delta_dist_x = 1;
	}
	if (data->rc.ray_dir_y < 0)
	{
		data->rc.side_dist_y = (player->pos_y - data->rc.map_y) * data->rc.delta_dist_y;
		data->rc.delta_dist_y = -1;
	}
	else
	{
		data->rc.side_dist_y = (data->rc.map_y + 1.0 - player->pos_y) * data->rc.delta_dist_y;
		data->rc.delta_dist_y = 1;
	}
}

void	hit_checker(t_data *data)
{
	// Effectuer le DDA
	data->rc.hit = 0;
	while (data->rc.hit == 0)
	{
		// Passer à la prochaine case de la carte, soit en direction x, soit en direction y (on utilise fabs pour la valeur absolue, car si on avance ver une direction -- on veux savoir combien en ++)
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
		// Vérifier si le rayon a touché un mur
		if (data->map[data->rc.map_y][data->rc.map_x] == '1')
			data->rc.hit = 1;
	}
}

void	col_wall_sizer(t_data *data, t_player *player)
{
	// calculer suivant si le mur est horizontal ou vertical le calcul qui sera necessaire au moment de dessiner le mur avec une taille differente en focntion de la distance
	if (data->rc.side == 0)
		data->rc.perp_wall_dist = (data->rc.map_x - player->pos_x + (1 - (int)data->rc.delta_dist_x) / 2) / data->rc.ray_dir_x;
	else
		data->rc.perp_wall_dist = (data->rc.map_y - player->pos_y + (1 - (int)data->rc.delta_dist_y) / 2) / data->rc.ray_dir_y;
	// Calculer la hauteur de la ligne à dessiner sur l'écran
	data->rc.line_height = (int)(data->height / data->rc.perp_wall_dist);
	// Calculer les pixels les plus bas et les plus hauts pour remplir la bande actuelle
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
		data->rc.tex_num = 0; // Mur vers l'est
	else if (data->rc.side == 0 && data->rc.ray_dir_x >= 0)
		data->rc.tex_num = 1; // Mur vers l'ouest
	else if (data->rc.side == 1 && data->rc.ray_dir_y < 0)
		data->rc.tex_num = 2; // Mur vers le nord
	else
		data->rc.tex_num = 3; // Mur vers le sud
}

void	wall_drawer(t_data *data, t_player *player)
{
	//calcul coordonnees textures
	if (data->rc.side == 0)
		data->rc.wall_x = player->pos_y + data->rc.perp_wall_dist * data->rc.ray_dir_y;
	else
		data->rc.wall_x = player->pos_x + data->rc.perp_wall_dist * data->rc.ray_dir_x;
	data->rc.wall_x -= floor(data->rc.wall_x);
	data->rc.tex_x = (int)(data->rc.wall_x * (double)(data->textures[data->rc.tex_num].width));
	if (data->rc.side == 0 && data->rc.ray_dir_x > 0)
		data->rc.tex_x = data->textures[data->rc.tex_num].width - data->rc.tex_x - 1;
	if (data->rc.side == 1 && data->rc.ray_dir_y < 0)
		data->rc.tex_x = data->textures[data->rc.tex_num].width - data->rc.tex_x - 1;
	// Dessiner les pixels de la bande en utilisant une boucle while
	data->rc.y = data->rc.draw_start;
	while (data->rc.y < data->rc.draw_end)
	{
		data->rc.d = data->rc.y * 256 - data->height * 128 + data->rc.line_height * 128;
		data->rc.tex_y = ((data->rc.d * data->textures[data->rc.tex_num].height) / data->rc.line_height) / 256;
		data->rc.color = *(unsigned int*)(data->textures[data->rc.tex_num].addr + (data->rc.tex_y * data->textures[data->rc.tex_num].line_length + data->rc.tex_x * (data->textures[data->rc.tex_num].bits_per_pixel / 8)));
		my_mlx_pixel_put(data, data->rc.x, data->rc.y, data->rc.color);
		data->rc.y++;
	}
}

void	raycasting(t_data *data, t_player *player)
{
	data->rc.x = 0;
	draw_floor_and_sky(data);
	while (data->rc.x < data->width)
	{
		start_and_dir(data, player);
		send_ray_helper(data, player);
		hit_checker(data);
		col_wall_sizer(data, player);
		wall_orientation(data);
		wall_drawer(data, player);
		data->rc.x++;
	}
}

int	main(void)
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
