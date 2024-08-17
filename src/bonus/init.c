/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:08:18 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/17 14:40:52 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_textures(t_data *data, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, \
	texture->path, &texture->width, &texture->height);
	if (texture->img == NULL)
		return (write(2, "ERROR IMG\n", 10), FAILURE);
	if ((texture->addr = mlx_get_data_addr(texture->img, \
	&texture->bits_per_pixel, &texture->line_length, &texture->endian)) == NULL)
		return (FAILURE);
	return (SUCCESS);
}
int	texture_init(t_data *data)
{
	if (load_textures(data, &data->textures[0]) == FAILURE)
		return (FAILURE);
	if (load_textures(data, &data->textures[1]) == FAILURE)
		return (FAILURE);
	if (load_textures(data, &data->textures[2]) == FAILURE)
		return (FAILURE);
	if (load_textures(data, &data->textures[3]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	data_init(t_data *data)
{
	data->width = 1600;
	data->height = 1000;
	data->win = NULL;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (write(2, "ERROR MLX\n", 10),FAILURE);
	data->win = mlx_new_window(data->mlx, data->width, \
	data->height, "Cub3D");
	if (data->win == NULL)
		return (write(2, "ERROR win\n", 10),FAILURE);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		return (write(2, "ERROR IMG\n", 10),FAILURE);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->addr == NULL)
		return (write(2, "ERROR ADDR\n", 10), FAILURE);
	if (texture_init(data) == FAILURE)
		return (FAILURE);
	data->floor_color = color_converter(data->floor);
	data->sky_color = color_converter(data->sky);
	return (SUCCESS);
}
