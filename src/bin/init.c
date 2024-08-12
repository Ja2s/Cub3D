/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:08:18 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/12 11:18:39 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_data *data, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, \
	texture->path, &texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, \
	&texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	data_init(t_data *data)
{
	data->width = 1600;
	data->height = 1000;
	map_init(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, \
	data->height, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	data->floor_color = color_converter(data->floor);
	data->sky_color = color_converter(data->sky);
	load_textures(data, &data->textures[0]);
	load_textures(data, &data->textures[1]);
	load_textures(data, &data->textures[2]);
	load_textures(data, &data->textures[3]);
}
