/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_transparent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:32:53 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 15:34:01 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_draw_transparent(t_thread_env *e)
{
	e->rc.y_ = 0;
	e->rc.orientation = GRID_XPM;
	while (e->rc.y_ < H)
	{
		if (e->rc.y_ >= e->rc.ceiling && e->rc.y_ <= e->rc.floor)
			ft_draw_wall(e);
		e->rc.y_++;
	}
}

void	ft_draw_transparent_textures(t_thread_env *e)
{
	while (e->transparent_found > 0)
	{
		e->transparent_found = 1;
		ft_calc_next_intersection_transparent(e);
		ft_calc_sampling_x(e);
		ft_fix_fisheye_distorsion(e);
		ft_set_ceiling_floor(e);
		ft_draw_transparent(e);
		e->transparent_found--;
	}
}
