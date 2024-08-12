/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:55:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/12 10:55:58 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_init(t_minimap *minimap, t_data *data)
{
	minimap->size_x = 24;// Taille de la mini carte en cases
	minimap->size_y = 11;// Taille de la mini carte en cases
	minimap->pos_x = data->width - (50);
	minimap->pos_y = 50;
	minimap->x = 0;
}

void	player_drawer(t_minimap *minimap, t_data *data)
{
	minimap->player_x = minimap->pos_x - data->player.pos_x * 10;
	minimap->player_y = minimap->pos_y + data->player.pos_y * 10;
	minimap->i = 0;
	while (minimap->i <= 6)
	{
		minimap->j = 0;
		while (minimap->j <= 6)
		{
			my_mlx_pixel_put(data, minimap->player_x + minimap->i + 10, minimap->player_y + minimap->j, 0xFFFFFF);  // Rouge pour le joueur
			minimap->j++;
		}
		minimap->i++;
	}
}

void mini_mapper(t_data *data)
{
	t_minimap minimap;

	minimap_init(&minimap, data);
	while (minimap.x < minimap.size_x)
	{
		minimap.y = 0;
		while (minimap.y < minimap.size_y)
		{   
			minimap.i = 0;
			while (minimap.i < 10)
			{
				minimap.j = 0;
				while (minimap.j < 10)
				{
					if (data->map[minimap.y][minimap.x] == '1')
						my_mlx_pixel_put(data, minimap.pos_x - (minimap.x * 10) + minimap.i, minimap.pos_y + (minimap.y * 10) + minimap.j, 0x2F2F2F);  // Mur en noir
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
