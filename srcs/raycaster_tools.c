/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/16 14:19:55 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_set_ceiling_floor(t_thread_env *e)
{
	e->rc.ceiling = (H * 0.5) - H /
					e->rc.distance_towall * WALL_SIZE;
	e->rc.floor = H - e->rc.ceiling;
	e->rc.ceiling -= (e->map.alt[e->rc.test_y]
			[e->rc.test_x]) / e->rc.distance_towall;
	e->rc.ceiling += e->cam.angle_z;
	e->rc.floor += e->cam.angle_z;
}

void			ft_draw_ceiling(t_thread_env *e)
{
	e->screen_pixels[e->rc.y_ *
		W + e->rc.x_] = DODGER_BLUE;
}

void			ft_draw_wall(t_thread_env *e)
{
	if (e->map.data[e->rc.test_y][e->rc.test_x] == 'D' || e->wall == TEXTURED)
		ft_apply_textured_wall(e);
	else if (e->wall == COLOR_ORIENTED)
		ft_apply_color_oriented_wall(e);
	else if (e->wall == SHADED)
		ft_apply_shaded_wall(e);
	else
		e->screen_pixels[e->rc.y_ *
			W + e->rc.x_] = WHITE;
}

void			ft_setup_view(t_thread_env *e)
{
	e->rc.horizon = (e->rc.y_ - H / 2) - e->cam.angle_z;
	e->rc.rowdistance = e->cam.pos_z / e->rc.horizon;
	e->rc.rowdistance /= cos(e->cam.angle -
		e->rc.ray_angle);
	e->rc.floorstepx = e->rc.rowdistance / W;
	e->rc.floorstepy = e->rc.rowdistance / W;
}

void			ft_draw_floor(t_thread_env *e)
{
	if (e->wall == NON_TEXTURED || e->wall == SHADED)
	{
		e->screen_pixels[e->rc.y_ * W + e->rc.x_] = OLIVE;
		return ;
	}
	ft_setup_view(e);
	e->rc.floorx = e->cam.pos_x + e->rc.rowdistance *
		e->rc.eye_x;
	e->rc.floory = e->cam.pos_y + e->rc.rowdistance *
		e->rc.eye_y;
	e->rc.text_x = (int)(e->xpm[FLOOR].w *
		(e->rc.floorx -
			(int)(e->rc.floorx))) & (e->xpm[FLOOR].w - 1);
	e->rc.text_y = (int)(e->xpm[FLOOR].h *
		(e->rc.floory -
			(int)(e->rc.floory))) & (e->xpm[FLOOR].h - 1);
	e->rc.floorx += e->rc.floorstepx;
	e->rc.floory += e->rc.floorstepy;
	e->screen_pixels[e->rc.y_ * W + e->rc.x_] =
		e->xpm[FLOOR].pixels[e->xpm[FLOOR].w * e->rc.text_y + e->rc.text_x];
}
