/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:41:21 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 16:26:34 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_rotate_up(t_env *doom)
{
	if (doom->cam.angle_z <= MAX_ANGLE_Z)
		doom->cam.angle_z += UP_DOWN_ANGLE_SPEED;
}

void	ft_rotate_down(t_env *doom)
{
	if (doom->cam.angle_z >= -MAX_ANGLE_Z)
		doom->cam.angle_z -= UP_DOWN_ANGLE_SPEED;
}

void	ft_rotate_left(t_env *doom)
{
	doom->cam.angle += ROTATE_SPEED;
	if (doom->cam.angle > PI)
		doom->cam.angle = -PI;
}

void	ft_rotate_right(t_env *doom)
{
	doom->cam.angle -= ROTATE_SPEED;
	if (doom->cam.angle <= -PI)
		doom->cam.angle = PI;
}

void	ft_rotation(t_env *doom)
{
	if (doom->moves.rotate_left == TRUE)
		ft_rotate_left(doom);
	if (doom->moves.rotate_right == TRUE)
		ft_rotate_right(doom);
	if (doom->moves.rotate_up == TRUE)
		ft_rotate_up(doom);
	if (doom->moves.rotate_down == TRUE)
		ft_rotate_down(doom);
}
