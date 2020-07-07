/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:51:13 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 04:56:18 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_apply_brightness(t_env *wolf)
{
	if (wolf->map.bright[(int)wolf->cam.pos_y]
					[(int)wolf->cam.pos_x] != 100)
		wolf->screen_pixels[wolf->raycast.y_render *
		WIDTH + wolf->raycast.x_render] =
			ft_darken_color(wolf->screen_pixels[wolf->raycast.y_render *
				WIDTH + wolf->raycast.x_render],
					(double)wolf->map.bright[(int)wolf->cam.pos_y]
						[(int)wolf->cam.pos_x] /
							100);
}

/* 
void	ft_casting_ray(t_env *wolf)
{
	
	wolf->raycast.distance_towall += 0.1;
	wolf->raycast.test_x = (int)(wolf->cam.pos_x +
							wolf->raycast.eye_x *
							wolf->raycast.distance_towall);
	wolf->raycast.test_y = (int)(wolf->cam.pos_y +
							wolf->raycast.eye_y *
							wolf->raycast.distance_towall);
	if (wolf->raycast.test_x < 0 ||
			wolf->raycast.test_x >= wolf->map.nbcol ||
			wolf->raycast.test_y < 0 ||
			wolf->raycast.test_y >= wolf->map.nbl)
	{
		wolf->raycast.hit_wall = 1;
		wolf->raycast.distance_towall = MAX_DEPTH;
	}
	else if (wolf->map.data[wolf->raycast.test_y]
								[wolf->raycast.test_x] == WALL
		|| wolf->map.data[wolf->raycast.test_y]
								[wolf->raycast.test_x] == DOOR
		|| wolf->map.data[wolf->raycast.test_y]
								[wolf->raycast.test_x] == TRANSP) // a modifier
		wolf->raycast.hit_wall = 1;
}
*/

void	ft_set_new_ray_angle(t_env *wolf)
{
	wolf->raycast.ray_angle = (wolf->cam.angle + wolf->cam.fov / 2.0) -
							((double)wolf->raycast.x_render / (double)WIDTH) *
							wolf->cam.fov;
	wolf->raycast.distance_towall = 0;
	wolf->raycast.hit_wall = 0;
	wolf->raycast.shading = 1;
	wolf->raycast.eye_x = sin(wolf->raycast.ray_angle);
	wolf->raycast.eye_y = cos(wolf->raycast.ray_angle);
}

void	ft_raycaster(t_env *wolf)
{
	wolf->raycast.x_render = 0;
	while (wolf->raycast.x_render < WIDTH)
	{
		ft_set_new_ray_angle(wolf);
		//while (wolf->raycast.hit_wall == 0 &&
		//		wolf->raycast.distance_towall < MAX_DEPTH)
		//	ft_casting_ray(wolf);	//<----	old casting_ray function
		ft_calc_next_intersection(wolf);
		ft_calc_sampling_x(wolf);
		ft_fix_fisheye_distorsion(wolf);
		ft_set_ceiling_floor(wolf);
		wolf->raycast.y_render = 0;
		while (wolf->raycast.y_render < HEIGHT)
		{
			if (wolf->raycast.y_render < wolf->ceiling)
				ft_draw_ceiling(wolf);
			else if (wolf->raycast.y_render >= wolf->ceiling &&
					wolf->raycast.y_render <= wolf->floor)
				ft_draw_wall(wolf);
			else
				ft_draw_floor(wolf);
			ft_apply_brightness(wolf);
			wolf->raycast.y_render++;
		}
		wolf->raycast.x_render++;
	}
}
