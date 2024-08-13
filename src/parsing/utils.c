/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:32:15 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/13 12:54:02 by rasamad          ###   ########.fr       */
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

//Function	: Verifie l'extension de la map et initialise les elements de la struct data
//Param 	: La struct data, et le nom de la map
//Return	: ERROR --> 1 || SUCCESS --> 0
int	ft_check_arg(t_data *data, char *arg_map)
{
	int	len;

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
	data->textures[0].path = NULL;
	data->textures[1].path = NULL;
	data->textures[2].path = NULL;
	data->textures[3].path = NULL;
	data->floor.check = false;
	data->sky.check = false;
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

void	ft_free_data(t_data data)
{
	int	i;

	if (data.textures[0].path)
		free(data.textures[0].path);
	if (data.textures[1].path)
		free(data.textures[1].path);
	if (data.textures[2].path)
		free(data.textures[2].path);
	if (data.textures[3].path)
		free(data.textures[3].path);
	i = 0;
	if (!data.map)
		return ;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		free(data.map[i]);
		i++;
	}
	free(data.map);
}
