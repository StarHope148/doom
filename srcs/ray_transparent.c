/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transparent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:19:24 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 15:20:17 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_search_last_transparent(t_thread_env *e)
{
	int		i;

	i = 0;
	while (i < e->transparent_found)
	{
		if (e->map.data[e->rc.test_y * e->map.nbcol + e->rc.test_x] == GRID ||
				e->map.data[e->rc.test_y * e->map.nbcol + e->rc.test_x] == DOOR)
			i++;
		if (i >= e->transparent_found)
			return ;
		if (e->rc.sidedistx < e->rc.sidedisty)
		{
			e->rc.sidedistx += e->rc.deltadistx;
			e->rc.test_x += e->rc.stepx;
			e->rc.side = 0;
		}
		else
		{
			e->rc.sidedisty += e->rc.deltadisty;
			e->rc.test_y += e->rc.stepy;
			e->rc.side = 1;
		}
	}
}

void	ft_transparent_found(t_thread_env *e)
{
	if (e->map.data[e->rc.test_y * e->map.nbcol + e->rc.test_x] == GRID ||
			e->map.data[e->rc.test_y * e->map.nbcol + e->rc.test_x] == DOOR)
		e->transparent_found++;
}

void	ft_calc_next_intersection_transparent(t_thread_env *e)
{
	ft_setup(e);
	ft_set_direction(e);
	ft_search_last_transparent(e);
	ft_calcul_distance_to_collision(e);
}
