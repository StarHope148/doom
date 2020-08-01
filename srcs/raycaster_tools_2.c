/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:57:43 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 16:27:32 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_set_ceiling_floor(t_thread_env *e)
{
	double	scale;

	scale = e->cam.proj_dist * WALL_SIZE / e->rc.distance_towall;
	e->rc.floor = (e->cam.proj_dist / e->rc.distance_towall) * (e->cam.pos_z)
		+ e->cam.angle_z;
	e->rc.ceiling = e->rc.floor - scale;
	e->rc.ceiling -= ((e->map.alt[e->rc.test_y * e->map.nbcol + e->rc.test_x]
		- 1) / e->rc.distance_towall) * WALL_SIZE;
}
