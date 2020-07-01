/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:19 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 23:26:32 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_strafe_right(t_env *wolf)
{
	wolf->cam.pos_x -= cos(wolf->cam.angle) * MOVE_SPEED;
	wolf->cam.pos_y += sin(wolf->cam.angle) * MOVE_SPEED;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x += cos(wolf->cam.angle) * MOVE_SPEED;
		wolf->cam.pos_y -= sin(wolf->cam.angle) * MOVE_SPEED;
	}
}

void	ft_strafe_left(t_env *wolf)
{
	wolf->cam.pos_x += cos(wolf->cam.angle) * MOVE_SPEED;
	wolf->cam.pos_y -= sin(wolf->cam.angle) * MOVE_SPEED;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x -= cos(wolf->cam.angle) * MOVE_SPEED;
		wolf->cam.pos_y += sin(wolf->cam.angle) * MOVE_SPEED;
	}
}

void	ft_backward(t_env *wolf)
{
	wolf->cam.pos_x -= sin(wolf->cam.angle) * MOVE_SPEED;
	wolf->cam.pos_y -= cos(wolf->cam.angle) * MOVE_SPEED;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x += sin(wolf->cam.angle) * MOVE_SPEED;
		wolf->cam.pos_y += cos(wolf->cam.angle) * MOVE_SPEED;
	}
}

void	ft_forward(t_env *wolf)
{
	wolf->cam.pos_x += sin(wolf->cam.angle) * MOVE_SPEED;
	wolf->cam.pos_y += cos(wolf->cam.angle) * MOVE_SPEED;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x -= sin(wolf->cam.angle) * MOVE_SPEED;
		wolf->cam.pos_y -= cos(wolf->cam.angle) * MOVE_SPEED;
	}
}

void	ft_refresh_new_pos(t_env *wolf)
{
	if (wolf->cam.strafe_right == TRUE)
		ft_strafe_right(wolf);
	if (wolf->cam.strafe_left == TRUE)
		ft_strafe_left(wolf);
	if (wolf->cam.backward == TRUE)
		ft_backward(wolf);
	if (wolf->cam.forward == TRUE)
		ft_forward(wolf);
	if (wolf->cam.rotate_left == TRUE)
	{
		wolf->cam.angle += ROTATE_SPEED;
		if (wolf->cam.angle > PI)
			wolf->cam.angle = -PI;
	}
	if (wolf->cam.rotate_right == TRUE)
	{
		wolf->cam.angle -= ROTATE_SPEED;
		if (wolf->cam.angle <= -PI)
			wolf->cam.angle = PI;
	}
}
