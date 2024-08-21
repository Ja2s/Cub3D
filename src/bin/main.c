/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:13:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/21 16:33:26 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* 	//Function	: Lance le parsing du programme
	//Param 	: La struct data, le nombre et le contenue des argument du main
	//Return	: ERROR --> 1 || SUCCESS --> 0 */
int	ft_perror(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}
	
int	ft_parser(t_data *data, int ac, char **av)
{
	if (ac != 2)
		return (printf("Error: bad number of arguments\n"), -1);
	if (ft_check_arg(data, av[1]) != 0)
		return (printf("Error: the map file is not .cub\n"), -1);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		return (printf("Error: open failed\n"), -1);
	if (ft_get_texture(data) < 6)
		return (-1);
	if (ft_get_map(data) != 0)
		return (-1);
	data->ok_map = 1;
	return (0);
}

int	game_loop(t_data *data)
{
	if (data->keys.w)
		fordward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.s)
		move_back(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.q)
		rotate_left(data);
	if (data->keys.e)
		rotate_right(data);
	raycasting(data, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = NULL;
	init_ok(&data);
	if (ft_parser(&data, argc, argv) != 0)
		return (ft_free_data(argc, data), -1);
	player_init(&data.player);
	if (data_init(&data) == FAILURE)
		return (ft_free_data(argc, data), FAILURE);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop(data.mlx);
	return (ft_free_data(argc, data), 0);
}
