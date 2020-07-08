/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:23:06 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../SDL2-2.0.12/include/SDL.h"
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <sys/stat.h>
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
	char			**data;
	int				**bright;
	int				**alt;
}				t_map;

typedef struct	s_camera
{
	double			pos_x;
	double			pos_y;
	double			pos_z;
	double			angle;
	int				angle_z;
	double			fov;
	double			fov_ratio;
}				t_camera;

typedef struct	s_movements
{
	size_t			strafe_left;
	size_t			strafe_right;
	size_t			forward;
	size_t			backward;
	size_t			rotate_left;
	size_t			rotate_right;
	size_t			rotate_up;
	size_t			rotate_down;
	size_t			running;
	size_t			crouching;
	double			movespeed;
}				t_movements;

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

typedef	struct	s_ray
{
	int				stepx;
	int				stepy;
	int				side;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
}				t_ray;

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

typedef struct	s_calc_floor
{
	int				horizon;
	double			rowDistance;
	double			floorStepX;
	double			floorStepY;
	double			floorX;
	double			floorY;
	int				text_x;
	int				text_y;
}				t_calc_floor;

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

typedef struct	s_text
{
	TTF_Font		*font;
	SDL_Surface		*welcome1;
	SDL_Surface		*welcome2;
	SDL_Color		black;
}				t_text;

typedef struct	s_fps
{
	SDL_Surface		*s;
	clock_t			time_fps;
	clock_t			time_tmp;
	unsigned int	frames;
}				t_fps;

/* a t_door is malloc-ed when a door is opened */
typedef struct	s_door
{
	int				x;
	int				y;
	int				start_alt;
	double			speed;
	double			start_time;
	struct s_door	*next;
}				t_door;

typedef struct	s_xpm
{
	char			*name;
	int				w;
	int				h;
	int				clrmax;
	int				nchar;
	int				fileline;
	int				*pixels;
	struct s_xpm	*next;
}				t_xpm;

typedef struct	s_env
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Event		event;
	t_map			map;
	t_camera		cam;
	t_movements		moves;
	t_text			txt;
	t_door			*door;
	t_xpm			*xpm;
	Uint32			*screen_pixels;
	SDL_Surface		*surface_wall_north;
	Uint32			*pixels_wall_north;
	SDL_Surface		*surface_wall_south;
	Uint32			*pixels_wall_south;
	SDL_Surface		*surface_wall_east;
	Uint32			*pixels_wall_east;
	SDL_Surface		*surface_wall_west;
	Uint32			*pixels_wall_west;
	SDL_Surface		*surface_floor;
	Uint32			*pixels_floor;
	t_raycast		raycast;
	t_calc			calc;
	t_calc_floor	calc_floor;
	t_minimap		minimap;
	Mix_Music		*music;
	t_ray			ray;
	char			orientation;
	char			wall;
	int				pitch;
	int				ceiling;
	int				floor;
	unsigned int	tmp_x;
	unsigned int	tmp_y;
	int				block;
	int				h;
	t_fps			fps;
	double			music_puls;
	unsigned int	count_puls;
	clock_t			time0;
	int				no_funky;
}				t_env;

void			ft_doom(char *mapfile);
void			ft_sdl(t_env *doom);
void			ft_exit(t_env *doom, int exit_type, char *message);
void			ft_print(t_env *doom);
void			ft_initialize(t_env *doom, char *mapfile);
void			ft_init_map(t_env *doom, char *mapfile);
void			ft_movement(t_env *doom);
void			ft_stop_movement(t_env *doom);
void			ft_settings(t_env *doom);
void			ft_refresh_new_pos(t_env *doom);
void			ft_error(t_map *m, int code, char *line);

/* map_checker.c */
int				ft_check_line(t_map *m);
int				ft_check_borders(char *line);
void			ft_count_lines_columns(t_map *m, char *mapfile, int fd);
void			ft_norme(int code);
void			ft_raycaster(t_env *doom);
void			ft_calc_sampling_x(t_env *doom);
void			ft_west_face(t_env *doom);
void			ft_north_face(t_env *doom);
void			ft_south_face(t_env *doom);
void			ft_east_face(t_env *doom);
void			ft_fix_fisheye_distorsion(t_env *doom);
void			ft_set_ceiling_floor(t_env *doom);
void			ft_draw_ceiling(t_env *doom);
void			ft_draw_wall(t_env *doom);
void			ft_apply_north_texture(t_env *doom);
void			ft_apply_south_texture(t_env *doom);
void			ft_apply_east_texture(t_env *doom);
void			ft_apply_west_texture(t_env *doom);
void			ft_draw_floor(t_env *doom);
void			ft_draw_minimap(t_env *doom);
void			ft_set_sdl_minimap_colors(t_env *doom);
void			ft_apply_textured_wall(t_env *doom);
void			ft_apply_color_oriented_wall(t_env *doom);
void			ft_apply_shaded_wall(t_env *doom);
void			ft_free_map(t_map *m);
void			ft_free_door(t_door *list);
void			ft_free_surface_image(t_env *doom);
void			ft_destroy_texture_renderer_window(t_env *doom);
unsigned int	ft_darken_color(unsigned int color, double coeff);
void			ft_calc_next_intersection(t_env *doom);
void			ft_setup_view(t_env *doom);

/* KEYS */
void			ft_key_pressed(t_env *doom);
void			ft_key_released(t_env *doom);

/* time fps etc */
double			get_time(t_env *doom);
void			ft_funky_textures(t_env *doom);
void			ft_draw_fps(t_env *doom);
void			draw_text(t_env *doom, unsigned int pos, SDL_Surface *text);
void			draw_centered_text(t_env *doom, SDL_Surface *text);

/* open_door.c */
void			resolve_door(t_env *doom);
void			animation_opening_door(t_env *doom);

void			save_in_file(t_env *doom);

t_xpm			*get_xpm(t_env *doom, char *xpm_file);
void			ft_free_one_xpm(t_xpm *xpm);
void			ft_free_xpm(t_xpm *list);
#endif
