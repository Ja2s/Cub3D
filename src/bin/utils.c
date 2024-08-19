/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:40:51 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/19 23:45:04 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reverse_line(char *line)
{
	int		len;
	int		i;
	int		j;
	char	temp;

	if (line == NULL)
		return ;
	len = ft_strlen(line);
	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = line[i];
		line[i] = line[j];
		line[j] = temp;
		i++;
		j--;
	}
}

void	reverse_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		reverse_line(map[i]);
		i++;
	}
}

unsigned int	color_converter(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_and_sky(t_data *data, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < data->height)
	{
		if (y < draw_start)
			my_mlx_pixel_put(data, x, y, data->sky_color);
		else if (y > draw_end)
			my_mlx_pixel_put(data, x, y, data->floor_color);
		y++;
	}
}
