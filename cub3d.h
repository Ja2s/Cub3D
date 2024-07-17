/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:32:03 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/17 16:27:18 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>

typedef struct s_raycast
{
	int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    int     hit;
    int     side;
}			t_raycast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	char		**map;
	int			bits_per_pixel;
	int			line_lenght;
	int			endian;
	int			width;
	int			height;
	t_raycast	raycast;
}				t_data;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	FOV;
	char	dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

