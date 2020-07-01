/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:15:33 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 20:09:42 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_apply_textured_wall(t_env *wolf)
{
	wolf->calc.sample_y = ((double)wolf->raycast.y_render -
								(double)wolf->ceiling) /
								((double)wolf->floor - (double)wolf->ceiling);
	wolf->calc.sample_y = fabs(wolf->calc.sample_y - (int)wolf->calc.sample_y);
	if (wolf->orientation == NORTH)
		ft_apply_north_texture(wolf);
	else if (wolf->orientation == SOUTH)
		ft_apply_south_texture(wolf);
	else if (wolf->orientation == EAST)
		ft_apply_east_texture(wolf);
	else if (wolf->orientation == WEST)
		ft_apply_west_texture(wolf);
}

void	ft_apply_color_oriented_wall(t_env *wolf)
{
	if (wolf->orientation == NORTH)
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = BLUE;
	else if (wolf->orientation == SOUTH)
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = RED;
	else if (wolf->orientation == EAST)
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = YELLOW;
	else if (wolf->orientation == WEST)
		wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] = ORANGE;
}

void	ft_apply_shaded_wall(t_env *wolf)
{
	wolf->raycast.shading = 1 - wolf->raycast.distance_towall / SHADING_DEPTH;
	if (wolf->raycast.shading < 0.1)
		wolf->raycast.shading = 0.1;
	wolf->screen_pixels[wolf->raycast.y_render *
			WIDTH + wolf->raycast.x_render] =
				ft_rgba_to_uint32(255 * wolf->raycast.shading,
				255 * wolf->raycast.shading, 255 * wolf->raycast.shading, 0);
}
