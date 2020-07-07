/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:05:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:25:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_west_face(t_env *doom)
{
	doom->calc.sample_x = doom->calc.test_point_y -
							(double)doom->raycast.test_y - 1;
	doom->orientation = WEST;
}

void	ft_north_face(t_env *doom)
{
	doom->calc.sample_x = doom->calc.test_point_x -
							(double)doom->raycast.test_x;
	doom->orientation = NORTH;
}

void	ft_south_face(t_env *doom)
{
	doom->calc.sample_x = doom->calc.test_point_x -
							(double)doom->raycast.test_x - 1;
	doom->orientation = SOUTH;
}

void	ft_east_face(t_env *doom)
{
	doom->calc.sample_x = doom->calc.test_point_y -
							(double)doom->raycast.test_y;
	doom->orientation = EAST;
}
