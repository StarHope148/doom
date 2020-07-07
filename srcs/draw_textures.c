/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:34:50 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:25:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_apply_north_texture(t_env *doom)
{
	doom->tmp_x = doom->calc.sample_x * doom->surface_wall_north->h;
	doom->tmp_y = doom->calc.sample_y * doom->surface_wall_north->w;
	doom->screen_pixels[doom->raycast.y_render * WIDTH +
		doom->raycast.x_render] = doom->pixels_wall_north[doom->tmp_y *
								doom->surface_wall_north->w + doom->tmp_x];
}

void	ft_apply_south_texture(t_env *doom)
{
	doom->tmp_x = doom->calc.sample_x * doom->surface_wall_south->h;
	doom->tmp_y = doom->calc.sample_y * doom->surface_wall_south->w;
	doom->screen_pixels[doom->raycast.y_render * WIDTH +
		doom->raycast.x_render] = doom->pixels_wall_south[doom->tmp_y *
								doom->surface_wall_south->w + doom->tmp_x];
}

void	ft_apply_east_texture(t_env *doom)
{
	doom->tmp_x = doom->calc.sample_x * doom->surface_wall_east->h;
	doom->tmp_y = doom->calc.sample_y * doom->surface_wall_east->w;
	doom->screen_pixels[doom->raycast.y_render * WIDTH +
		doom->raycast.x_render] = doom->pixels_wall_east[doom->tmp_y *
								doom->surface_wall_east->w + doom->tmp_x];
}

void	ft_apply_west_texture(t_env *doom)
{
	doom->tmp_x = doom->calc.sample_x * doom->surface_wall_west->h;
	doom->tmp_y = doom->calc.sample_y * doom->surface_wall_west->w;
	doom->screen_pixels[doom->raycast.y_render * WIDTH +
		doom->raycast.x_render] = doom->pixels_wall_west[doom->tmp_y *
								doom->surface_wall_west->w + doom->tmp_x];
}
