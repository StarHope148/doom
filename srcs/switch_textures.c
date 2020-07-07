/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:15:33 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:25:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_apply_textured_wall(t_env *doom)
{
	doom->calc.sample_y = ((double)doom->raycast.y_render -
								(double)doom->ceiling) /
								((double)doom->floor - (double)doom->ceiling);
	doom->calc.sample_y = fabs(doom->calc.sample_y - (int)doom->calc.sample_y);
	if (doom->orientation == NORTH)
		ft_apply_north_texture(doom);
	else if (doom->orientation == SOUTH)
		ft_apply_south_texture(doom);
	else if (doom->orientation == EAST)
		ft_apply_east_texture(doom);
	else if (doom->orientation == WEST)
		ft_apply_west_texture(doom);
}

void	ft_apply_color_oriented_wall(t_env *doom)
{
	if (doom->orientation == NORTH)
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = BLUE;
	else if (doom->orientation == SOUTH)
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = RED;
	else if (doom->orientation == EAST)
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = YELLOW;
	else if (doom->orientation == WEST)
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = ORANGE;
}

void	ft_apply_shaded_wall(t_env *doom)
{
	doom->raycast.shading = 1 - doom->raycast.distance_towall / SHADING_DEPTH;
	if (doom->raycast.shading < 0.1)
		doom->raycast.shading = 0.1;
	doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] =
				ft_rgba_to_uint32(255 * doom->raycast.shading,
				255 * doom->raycast.shading, 255 * doom->raycast.shading, 0);
}
