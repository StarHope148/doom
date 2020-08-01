/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 01:42:21 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 05:14:26 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_load_wall_textures(t_env *doom)
{
	if ((get_xpm("textures/wall_skull.xpm", &doom->xpm[NORTH])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for wall_skull.xpm");
	if ((get_xpm("textures/wall_skull.xpm", &doom->xpm[SOUTH])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for wall_skull.xpm");
	if ((get_xpm("textures/wall_skull.xpm", &doom->xpm[WEST])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for wall_skull.xpm");
	if ((get_xpm("textures/wall_skull.xpm", &doom->xpm[EAST])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for wall_skull.xpm");
}

void		ft_load_floor_sky_textures(t_env *doom)
{
	if ((get_xpm("textures/floor_metal.xpm", &doom->xpm[FLOOR])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for floor_metal.xpm");
	if ((get_xpm("textures/sky_red.xpm", &doom->xpm[SKY])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for sky_red.xpm");
}

void		ft_load_torch_textures(t_env *doom)
{
	if ((get_xpm("textures/torch/torch_1.xpm", &doom->xpm[TORCH_1_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_1.xpm");
	if ((get_xpm("textures/torch/torch_2.xpm", &doom->xpm[TORCH_2_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_2.xpm");
	if ((get_xpm("textures/torch/torch_3.xpm", &doom->xpm[TORCH_3_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_3.xpm");
	if ((get_xpm("textures/torch/torch_4.xpm", &doom->xpm[TORCH_4_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_4.xpm");
	if ((get_xpm("textures/torch/torch_5.xpm", &doom->xpm[TORCH_5_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_5.xpm");
	if ((get_xpm("textures/torch/torch_6.xpm", &doom->xpm[TORCH_6_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_6.xpm");
	if ((get_xpm("textures/torch/torch_7.xpm", &doom->xpm[TORCH_7_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_7.xpm");
	if ((get_xpm("textures/torch/torch_8.xpm", &doom->xpm[TORCH_8_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for torch_8.xpm");
}

void		ft_load_statue_textures(t_env *doom)
{
	t_xpm	*x;

	x = doom->xpm;
	if (get_xpm("textures/statue/statue_front.xpm", &x[STATUE_FRONT_XPM]))
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for statue_front.xpm");
	if (get_xpm("textures/statue/statue_right.xpm", &x[STATUE_RIGHT_XPM]))
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for statue_right.xpm");
	if (get_xpm("textures/statue/statue_left.xpm", &x[STATUE_LEFT_XPM]))
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for statue_left.xpm");
}

void		ft_load_textures(t_env *doom)
{
	ft_load_wall_textures(doom);
	ft_load_floor_sky_textures(doom);
	ft_load_torch_textures(doom);
	ft_load_statue_textures(doom);
	ft_load_textures_2(doom);
}
