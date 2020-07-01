/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:34:50 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 20:53:48 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_apply_north_texture(t_env *wolf)
{
	wolf->tmp_x = wolf->calc.sample_x * wolf->surface_wall_north->h;
	wolf->tmp_y = wolf->calc.sample_y * wolf->surface_wall_north->w;
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = wolf->pixels_wall_north[wolf->tmp_y *
								wolf->surface_wall_north->w + wolf->tmp_x];
}

void	ft_apply_south_texture(t_env *wolf)
{
	wolf->tmp_x = wolf->calc.sample_x * wolf->surface_wall_south->h;
	wolf->tmp_y = wolf->calc.sample_y * wolf->surface_wall_south->w;
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = wolf->pixels_wall_south[wolf->tmp_y *
								wolf->surface_wall_south->w + wolf->tmp_x];
}

void	ft_apply_east_texture(t_env *wolf)
{
	wolf->tmp_x = wolf->calc.sample_x * wolf->surface_wall_east->h;
	wolf->tmp_y = wolf->calc.sample_y * wolf->surface_wall_east->w;
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = wolf->pixels_wall_east[wolf->tmp_y *
								wolf->surface_wall_east->w + wolf->tmp_x];
}

void	ft_apply_west_texture(t_env *wolf)
{
	wolf->tmp_x = wolf->calc.sample_x * wolf->surface_wall_west->h;
	wolf->tmp_y = wolf->calc.sample_y * wolf->surface_wall_west->w;
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
		wolf->raycast.x_render] = wolf->pixels_wall_west[wolf->tmp_y *
								wolf->surface_wall_west->w + wolf->tmp_x];
}
