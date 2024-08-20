/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/20 18:17:10 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define M_PI 3.14159265358979323846
# define SUCCESS 0
# define FAILURE -1

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	q;
	int	e;
}		t_keys;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	bool	check;
}	t_color;

typedef struct s_double
{
	bool	no;
	bool	so;
}	t_double;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		loaded;
}			t_texture;

typedef struct s_minimap
{
	int		pos_x;
	int		pos_y;
	int		size_x;
	int		size_y;
	int		size;
	int		player_x;
	int		player_y;
	int		x;
	int		y;
	int		i;
	int		j;
}			t_minimap;

typedef struct s_raycast
{
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				hit;
	int				side;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				x;
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
}					t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				ok_mlx;
	int				ok_img;
	int				ok_win;
	int				ok_map;
	char			**map;
	char			**m;
	int				fd;
	int				bits_per_pixel;
	int				floor_color;
	int				sky_color;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				nb_param;
	int				size_x;
	int				size_y;
	t_keys			keys;
	t_color			sky;
	t_color			floor;
	t_player		player;
	t_raycast		rc;
	t_texture		textures[4];
}					t_data;

int				ft_perror(char *error);
void			init_ok(t_data *data);
void			start_and_dir(t_data *data, t_player *player);
void			send_ray_helper(t_data *data, t_player *player);
void			hit_checker(t_data *data);
void			col_wall_sizer(t_data *data, t_player *player);
void			wall_orientation(t_data *data);
void			raycasting(t_data *data, t_player *player);
void			wall_drawer(t_data *data, t_player *player);
int				load_textures(t_data *data, t_texture *texture);
int				data_init(t_data *data);
void			player_init(t_player *player);
void			choose_ew(t_player *player);
void			choose_ns(t_player *player);
void			reverse_line(char *line);
void			reverse_map(char **map);
unsigned int	color_converter(t_color color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_floor_and_sky(t_data *data, int x, int draw_start, \
				int draw_end);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				close_window(t_data *data);
int				check_wall(t_data *data, double x, double y);
int				is_wall(t_data *data, double x, double y);
void			choose_ns(t_player *player);
void			choose_ew(t_player *player);
void			player_init(t_player *player);
void			rotate_right(t_data *data);
void			rotate_left(t_data *data);
void			move_back(t_data *data);
void			fordward(t_data *data);
char			*ft_strjoin_cub(char *s1, char *s2);
void			move_right(t_data *data);
void			move_left(t_data *data);
void			mini_mapper(t_data *data);
int				ft_check_arg(t_data *data, char *arg_map);
int				ft_strlen_cub(char *s, int choice);
char			*ft_strdup_cub(char *str, int choice);
void			ft_strcpy(char *dst, const char *src);
int				ft_get_texture(t_data *data);
int				ft_get_no(t_data *data, char *gnl);
int				ft_get_so(t_data *data, char *gnl);
int				ft_get_we(t_data *data, char *gnl);
int				ft_get_ea(t_data *data, char *gnl);
int				ft_fill_color_c(t_data *data, char *gnl, int i);
int				ft_fill_color_f(t_data *data, char *gnl, int i);
int				ft_get_color_c(t_data *data, char *gnl);
int				ft_get_color_f(t_data *data, char *gnl);
int				ft_get_map(t_data *data);
int				ft_is_map_enclosed_wall(t_data *data);
int				ft_cpy_map(t_data *data);
void			raycasting(t_data *data, t_player *player);
void			ft_free_data(int ac, t_data data);
void			raycasting(t_data *data, t_player *player);
int				ft_check_arg(t_data *data, char *arg_map);
int				ft_strlen_cub(char *s, int choice);
int				ft_get_texture(t_data *data);
char			*ft_strdup_cub(char *str, int choice);
int				ft_fill_color_c(t_data *data, char *gnl, int i);
int				ft_fill_color_f(t_data *data, char *gnl, int i);
int				ft_get_color_c(t_data *data, char *gnl);
int				ft_get_color_f(t_data *data, char *gnl);
int				ft_get_no(t_data *data, char *gnl);
int				ft_get_so(t_data *data, char *gnl);
int				ft_get_we(t_data *data, char *gnl);
int				ft_get_ea(t_data *data, char *gnl);
int				is_wall(t_data *data, double x, double y);
void			ft_free_data(int ac, t_data data);

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
#endif