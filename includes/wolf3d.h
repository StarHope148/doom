/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/28 21:43:54 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../SDL2-2.0.12/include/SDL.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "defines.h"
# include "colors.h"

typedef enum	e_cardinal_point
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_cardinal_point;

typedef enum	e_switch_texture_mod
{
	NON_TEXTURED,
	SHADED,
	COLOR_ORIENTED,
	TEXTURED
}				t_switch_texture_mod;

typedef struct	s_map
{
	int				nbl;
	int				nbcol;
	size_t			cur_line;
	char			**map;
}				t_map;

typedef struct	s_camera
{
	double			pos_x;
	double			pos_y;
	double			angle;
	double			fov;
	size_t			strafe_left;
	size_t			strafe_right;
	size_t			forward;
	size_t			backward;
	size_t			rotate_left;
	size_t			rotate_right;
}				t_camera;

typedef struct	s_raycast
{
	int				x_render;
	int				y_render;
	double			eye_x;
	double			eye_y;
	int				test_x;
	int				test_y;
	double			ray_angle;
	double			distance_towall;
	int				hit_wall;
	double			shading;
}				t_raycast;

typedef struct	s_calc
{
	double			sample_x;
	double			sample_y;
	double			block_mid_x;
	double			block_mid_y;
	double			test_point_x;
	double			test_point_y;
	double			test_angle;
}				t_calc;

typedef struct	s_minimap
{
	int				i;
	int				j;
	int				x;
	int				y;
	int				def_x;
	int				def_y;
	char			done;
}				t_minimap;

typedef struct	s_env
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Event		event;
	t_map			mapdata;
	t_camera		cam;
	Uint32			*screen_pixels;
	SDL_Surface		*surface_wall_north;
	Uint32			*pixels_wall_north;
	SDL_Surface		*surface_wall_south;
	Uint32			*pixels_wall_south;
	SDL_Surface		*surface_wall_east;
	Uint32			*pixels_wall_east;
	SDL_Surface		*surface_wall_west;
	Uint32			*pixels_wall_west;
	t_raycast		raycast;
	t_calc			calc;
	t_minimap		minimap;
	char			orientation;
	double			precision;
	char			switch_textures;
	int				pitch;
	int				ceiling;
	int				floor;
	unsigned int	tmp_x;
	unsigned int	tmp_y;
	int				block;
}				t_env;

void			ft_wolf3d(char *mapfile);
void			ft_sdl(t_env *wolf);
void			ft_key_hook(t_env *wolf);
void			ft_exit(t_env *wolf, int exit_type, char *message);
void			ft_print(t_env *wolf);
void			ft_initialize(t_env *wolf, char *mapfile);
void			ft_init_map(t_env *wolf, char *mapfile);
void			ft_movement(t_env *wolf);
void			ft_stop_movement(t_env *wolf);
void			ft_settings(t_env *wolf);
void			ft_refresh_new_pos(t_env *wolf);
void			ft_error(int code, char *line);
int				ft_check_line(char *line);
int				ft_check_borders(char *line);
void			ft_norme(int code);
void			ft_raycaster(t_env *wolf);
void			ft_calc_sampling_x(t_env *wolf);
void			ft_west_face(t_env *wolf);
void			ft_north_face(t_env *wolf);
void			ft_south_face(t_env *wolf);
void			ft_east_face(t_env *wolf);
void			ft_fix_fisheye_distorsion(t_env *wolf);
void			ft_set_ceiling_floor(t_env *wolf);
void			ft_draw_ceiling(t_env *wolf);
void			ft_draw_wall(t_env *wolf);
void			ft_apply_north_texture(t_env *wolf);
void			ft_apply_south_texture(t_env *wolf);
void			ft_apply_east_texture(t_env *wolf);
void			ft_apply_west_texture(t_env *wolf);
void			ft_draw_floor(t_env *wolf);
void			ft_draw_minimap(t_env *wolf);
void			ft_set_sdl_minimap_colors(t_env *wolf);
void			ft_apply_textured_wall(t_env *wolf);
void			ft_apply_color_oriented_wall(t_env *wolf);
void			ft_apply_shaded_wall(t_env *wolf);
void			ft_free_map(t_env *wolf);
void			ft_free_surface_image(t_env *wolf);
void			ft_destroy_texture_renderer_window(t_env *wolf);

#endif
