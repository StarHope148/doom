/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:49:51 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/28 15:15:03 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_draw_objects(t_thread_env *e)
{
	e->obj.angle = atan2(cos(e->cam.angle - e->cam.fov / 2.0),
						sin(e->cam.angle - e->cam.fov / 2.0))
									- atan2(e->obj.vect_y, e->obj.vect_x);
	e->obj.angle += e->obj.angle < -PI ? 2 * PI : 0;
	e->obj.angle -= e->obj.angle > PI ? 2 * PI : 0;
	e->obj.y_ = H / 2 - H / e->obj.dist;
	e->obj.h_ = 2 * H / (e->obj.dist);
	e->obj.w_ = e->obj.h_ * e->xpm[BARREL_XPM].w / e->xpm[BARREL_XPM].h;
	e->obj.x_ = W - W * e->obj.angle / e->cam.fov - e->obj.w_ / 2;
	e->obj.delta_x_end = e->obj.w_ + e->obj.x_ > e->x_end ?
										e->x_end - e->obj.x_ : e->obj.w_;
	e->obj.delta_x_start = e->obj.x_ < e->x_start ? e->x_start - e->obj.x_ : 0;
}

static void		modify_screen_pixels(t_thread_env *e)
{
	t_point	delta;
	t_point	sample;
	t_point	pix;
	Uint32	color;

	init_draw_objects(e);
	delta.y = -1;
	while (++delta.y < e->obj.h_)
	{
		delta.x = e->obj.delta_x_start - 1;
		while (++delta.x < e->obj.delta_x_end)
		{
			sample.y = delta.y * e->xpm[BARREL_XPM].h / e->obj.h_;
			sample.x = delta.x * e->xpm[BARREL_XPM].w / e->obj.w_;
			color = e->xpm[BARREL_XPM].pixels
						[sample.y * e->xpm[BARREL_XPM].w + sample.x];
			if (color != MAGENTA)
			{
				pix.y = e->obj.y_ + delta.y;
				pix.x = e->obj.x_ + delta.x;
				e->screen_pixels[pix.y * W + pix.x] = color;
			}
		}
	}
}

static void		set_obj_dist(t_thread_env *e)
{
	e->obj.vect_x = e->obj.pos.x - e->cam.pos_x;
	e->obj.vect_y = e->obj.pos.y - e->cam.pos_y;
	e->obj.dist = sqrt(e->obj.vect_x * e->obj.vect_x
					+ e->obj.vect_y * e->obj.vect_y);
		
}

void			ft_draw_objects(t_thread_env *e)
{
	while (e->object_found > 0)
	{
		e->object_found = 1;
		set_obj_dist(e);
		if (e->obj.dist > 2)
			modify_screen_pixels(e);
		//printf("MiddleOfObject = %f\tObjectAngle = %f\te->obj.w_ = %f\tdistancefromplayer = %f\n", fMiddleOfObject, fObjectAngle, e->obj.w_, e->obj.dist);
		else
			printf("distance too low, did not draw object\n");
		e->obj.type = 0;
		e->object_found--;
		//printf("TEST\n");
	}
}
