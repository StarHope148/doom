/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 21:02:41 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void			ft_fix_fisheye_distorsion(t_env *wolf)
{
	wolf->raycast.distance_towall *= cos(wolf->cam.angle -
											wolf->raycast.ray_angle);
}

void			ft_set_ceiling_floor(t_env *wolf)
{
	wolf->ceiling = (double)(wolf->h * 0.5) - (double)wolf->h /
					wolf->raycast.distance_towall * WALL_SIZE;
	wolf->floor = wolf->h - wolf->ceiling;
	wolf->ceiling -= (wolf->map.altitude[wolf->raycast.test_y]
			[wolf->raycast.test_x]) * 100 / wolf->raycast.distance_towall;
	wolf->ceiling += wolf->cam.angle_z;
	wolf->floor += wolf->cam.angle_z;
}

void	ft_draw_ceiling(t_env *wolf)
{
	wolf->screen_pixels[wolf->raycast.y_render *
		WIDTH + wolf->raycast.x_render] = DODGER_BLUE;
}

void	ft_draw_wall(t_env *wolf)
{
	if (wolf->wall == TEXTURED)
		ft_apply_textured_wall(wolf);
	else if (wolf->wall == COLOR_ORIENTED)
		ft_apply_color_oriented_wall(wolf);
	else if (wolf->wall == SHADED)
		ft_apply_shaded_wall(wolf);
	else
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = WHITE;
}

void	ft_draw_floor(t_env *wolf)
{
	//wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
	//	wolf->raycast.x_render] = ft_rgba_to_uint32(0,
	//											255 *
	//											((wolf->raycast.y_render -
	//											wolf->h * 0.5) /
	//											wolf->h),
	//											0,
	//											0);
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = OLIVE;
}
