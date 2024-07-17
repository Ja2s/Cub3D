/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:32:03 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/18 01:14:30 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}			t_texture;

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
}
           t_raycast;
typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    char    dir;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
	double	move_speed;
}           t_player;

typedef struct s_data
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    char        **map;
	int			bits_per_pixel;
	int			floor_color;
	int			sky_color;
    int         line_length;
    int         endian;
    int         width;
    int         height;
	t_player	player;
    t_raycast   raycast;
	t_texture	textures[4];
}               t_data;

void raycasting(t_data *data, t_player *player);
