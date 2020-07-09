/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:51:13 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/09 01:20:43 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_setup_view(t_env *doom)
{
	doom->calc_floor.horizon = (doom->raycast.y_render - HEIGHT / 2) -
		doom->cam.angle_z;

	doom->calc_floor.rowDistance = doom->cam.pos_z / doom->calc_floor.horizon;
	doom->calc_floor.rowDistance /= cos(doom->cam.angle -
		doom->raycast.ray_angle);

	doom->calc_floor.floorStepX = doom->calc_floor.rowDistance / WIDTH;
	doom->calc_floor.floorStepY = doom->calc_floor.rowDistance / WIDTH;
}

void	ft_apply_brightness(t_env *doom)
{
	int		shadowing;

	shadowing = doom->map.bright[(int)doom->cam.pos_y]
					[(int)doom->cam.pos_x];
	if (doom->map.bright[(int)doom->cam.pos_y]
					[(int)doom->cam.pos_x] != 3)
	{
		/* doom->screen_pixels[doom->raycast.y_render *
		WIDTH + doom->raycast.x_render] =
			ft_darken_color(doom->screen_pixels[doom->raycast.y_render *
				WIDTH + doom->raycast.x_render],
					(double)doom->map.bright[(int)doom->cam.pos_y]
						[(int)doom->cam.pos_x] /
							100); */
		while(shadowing++ - 3)
		{
		doom->screen_pixels[doom->raycast.y_render *
		WIDTH + doom->raycast.x_render] =
			(doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] >> 1) &
				0b01111111011111110111111101111111;
		}
	}
}

/* 
void	ft_casting_ray(t_env *doom)
{
	
	doom->raycast.distance_towall += 0.1;
	doom->raycast.test_x = (int)(doom->cam.pos_x +
							doom->raycast.eye_x *
							doom->raycast.distance_towall);
	doom->raycast.test_y = (int)(doom->cam.pos_y +
							doom->raycast.eye_y *
							doom->raycast.distance_towall);
	if (doom->raycast.test_x < 0 ||
			doom->raycast.test_x >= doom->map.nbcol ||
			doom->raycast.test_y < 0 ||
			doom->raycast.test_y >= doom->map.nbl)
	{
		doom->raycast.hit_wall = 1;
		doom->raycast.distance_towall = MAX_DEPTH;
	}
	else if (doom->map.data[doom->raycast.test_y]
								[doom->raycast.test_x] == WALL
		|| doom->map.data[doom->raycast.test_y]
								[doom->raycast.test_x] == DOOR
		|| doom->map.data[doom->raycast.test_y]
								[doom->raycast.test_x] == TRANSP) // a modifier
		doom->raycast.hit_wall = 1;
}
*/

void	ft_set_new_ray_angle(t_env *doom)
{
	doom->raycast.ray_angle = (doom->cam.angle + doom->cam.fov / 2.0) -
							((double)doom->raycast.x_render / (double)WIDTH) *
							doom->cam.fov;
	doom->raycast.distance_towall = 0;
	doom->raycast.hit_wall = 0;
	doom->raycast.shading = 1;
	doom->raycast.eye_x = sin(doom->raycast.ray_angle);
	doom->raycast.eye_y = cos(doom->raycast.ray_angle);
}

void	ft_draw_rendering(t_env *doom)
{
	doom->raycast.y_render = 0;
	while (doom->raycast.y_render < HEIGHT)
	{
		if (doom->raycast.y_render < doom->ceiling)
			ft_draw_ceiling(doom);
		else if (doom->raycast.y_render >= doom->ceiling &&
				doom->raycast.y_render <= doom->floor)
			ft_draw_wall(doom);
		else
			ft_draw_floor(doom);
		ft_apply_brightness(doom);
		doom->raycast.y_render++;
	}
	doom->raycast.x_render++;
}

void	ft_raycaster(t_env *doom)
{
	doom->raycast.x_render = 0;
	while (doom->raycast.x_render < WIDTH)
	{
		ft_set_new_ray_angle(doom);
		//while (doom->raycast.hit_wall == 0 &&
		//		doom->raycast.distance_towall < MAX_DEPTH)
		//	ft_casting_ray(doom);	//<----	old casting_ray function
		ft_calc_next_intersection(doom);
		ft_calc_sampling_x(doom);
		ft_fix_fisheye_distorsion(doom);
		ft_set_ceiling_floor(doom);
		ft_draw_rendering(doom);
	}
}
