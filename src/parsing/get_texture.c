/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:26:49 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/26 14:09:58 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_get_no(t_data *data, char *gnl)
{
	int	i;

	i = 2;
	if (gnl[0] == 'N' && gnl[1] == 'O' && gnl[2] == ' ')
	{
		while (gnl[i] == ' ')
			i++;
		if (gnl[i] == '\n')
			return (ft_perror("texture north empty"), -2);
		if (data->textures[0].path)
			return (ft_perror("doublon texture"), -2);
		data->textures[0].path = ft_strdup_cub(gnl + i, 2);
		if (!data->textures[0].path)
			return (ft_perror("malloc failed"), -1);
		data->nb_param = data->nb_param + 1;
	}
	return (0);
}

static int	ft_get_so(t_data *data, char *gnl)
{
	int	i;

	i = 2;
	if (gnl[0] == 'S' && gnl[1] == 'O' && gnl[2] == ' ')
	{
		while (gnl[i] == ' ')
			i++;
		if (gnl[i] == '\n')
			return (ft_perror("texture south empty"), -2);
		if (data->textures[1].path)
			return (ft_perror("doublon texture"), -2);
		data->textures[1].path = ft_strdup_cub(gnl + i, 2);
		if (!data->textures[1].path)
			return (ft_perror("malloc failed"), -1);
		data->nb_param = data->nb_param + 1;
	}
	return (0);
}

static int	ft_get_we(t_data *data, char *gnl)
{
	int	i;

	i = 2;
	if (gnl[0] == 'W' && gnl[1] == 'E' && gnl[2] == ' ')
	{
		while (gnl[i] == ' ')
			i++;
		if (gnl[i] == '\n')
			return (ft_perror("texture weast empty"), -2);
		if (data->textures[2].path)
			return (ft_perror("doublon texture"), -2);
		data->textures[2].path = ft_strdup_cub(gnl + i, 2);
		if (!data->textures[2].path)
			return (ft_perror("malloc failed"), -1);
		data->nb_param = data->nb_param + 1;
	}
	return (0);
}

static int	ft_get_ea(t_data *data, char *gnl)
{
	int	i;

	i = 2;
	if (gnl[0] == 'E' && gnl[1] == 'A' && gnl[2] == ' ')
	{
		while (gnl[i] == ' ')
			i++;
		if (gnl[i] == '\n')
			return (ft_perror("texture east empty"), -2);
		if (data->textures[3].path)
			return (ft_perror("bad texture"), -2);
		data->textures[3].path = ft_strdup_cub(gnl + i, 2);
		if (!data->textures[3].path)
			return (ft_perror("malloc failed"), -1);
		data->nb_param = data->nb_param + 1;
	}
	return (0);
}

int	ft_get_texture(t_data *data)
{
	char	*gnl;
	int		tmp_count;

	data->nb_param = 0;
	gnl = get_next_line(data->fd);
	while (gnl && data->nb_param < 6)
	{
		tmp_count = data->nb_param;
		if (ft_get_no(data, gnl) != 0 || ft_get_so(data, gnl) != 0 \
		|| ft_get_we(data, gnl) != 0 || ft_get_ea(data, gnl) != 0 \
		|| ft_get_color_f(data, gnl) == -1 || ft_get_color_c(data, gnl) == -1)
			return (free(gnl), -1);
		if (tmp_count == data->nb_param && gnl[0] != '\n')
			return (ft_perror("invalid char in .cub"), free(gnl), -1);
		free(gnl);
		if (data->nb_param < 6)
			gnl = get_next_line(data->fd);
	}
	if (!gnl)
		return (ft_perror("missing texture"), free(gnl), -1);
	if (ft_check_same_texture(data) != 0)
		return (-1);
	return (data->nb_param);
}
