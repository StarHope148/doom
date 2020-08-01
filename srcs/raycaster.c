/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:51:13 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 19:24:53 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_set_new_ray_angle(t_thread_env *e)
{
	e->rc.ray_angle = (e->cam.angle + e->cam.fov / 2.0) -
							((double)e->rc.x_ / (double)W) *
							e->cam.fov;
	e->rc.distance_towall = 0;
	e->rc.eye_x = sin(e->rc.ray_angle);
	e->rc.eye_y = cos(e->rc.ray_angle);
}

void	ft_apply_brightness(t_thread_env *e)
{
	int		shadowing;

	if (e->map.bright[(int)e->cam.pos_y * e->map.nbcol + (int)e->cam.pos_x]
																	!= 3)
	{
		shadowing = e->map.bright[(int)e->cam.pos_y
									* e->map.nbcol + (int)e->cam.pos_x];
		while (shadowing++ - 3)
		{
			e->screen_pixels[e->rc.y_ * W + e->rc.x_] >>= 1;
			e->screen_pixels[e->rc.y_ * W + e->rc.x_] &=
								0b01111111011111110111111101111111;
		}
	}
}

void	ft_draw_full_column(t_thread_env *e)
{
	e->rc.y_ = -1;
	while (++e->rc.y_ < H)
	{
		if (e->rc.y_ < e->rc.ceiling)
			ft_draw_ceiling(e);
		else if (e->rc.y_ >= e->rc.ceiling &&
				e->rc.y_ <= e->rc.floor)
			ft_draw_wall(e);
		else
			ft_draw_floor(e);
		ft_apply_brightness(e);
	}
}

void	ft_fix_fisheye_distorsion(t_thread_env *e)
{
	e->rc.distance_towall *= cos(e->cam.angle - e->rc.ray_angle);
}

void	ft_raycaster(t_thread_env *e)
{
	t_shared_data *shared_data;

	shared_data = (t_shared_data *)e->shared_data;
	e->rc.x_ = e->x_start - 1;
	while (++e->rc.x_ < e->x_end)
	{
		ft_set_new_ray_angle(e);
		ft_calc_next_intersection(e);
		ft_calc_sampling_x(e);
		ft_fix_fisheye_distorsion(e);
		ft_set_ceiling_floor(e);
		ft_draw_full_column(e);
		ft_draw_transparent_textures(e);
		pthread_mutex_lock(&shared_data->mutex);
		shared_data->depth_buf[e->rc.x_] = e->rc.distance_towall + 0.5;
		pthread_mutex_unlock(&shared_data->mutex);
	}
}
