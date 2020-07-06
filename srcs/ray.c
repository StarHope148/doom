/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:52:39 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/06 22:18:45 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_setup(t_env *wolf)
{
	wolf->ray.deltadistx = sqrt(1 + (wolf->raycast.eye_y *
		wolf->raycast.eye_y) / (wolf->raycast.eye_x * wolf->raycast.eye_x));
	wolf->ray.deltadisty = sqrt(1 + (wolf->raycast.eye_x *
		wolf->raycast.eye_x) / (wolf->raycast.eye_y * wolf->raycast.eye_y));
	wolf->raycast.test_x = (int)wolf->cam.pos_x;
	wolf->raycast.test_y = (int)wolf->cam.pos_y;
}

void	ft_set_direction(t_env *wolf)
{
	if (wolf->raycast.eye_x < 0)
	{
		wolf->ray.stepx = -1;
		wolf->ray.sidedistx = (wolf->cam.pos_x - wolf->raycast.test_x) *
			wolf->ray.deltadistx;
	}
	else
	{
		wolf->ray.stepx = 1;
		wolf->ray.sidedistx = (wolf->raycast.test_x + 1 - wolf->cam.pos_x) *
			wolf->ray.deltadistx;
	}
	if (wolf->raycast.eye_y < 0)
	{
		wolf->ray.stepy = -1;
		wolf->ray.sidedisty = (wolf->cam.pos_y - wolf->raycast.test_y) *
			wolf->ray.deltadisty;
	}
	else
	{
		wolf->ray.stepy = 1;
		wolf->ray.sidedisty = (wolf->raycast.test_y + 1 - wolf->cam.pos_y) *
			wolf->ray.deltadisty;
	}
}

void	ft_search_collision(t_env *wolf)
{
	while (wolf->map.data[wolf->raycast.test_y][wolf->raycast.test_x] == EMPTY)
	{
		if (wolf->ray.sidedistx < wolf->ray.sidedisty)
		{
			wolf->ray.sidedistx += wolf->ray.deltadistx;
			wolf->raycast.test_x += wolf->ray.stepx;
			wolf->ray.side = 0;
		}
		else
		{
			wolf->ray.sidedisty += wolf->ray.deltadisty;
			wolf->raycast.test_y += wolf->ray.stepy;
			wolf->ray.side = 1;
		}
	}
}

void	ft_calcul_distance_to_collision(t_env *wolf)
{
	if (wolf->ray.side == 0)
	{
		wolf->raycast.distance_towall =
			fabs((wolf->raycast.test_x - wolf->cam.pos_x +
				(1 - wolf->ray.stepx) / 2) / wolf->raycast.eye_x);
	}
	else
	{
		wolf->raycast.distance_towall =
			fabs((wolf->raycast.test_y - wolf->cam.pos_y +
				(1 - wolf->ray.stepy) / 2) / wolf->raycast.eye_y);
	}
}

void	ft_calc_next_intersection(t_env *wolf)
{
	ft_setup(wolf);
	ft_set_direction(wolf);
	ft_search_collision(wolf);
	ft_calcul_distance_to_collision(wolf);
}
