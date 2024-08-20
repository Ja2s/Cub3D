/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:08:18 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 16:13:01 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	keys_init(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->q = 0;
	keys->e = 0;
}

int	load_textures(t_data *data, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, \
	texture->path, &texture->width, &texture->height);
	if (texture->img == NULL)
		return (write(2, "Error\nbad texture\n", 18), FAILURE);
	texture->addr = mlx_get_data_addr(texture->img, \
	&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->addr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	texture_init(t_data *data)
{
	data->textures[0].loaded = 0;
	data->textures[1].loaded = 0;
	data->textures[2].loaded = 0;
	data->textures[3].loaded = 0;
	if (load_textures(data, &data->textures[0]) == FAILURE)
		return (FAILURE);
	else
		data->textures[0].loaded = 1;
	if (load_textures(data, &data->textures[1]) == FAILURE)
		return (FAILURE);
	else
		data->textures[1].loaded = 1;
	if (load_textures(data, &data->textures[2]) == FAILURE)
		return (FAILURE);
	else
		data->textures[2].loaded = 1;
	if (load_textures(data, &data->textures[3]) == FAILURE)
		return (FAILURE);
	else
		data->textures[3].loaded = 1;
	return (SUCCESS);
}

int	data_init(t_data *data)
{
	data->width = 1800;
	data->height = 1000;
	data->win = NULL;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (write(2, "Error\ninit mlx\n", 15), FAILURE);
	data->win = mlx_new_window(data->mlx, data->width, \
	data->height, "Cub3D");
	if (data->win == NULL)
		return (write(2, "Error\ninit win\n", 15), FAILURE);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		return (write(2, "Error\ninit img\n", 15), FAILURE);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->addr == NULL)
		return (write(2, "Error\ninit address\n", 19), FAILURE);
	if (texture_init(data) == FAILURE)
		return (FAILURE);
	keys_init(&data->keys);
	data->floor_color = color_converter(data->floor);
	data->sky_color = color_converter(data->sky);
	return (SUCCESS);
}
