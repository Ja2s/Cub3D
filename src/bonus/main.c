/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:13:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/14 13:10:26 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Function	: Lance le parsing du programme
//Param 	: La struct data, le nombre et le contenue des argument du main
//Return	: ERROR --> 1 || SUCCESS --> 0
int	ft_parser(t_data *data, int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nNombre d'arguments incorrect\n"), -1);
	if (ft_check_arg(data, av[1]) != 0)
		return (printf("Error\nLe fichier de description de scène doit avoir pour extension .cub\n"), -1);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		return (printf("Error\nOpen failed\n"), -1);
	if (ft_get_texture(data) < 6)
		return (-1);
	if (ft_get_map(data) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = NULL;
	if (ft_parser(&data, argc, argv) != 0)
		return (ft_free_data(data), -1);
	
	player_init(&data.player);
	data_init(&data);

	raycasting(&data, &data.player);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);

	mlx_loop(data.mlx);

	return (ft_free_data(data), 0);
}

// gcc -Wall -Werror -Wextra main.c -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm -o cub3d
/*
void start_and_dir(t_data *data, t_player *player)

	But : Déterminer la direction dans laquelle un rayon est lancé à partir de la position du joueur.
	Ce qu'elle fait : Calcule où se trouve le joueur et dans quelle direction le rayon partira.

void send_ray_helper(t_data *data, t_player *player)

	But : Calculer la distance entre le joueur et le prochain mur.
	Ce qu'elle fait : Détermine les distances aux bords de la case en fonction de la direction du rayon.

void hit_checker(t_data *data)

	But : Vérifier quand le rayon touche un mur.
	Ce qu'elle fait : Avance pas à pas jusqu'à ce que le rayon rencontre un mur.

void col_wall_sizer(t_data *data, t_player *player)

	But : Calculer la taille du mur à dessiner.
	Ce qu'elle fait : Calcule la hauteur du mur en fonction de la distance entre le joueur et le mur.

void wall_orientation(t_data *data)

	But : Déterminer quel côté du mur le rayon a touché.
	Ce qu'elle fait : Identifie l'orientation du mur touché (nord, sud, est, ou ouest).

void wall_drawer(t_data *data, t_player *player)

	But : Dessiner le mur sur l'écran.
	Ce qu'elle fait : Utilise la texture appropriée pour dessiner le mur, en fonction de l'endroit où il a été touché.

void mini_mapper(t_data *data)

	But : Dessiner une mini-carte de l'environnement.
	Ce qu'elle fait : Affiche une petite carte avec la position des murs et du joueur.

void raycasting(t_data *data, t_player *player)

	But : Lancer des rayons pour dessiner la scène.
	Ce qu'elle fait : Utilise toutes les fonctions précédentes pour lancer des rayons et dessiner les murs, puis affiche la mini-carte
*/