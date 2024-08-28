/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:13:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/28 11:47:23 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*	Function	: Verifie l'extension de la map et 
		initialise les elements de la struct data
	Param 	: La struct data, et le nom de la map
	Return	: ERROR --> 1 || SUCCESS --> 0*/
static int	ft_check_arg(t_data *data, char *arg_map)
{
	int	len;

	data->map = NULL;
	data->m = NULL;
	data->textures[0].path = NULL;
	data->textures[1].path = NULL;
	data->textures[2].path = NULL;
	data->textures[3].path = NULL;
	data->floor.check = false;
	data->sky.check = false;
	len = ft_strlen_cub(arg_map, 0);
	if (len <= 4)
		return (-1);
	if (arg_map[len - 4] != '.')
		return (-1);
	if (arg_map[len - 3] != 'c')
		return (-1);
	if (arg_map[len - 2] != 'u')
		return (-1);
	if (arg_map[len - 1] != 'b')
		return (-1);
	return (0);
}

static int	ft_parser(t_data *data, int ac, char **av)
{
	if (ac != 2)
		return (ft_perror("bad number of arguments"), -1);
	if (ft_check_arg(data, av[1]) != 0)
		return (ft_perror("the map file is not .cub"), -1);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		return (ft_perror("open failed"), -1);
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
