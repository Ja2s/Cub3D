/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:10:28 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/12 11:16:35 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	// Calculer la distance entre le joueur et les bords de la case pour savoir quel mur le rayon va toucher
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
		data->rc.tex_num = 2; // Mur vers l'est
	else if (data->rc.side == 0 && data->rc.ray_dir_x >= 0)
		data->rc.tex_num = 3; // Mur vers l'ouest
	else if (data->rc.side == 1 && data->rc.ray_dir_y < 0)
		data->rc.tex_num = 0; // Mur vers le nord
	else
		data->rc.tex_num = 1; // Mur vers le sud
}
