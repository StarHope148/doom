/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:57:45 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:25:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_setup_ray_hit_location(t_env *doom)
{
	doom->calc.block_mid_x = (double)(doom->raycast.test_x) + 0.5;
	doom->calc.block_mid_y = (double)(doom->raycast.test_y) + 0.5;
	doom->calc.test_point_x = doom->cam.pos_x + doom->raycast.eye_x *
								doom->raycast.distance_towall;
	doom->calc.test_point_y = doom->cam.pos_y + doom->raycast.eye_y *
								doom->raycast.distance_towall;
	doom->calc.test_angle = atan2((doom->calc.test_point_y -
									doom->calc.block_mid_y),
								(doom->calc.test_point_x -
							doom->calc.block_mid_x));
}

void	ft_calc_sampling_x(t_env *doom)
{
	ft_setup_ray_hit_location(doom);
	doom->calc.sample_x = 0;
	if (doom->calc.test_angle >= -PI * 0.25 &&
		doom->calc.test_angle <= PI * 0.25)
		ft_west_face(doom);
	else if (doom->calc.test_angle >= PI * 0.25 &&
			doom->calc.test_angle <= PI * 0.75)
		ft_north_face(doom);
	else if (doom->calc.test_angle <= -PI * 0.25 &&
				doom->calc.test_angle >= -PI * 0.75)
		ft_south_face(doom);
	else if (doom->calc.test_angle >= PI * 0.75 ||
			doom->calc.test_angle <= -PI * 0.75)
		ft_east_face(doom);
	doom->calc.sample_x = fabs(doom->calc.sample_x - (int)doom->calc.sample_x);
}
