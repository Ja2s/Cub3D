/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:35:46 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/18 15:42:05 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int	 		width;
	int	 		height;
	int	 		bits_per_pixel;
	int	 		line_length;
	int	 		endian;
}					t_texture;

typedef struct s_raycast
{
	int	 			map_x;
	int	 			map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int	 			hit;
	int	 			side;
	double 			camera_x;
	double 			ray_dir_x;
	double 			ray_dir_y;
	int 			x;
	int				y;
	int				d;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				draw_end;
	int				line_height;
	int				draw_start;
	double			wall_x;
	double			perp_wall_dist;
	unsigned int	color;
}					t_raycast;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	char			dir;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
}					 t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	char			**map;
	int				bits_per_pixel;
	int				floor_color;
	int				sky_color;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	t_player		player;
	t_raycast		rc;
	t_texture		textures[4];
}					 t_data;

	// map_x et map_y :
	//	 La position du joueur en termes de case (cellule) sur la carte de jeu. Par exemple, si le joueur est dans la case (2, 3) de la grille.

	// side_dist_x et side_dist_y :
	//	 Les distances entre la position du joueur et le premier bord (ligne) vertical ou horizontal qu'un rayon va toucher.

	// delta_dist_x et delta_dist_y :
	//	 La distance que le rayon parcourt entre chaque ligne verticale (delta_dist_x) et chaque ligne horizontale (delta_dist_y) de la grille.

	// hit :
	//	 Un indicateur qui devient 1 lorsque le rayon touche un mur.

	// side :
	//	 Indique si le mur touché est vertical (0) ou horizontal (1).

	// camera_x :
	//	 La position horizontale du rayon dans le plan de la caméra, utilisée pour calculer la direction du rayon.

	// ray_dir_x et ray_dir_y :
	//	 La direction du rayon en termes de coordonnées x et y. Par exemple, un rayon allant vers le nord-est aura des ray_dir_x et ray_dir_y positifs ou négatifs.

	// x et y :
	//	 Les coordonnées en pixels sur l'écran pour dessiner les murs.

	// tex_num :
	//	 Le numéro de la texture à utiliser pour le mur touché.

	// tex_x :

	// La position horizontale dans la texture du mur pour un rayon donné.

	// draw_end :

	// La position y sur l'écran où le mur cesse d'être dessiné.

	// line_height :

	// La hauteur du mur en pixels à dessiner sur l'écran.

	// draw_start :

	// La position y sur l'écran où le mur commence à être dessiné.

	// wall_x :

	// La position exacte où le rayon touche le mur, en termes de coordonnées x dans le mur.

	// perp_wall_dist :

	// La distance perpendiculaire entre le joueur et le mur touché par le rayon, utilisée pour corriger l'effet "fisheye".

void raycasting(t_data *data, t_player *player);
