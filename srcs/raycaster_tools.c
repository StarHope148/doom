/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/25 18:14:28 by jcanteau         ###   ########.fr       */
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
	wolf->ceiling = (double)(HEIGHT / 2) - (double)HEIGHT /
					wolf->raycast.distance_towall * WALL_SIZE;
	wolf->floor = HEIGHT - wolf->ceiling;
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
												HEIGHT * 0.5) /
												HEIGHT),
												0,
												0);
}
