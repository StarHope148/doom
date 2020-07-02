/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:19 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/02 19:24:31 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_strafe_right(t_env *wolf)
{
	wolf->cam.pos_x -= cos(wolf->cam.angle) * wolf->moves.movespeed;
	wolf->cam.pos_y += sin(wolf->cam.angle) * wolf->moves.movespeed;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x += cos(wolf->cam.angle) * wolf->moves.movespeed;
		wolf->cam.pos_y -= sin(wolf->cam.angle) * wolf->moves.movespeed;
	}
}

void	ft_strafe_left(t_env *wolf)
{
	wolf->cam.pos_x += cos(wolf->cam.angle) * wolf->moves.movespeed;
	wolf->cam.pos_y -= sin(wolf->cam.angle) * wolf->moves.movespeed;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x -= cos(wolf->cam.angle) * wolf->moves.movespeed;
		wolf->cam.pos_y += sin(wolf->cam.angle) * wolf->moves.movespeed;
	}
}

void	ft_backward(t_env *wolf)
{
	wolf->cam.pos_x -= sin(wolf->cam.angle) * wolf->moves.movespeed;
	wolf->cam.pos_y -= cos(wolf->cam.angle) * wolf->moves.movespeed;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x += sin(wolf->cam.angle) * wolf->moves.movespeed;
		wolf->cam.pos_y += cos(wolf->cam.angle) * wolf->moves.movespeed;
	}
}

void	ft_forward(t_env *wolf)
{
	wolf->cam.pos_x += sin(wolf->cam.angle) * wolf->moves.movespeed;
	wolf->cam.pos_y += cos(wolf->cam.angle) * wolf->moves.movespeed;
	if (wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x] == WALL)
	{
		wolf->cam.pos_x -= sin(wolf->cam.angle) * wolf->moves.movespeed;
		wolf->cam.pos_y -= cos(wolf->cam.angle) * wolf->moves.movespeed;
	}
}

void	set_movespeed_crouch_height(t_env *wolf)
{
	if (wolf->moves.crouching)
	{
		wolf->h = HEIGHT - HEIGHT / 4;
		wolf->moves.movespeed = MOVE_SPEED / 3;
	}
	if (!wolf->moves.crouching)
	{
		wolf->h = HEIGHT;
		if (wolf->moves.running && !wolf->moves.backward)
		{
			if (wolf->moves.forward)
				wolf->moves.movespeed = 3 * MOVE_SPEED;
			if (!wolf->moves.forward)
				wolf->moves.movespeed = MOVE_SPEED;
		}
		if (!wolf->moves.running)
			wolf->moves.movespeed = MOVE_SPEED;
	}
}

void	ft_refresh_new_pos(t_env *wolf)
{
	set_movespeed_crouch_height(wolf);
	if (wolf->moves.strafe_right == TRUE)
		ft_strafe_right(wolf);
	if (wolf->moves.strafe_left == TRUE)
		ft_strafe_left(wolf);
	if (wolf->moves.backward == TRUE)
		ft_backward(wolf);
	if (wolf->moves.forward == TRUE)
		ft_forward(wolf);
	if (wolf->moves.rotate_left == TRUE)
	{
		wolf->cam.angle += ROTATE_SPEED;
		if (wolf->cam.angle > PI)
			wolf->cam.angle = -PI;
	}
	if (wolf->moves.rotate_right == TRUE)
	{
		wolf->cam.angle -= ROTATE_SPEED;
		if (wolf->cam.angle <= -PI)
			wolf->cam.angle = PI;
	}
}
