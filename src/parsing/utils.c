/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:32:15 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/20 18:22:15 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen_cub(char *s, int choice)
{
	int	i;

	i = 0;
	if (choice == 0)
		while (s[i])
			i++;
	else if (choice == 1)
		while (s[i] && !(s[i] >= '0' && s[i] <= '9'))
			i++;
	else if (choice == 2)
		while (s[i] && s[i] != '\n')
			i++;
	return (i);
}

/*	Function	: Verifie l'extension de la map et 
		initialise les elements de la struct data
	Param 	: La struct data, et le nom de la map
	Return	: ERROR --> 1 || SUCCESS --> 0*/
int	ft_check_arg(t_data *data, char *arg_map)
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

char	*ft_strdup_cub(char *str, int choice)
{
	size_t	i;
	size_t	len_src;
	char	*tmp;

	i = 0;
	len_src = ft_strlen_cub(str, choice);
	tmp = malloc((len_src + 1) * sizeof(char));
	if (tmp == NULL)
		return (tmp);
	while (i < len_src)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	free_mlx(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
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

char	*ft_strjoin_cub(char *s1, char *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;
	size_t		len_1;
	size_t		len_2;

	len_1 = tmp_len(s1, 2);
	len_2 = tmp_len(s2, 1);
	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	s3 = malloc((len_1 + len_2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	while (i < len_1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len_2 && s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
