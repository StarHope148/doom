/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_type2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 22:11:44 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 22:11:57 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_draw_projectile(t_env *e, t_object *tmp)
{
	tmp->data.h_ = 0.2 * H / tmp->data.dist * e->cam.proj_dist / PROJ_DIST;
	tmp->data.w_ = 0.2 * H / tmp->data.dist * e->xpm[PROJECTILE_XPM].w /
		e->xpm[PROJECTILE_XPM].h / e->cam.fov;
	tmp->data.y_ = (e->cam.proj_dist / tmp->data.dist) * (e->cam.pos_z) +
		e->cam.angle_z - tmp->data.h_ * 4;
	tmp->data.x_ = W - W * tmp->data.angle / e->cam.fov - tmp->data.w_ / 2;
	tmp->data.delta_x_end = tmp->data.w_;
	tmp->data.delta_x_start = 0;
}
