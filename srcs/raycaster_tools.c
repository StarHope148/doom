/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/02 17:47:09 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_fix_fisheye_distorsion(t_env *wolf)
{
	wolf->raycast.distance_towall *= cos(wolf->cam.angle -
											wolf->raycast.ray_angle);
}

void	ft_set_ceiling_floor(t_env *wolf)
{
	wolf->ceiling = (double)(wolf->h / 2) - (double)wolf->h /
					wolf->raycast.distance_towall * WALL_SIZE;
	wolf->floor = wolf->h - wolf->ceiling;
}

void	ft_draw_ceiling(t_env *wolf)
{
	wolf->screen_pixels[wolf->raycast.y_render *
						WIDTH + wolf->raycast.x_render] = DODGER_BLUE;
}

void	ft_draw_wall(t_env *wolf)
{
	if (wolf->switch_textures == TEXTURED)
		ft_apply_textured_wall(wolf);
	else if (wolf->switch_textures == COLOR_ORIENTED)
		ft_apply_color_oriented_wall(wolf);
	else if (wolf->switch_textures == SHADED)
		ft_apply_shaded_wall(wolf);
	else
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = WHITE;
}

void	ft_draw_floor(t_env *wolf)
{
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = ft_rgba_to_uint32(0,
												255 *
												((wolf->raycast.y_render -
												wolf->h * 0.5) /
												wolf->h),
												0,
												0);
}
