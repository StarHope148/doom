/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:57:45 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 23:30:52 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_setup_ray_hit_location(t_env *wolf)
{
	wolf->calc.block_mid_x = (double)(wolf->raycast.test_x) + 0.5;
	wolf->calc.block_mid_y = (double)(wolf->raycast.test_y) + 0.5;
	wolf->calc.test_point_x = wolf->cam.pos_x + wolf->raycast.eye_x *
								wolf->raycast.distance_towall;
	wolf->calc.test_point_y = wolf->cam.pos_y + wolf->raycast.eye_y *
								wolf->raycast.distance_towall;
	wolf->calc.test_angle = atan2((wolf->calc.test_point_y -
									wolf->calc.block_mid_y),
								(wolf->calc.test_point_x -
							wolf->calc.block_mid_x));
}

void	ft_calc_sampling_x(t_env *wolf)
{
	ft_setup_ray_hit_location(wolf);
	wolf->calc.sample_x = 0;
	if (wolf->calc.test_angle >= -PI * 0.25 &&
		wolf->calc.test_angle <= PI * 0.25)
		ft_west_face(wolf);
	else if (wolf->calc.test_angle >= PI * 0.25 &&
			wolf->calc.test_angle <= PI * 0.75)
		ft_north_face(wolf);
	else if (wolf->calc.test_angle <= -PI * 0.25 &&
				wolf->calc.test_angle >= -PI * 0.75)
		ft_south_face(wolf);
	else if (wolf->calc.test_angle >= PI * 0.75 ||
			wolf->calc.test_angle <= -PI * 0.75)
		ft_east_face(wolf);
	wolf->calc.sample_x = fabs(wolf->calc.sample_x - (int)wolf->calc.sample_x);
}
