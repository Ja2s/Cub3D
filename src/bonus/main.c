/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:13:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/12 11:36:10 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_init(t_data *data)
{
	data->map = malloc(sizeof(char *) * 12);
	if (!data->map)
		return ;
	data->map[0] = strdup("11111111111111111111111");
	data->map[1] = strdup("10100000000000000000001");
	data->map[2] = strdup("10100000000000000000001");
	data->map[3] = strdup("10100E00000000111111111");
	data->map[4] = strdup("101000000000001        ");
	data->map[5] = strdup("101000000000001        ");
	data->map[6] = strdup("100011100000001        ");
	data->map[7] = strdup("101010000000001        ");
	data->map[8] = strdup("101011100000001        ");
	data->map[9] = strdup("101000100000001        ");
	data->map[10] = strdup("111111111111111        ");
	data->map[11] = NULL;
	reverse_map(data->map);
}

int	ft_get_map(t_data *data)
{
	char	*gnl;

	printf("map : \n");
	gnl = get_next_line(data->fd);
	while (gnl)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(data->fd);
	}
	free(gnl); // Libérer la mémoire allouée par la dernière appel à get_next_line
	return (0);
}

int	ft_parser(t_data *data, int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nNombre d'arguments incorrect\n"), -1);
	if (ft_check_arg(data, av[1]) == 1)
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

	if (ft_parser(&data, argc, argv) == -1)
		return (-1);
	player_init(&data.player);
	data_init(&data);

	raycasting(&data, &data.player);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);

	mlx_loop(data.mlx);
	ft_free_data(data);
	return (0);
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