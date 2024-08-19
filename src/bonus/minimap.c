/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:55:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/19 23:53:50 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_init(t_minimap *minimap, t_data *data)
{
	minimap->size_x = data->size_x;
	minimap->size_y = data->size_y;
	minimap->size = 10;
	if (minimap->size_x >= 50 || minimap->size_y >= 50)
		minimap->size = 8;
	if (minimap->size_x >= 70 || minimap->size_y >= 70)
		minimap->size = 6;
	if (minimap->size_x >= 90 || minimap->size_y >= 90)
		minimap->size = 4;
	if (minimap->size_x >= 110 || minimap->size_y >= 110)
		minimap->size = 2;
	minimap->pos_x = data->width - (50);
	minimap->pos_y = 50;
	minimap->x = 0;
}

void	player_drawer(t_minimap *minimap, t_data *data)
{
	minimap->player_x = minimap->pos_x - data->player.pos_x * minimap->size;
	minimap->player_y = minimap->pos_y + data->player.pos_y * minimap->size;
	minimap->i = 0;
	while (minimap->i <= (minimap->size / 1.66))
	{
		minimap->j = 0;
		while (minimap->j <= (minimap->size / 1.66))
		{
			my_mlx_pixel_put(data, minimap->player_x + minimap->i + \
			minimap->size, minimap->player_y + minimap->j, 0xFFFFFF);
			minimap->j++;
		}
		minimap->i++;
	}
}

void	case_drawer(t_data *data, t_minimap *minimap)
{
	my_mlx_pixel_put(data, minimap->pos_x - (minimap->x * \
	minimap->size) + minimap->i, minimap->pos_y + \
	(minimap->y * minimap->size) + minimap->j, 0x2F2F2F);
}

void	mini_mapper(t_data *data)
{
	t_minimap	minimap;

	minimap_init(&minimap, data);
	while (minimap.x < minimap.size_x)
	{
		minimap.y = 0;
		while (minimap.y < minimap.size_y)
		{
			minimap.i = 0;
			while (minimap.i < minimap.size)
			{
				minimap.j = 0;
				while (minimap.j < minimap.size)
				{
					if (data->map[minimap.y][minimap.x] == '1')
						case_drawer(data, &minimap);
					minimap.j++;
				}
				minimap.i++;
			}
			minimap.y++;
		}
		minimap.x++;
	}
	player_drawer(&minimap, data);
}
