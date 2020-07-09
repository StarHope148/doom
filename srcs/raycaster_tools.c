/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/09 06:03:04 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	ft_darken_color(unsigned int color, double coeff)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	// FF 00 00 00
	// 00 FF 00 00
	color >>= 8;
	b = (unsigned char)color * coeff;
	color >>= 8;
	g = (unsigned char)color * coeff;
	color >>= 8;
	r = (unsigned char)color * coeff;
	return (ft_rgba_to_uint32(r, g, b, 0));
}

void			ft_fix_fisheye_distorsion(t_env *doom)
{
	doom->raycast.distance_towall *= cos(doom->cam.angle -
											doom->raycast.ray_angle);
}

void			ft_set_ceiling_floor(t_env *doom)
{
	doom->ceiling = (double)(doom->h * 0.5) - (double)doom->h /
					doom->raycast.distance_towall * WALL_SIZE;
	doom->floor = doom->h - doom->ceiling;
	doom->ceiling -= (doom->map.alt[doom->raycast.test_y]
			[doom->raycast.test_x]) / doom->raycast.distance_towall;
	doom->ceiling += doom->cam.angle_z;
	doom->floor += doom->cam.angle_z;
}

void	ft_draw_ceiling(t_env *doom)
{
	doom->screen_pixels[doom->raycast.y_render *
		WIDTH + doom->raycast.x_render] = DODGER_BLUE;
}

void	ft_draw_wall(t_env *doom)
{
	if (doom->map.data
				[(int)doom->raycast.test_y][(int)doom->raycast.test_x] == 'D')
		ft_apply_textured_wall(doom);
	else if (doom->wall == TEXTURED)
		ft_apply_textured_wall(doom);
	else if (doom->wall == COLOR_ORIENTED)
		ft_apply_color_oriented_wall(doom);
	else if (doom->wall == SHADED)
		ft_apply_shaded_wall(doom);
	else
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = WHITE;
}

void	ft_draw_floor(t_env *doom)
{
	//doom->screen_pixels[doom->raycast.y_render * WIDTH +
	//	doom->raycast.x_render] = ft_rgba_to_uint32(0,
	//											255 *
	//											((doom->raycast.y_render -
	//											doom->h * 0.5) /
	//											doom->h),
	//											0,
	//											0);
	if (doom->wall == NON_TEXTURED || doom->wall == SHADED)
		doom->screen_pixels[doom->raycast.y_render * WIDTH +
			doom->raycast.x_render] = OLIVE;
	else
	{
		ft_setup_view(doom);
		doom->calc_floor.floorX = doom->cam.pos_x + doom->calc_floor.rowDistance *
			doom->raycast.eye_x;
		doom->calc_floor.floorY = doom->cam.pos_y + doom->calc_floor.rowDistance *
			doom->raycast.eye_y;
		doom->calc_floor.text_x = (int)(doom->surface_floor->w *
			(doom->calc_floor.floorX -
				(int)(doom->calc_floor.floorX))) & (doom->surface_floor->w - 1);
		doom->calc_floor.text_y = (int)(doom->surface_floor->h *
			(doom->calc_floor.floorY -
				(int)(doom->calc_floor.floorY))) & (doom->surface_floor->h - 1);
		doom->calc_floor.floorX += doom->calc_floor.floorStepX;
		doom->calc_floor.floorY += doom->calc_floor.floorStepY;
		doom->screen_pixels[doom->raycast.y_render * WIDTH + doom->raycast.x_render] =
			doom->pixels_floor[doom->surface_floor->w *
				doom->calc_floor.text_y + doom->calc_floor.text_x];
	}
}
