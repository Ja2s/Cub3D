/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:27:44 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/21 17:39:27 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_perror(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}

void	free_mlx(t_data *data)
{
	if (data->ok_win == 1)
		mlx_destroy_window(data->mlx, data->win);
	if (data->ok_img == 1)
		mlx_destroy_image(data->mlx, data->img);
	if (data->textures[0].loaded == 1)
		mlx_destroy_image(data->mlx, data->textures[0].img);
	if (data->textures[1].loaded == 1)
		mlx_destroy_image(data->mlx, data->textures[1].img);
	if (data->textures[2].loaded == 1)
		mlx_destroy_image(data->mlx, data->textures[2].img);
	if (data->textures[3].loaded == 1)
		mlx_destroy_image(data->mlx, data->textures[3].img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_path(t_data *data)
{
	if (data->textures[0].path)
		free(data->textures[0].path);
	if (data->textures[1].path)
		free(data->textures[1].path);
	if (data->textures[2].path)
		free(data->textures[2].path);
	if (data->textures[3].path)
		free(data->textures[3].path);
}

void	ft_free_data(int ac, t_data data)
{
	int	i;

	if (ac != 2)
		return ;
	free_path(&data);
	i = 0;
	if (data.m)
	{
		while (data.m[i])
			free(data.m[i++]);
		free(data.m);
	}
	i = 0;
	if (data.map)
	{
		while (data.map[i])
			free(data.map[i++]);
		free(data.map);
	}
	if (data.ok_map == 1 && data.ok_mlx == 1)
		free_mlx(&data);
}
