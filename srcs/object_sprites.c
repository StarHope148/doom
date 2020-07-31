/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:49:51 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 00:24:38 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		modify_screen_pixels(t_env *e, t_object *tmp)
{
	t_point			delta;
	t_point			sample;
	unsigned int	y_;
	unsigned int	x_;
	t_xpm			*x;

	x = &e->xpm[ft_choose_and_init_sprite(e, tmp)];
	if (!x || !x->pixels || x->w < 1 || x->h < 1)
		return ;
	delta.y = -1;
	while (++delta.y < tmp->data.h_)
	{
		delta.x = tmp->data.delta_x_start - 1;
		while (++delta.x < tmp->data.w_)
		{
			sample.y = delta.y * x->h / tmp->data.h_;
			sample.x = delta.x * x->w / tmp->data.w_;
			y_ = tmp->data.y_ + delta.y;
			x_ = tmp->data.x_ + delta.x;
			if (sample.y * x->w + sample.x < x->w * x->h &&
					x->pixels[sample.y * x->w + sample.x] != MAGENTA &&
					y_ * W + x_ < W * H && x_ < W &&
					tmp->data.dist < e->shared_data.depth_buf[x_])
				e->screen_pixels[y_ * W + x_] =
										x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		set_obj_dist(t_env *e, t_object *tmp)
{
	tmp->data.vect_x = tmp->data.pos.x - e->cam.pos_x;
	tmp->data.vect_y = tmp->data.pos.y - e->cam.pos_y;
	tmp->data.dist = sqrt(tmp->data.vect_x * tmp->data.vect_x
					+ tmp->data.vect_y * tmp->data.vect_y);
}

void		set_obj_angle(t_env *e, t_object *tmp)
{
	tmp->data.angle = atan2(cos(e->cam.angle - e->cam.fov / 2),
						sin(e->cam.angle - e->cam.fov / 2))
									- atan2(tmp->data.vect_y, tmp->data.vect_x);
	tmp->data.angle += tmp->data.angle < -PI ? 2 * PI : 0;
	tmp->data.angle -= tmp->data.angle > PI ? 2 * PI : 0;
	if (tmp->data.angle > 0 - 0.5 && tmp->data.angle < e->cam.fov + 0.5)
		tmp->data.in_fov = TRUE;
	else
		tmp->data.in_fov = FALSE;
}

void		ft_sort_list(t_env *e, t_object *tmp)
{
	int				done;
	t_object_data	tmp_data;

	done = FALSE;
	while (done == FALSE)
	{
		tmp = &e->obj;
		if (tmp->next == NULL)
			return ;
		while (tmp != NULL && tmp->next != NULL)
		{
			if (tmp->data.dist < tmp->next->data.dist)
			{
				tmp_data = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = tmp_data;
				done = FALSE;
			}
			else
				done = TRUE;
			tmp = tmp->next;
		}
	}
}

void		ft_draw_objects(t_env *e)
{
	t_object	*tmp;

	tmp = &e->obj;
	while (tmp != NULL)
	{
		set_obj_dist(e, tmp);
		tmp = tmp->next;
	}
	ft_sort_list(e, tmp);
	tmp = &e->obj;
	while (tmp != NULL)
	{
		set_obj_angle(e, tmp);
		if (tmp->data.dist > 0.5 && tmp->data.in_fov == TRUE)
			modify_screen_pixels(e, tmp);
		tmp = tmp->next;
	}
}
