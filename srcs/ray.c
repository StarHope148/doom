/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:52:39 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:25:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_setup(t_env *doom)
{
	doom->ray.deltadistx = sqrt(1 + (doom->raycast.eye_y *
		doom->raycast.eye_y) / (doom->raycast.eye_x * doom->raycast.eye_x));
	doom->ray.deltadisty = sqrt(1 + (doom->raycast.eye_x *
		doom->raycast.eye_x) / (doom->raycast.eye_y * doom->raycast.eye_y));
	doom->raycast.test_x = (int)doom->cam.pos_x;
	doom->raycast.test_y = (int)doom->cam.pos_y;
}

void	ft_set_direction(t_env *doom)
{
	if (doom->raycast.eye_x < 0)
	{
		doom->ray.stepx = -1;
		doom->ray.sidedistx = (doom->cam.pos_x - doom->raycast.test_x) *
			doom->ray.deltadistx;
	}
	else
	{
		doom->ray.stepx = 1;
		doom->ray.sidedistx = (doom->raycast.test_x + 1 - doom->cam.pos_x) *
			doom->ray.deltadistx;
	}
	if (doom->raycast.eye_y < 0)
	{
		doom->ray.stepy = -1;
		doom->ray.sidedisty = (doom->cam.pos_y - doom->raycast.test_y) *
			doom->ray.deltadisty;
	}
	else
	{
		doom->ray.stepy = 1;
		doom->ray.sidedisty = (doom->raycast.test_y + 1 - doom->cam.pos_y) *
			doom->ray.deltadisty;
	}
}

void	ft_search_collision(t_env *doom)
{
	while (doom->map.data[doom->raycast.test_y][doom->raycast.test_x] == EMPTY)
	{
		if (doom->ray.sidedistx < doom->ray.sidedisty)
		{
			doom->ray.sidedistx += doom->ray.deltadistx;
			doom->raycast.test_x += doom->ray.stepx;
			doom->ray.side = 0;
		}
		else
		{
			doom->ray.sidedisty += doom->ray.deltadisty;
			doom->raycast.test_y += doom->ray.stepy;
			doom->ray.side = 1;
		}
	}
}

void	ft_calcul_distance_to_collision(t_env *doom)
{
	if (doom->ray.side == 0)
	{
		doom->raycast.distance_towall =
			fabs((doom->raycast.test_x - doom->cam.pos_x +
				(1 - doom->ray.stepx) / 2) / doom->raycast.eye_x);
	}
	else
	{
		doom->raycast.distance_towall =
			fabs((doom->raycast.test_y - doom->cam.pos_y +
				(1 - doom->ray.stepy) / 2) / doom->raycast.eye_y);
	}
}

void	ft_calc_next_intersection(t_env *doom)
{
	ft_setup(doom);
	ft_set_direction(doom);
	ft_search_collision(doom);
	ft_calcul_distance_to_collision(doom);
}
