/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:19 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/16 14:46:51 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_rotate_up(t_env *doom)
{
	if (doom->cam.angle_z <= 800)
		doom->cam.angle_z += UP_DOWN_ANGLE_SPEED;
}

void	ft_rotate_down(t_env *doom)
{
	if (doom->cam.angle_z >= -800)
		doom->cam.angle_z -= UP_DOWN_ANGLE_SPEED;
}

int		wall_on_cam_pos(t_env *doom)
{
	char	map_symbol;

	map_symbol = doom->map.data[(int)doom->cam.pos_y][(int)doom->cam.pos_x];
	if (map_symbol == WALL)
		return (1);
	else if (map_symbol == DOOR)
		return (2);
	else if (map_symbol == TRANSP)
		return (3);
	return (0);
}

void	ft_strafe_right(t_env *doom)
{
	doom->cam.pos_x -= cos(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_x += cos(doom->cam.angle) * doom->moves.movespeed;
	doom->cam.pos_y += sin(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_y -= sin(doom->cam.angle) * doom->moves.movespeed;
}

void	ft_strafe_left(t_env *doom)
{
	doom->cam.pos_x += cos(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_x -= cos(doom->cam.angle) * doom->moves.movespeed;
	doom->cam.pos_y -= sin(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_y += sin(doom->cam.angle) * doom->moves.movespeed;
}

void	ft_backward(t_env *doom)
{
	doom->cam.pos_x -= sin(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_x += sin(doom->cam.angle) * doom->moves.movespeed;
	doom->cam.pos_y -= cos(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_y += cos(doom->cam.angle) * doom->moves.movespeed;
}

void	ft_forward(t_env *doom)
{
	doom->cam.pos_x += sin(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_x -= sin(doom->cam.angle) * doom->moves.movespeed;
	doom->cam.pos_y += cos(doom->cam.angle) * doom->moves.movespeed;
	if (wall_on_cam_pos(doom))
		doom->cam.pos_y -= cos(doom->cam.angle) * doom->moves.movespeed;
}

void	set_movespeed_crouch_height(t_env *doom)
{
	if (doom->moves.crouching)
	{
		doom->h = H - H / 4;
		doom->moves.movespeed = MOVE_SPEED / 3;
	}
	if (!doom->moves.crouching)
	{
		doom->h = H;
		if (doom->moves.running && !doom->moves.backward)
		{
			if (doom->moves.forward)
				doom->moves.movespeed = 3 * MOVE_SPEED;
			if (!doom->moves.forward)
				doom->moves.movespeed = MOVE_SPEED;
		}
		if (!doom->moves.running)
			doom->moves.movespeed = MOVE_SPEED;
	}
}

void	ft_refresh_new_pos(t_env *doom)
{
	set_movespeed_crouch_height(doom);
	if (doom->moves.strafe_right == TRUE)
		ft_strafe_right(doom);
	if (doom->moves.strafe_left == TRUE)
		ft_strafe_left(doom);
	if (doom->moves.backward == TRUE)
		ft_backward(doom);
	if (doom->moves.forward == TRUE)
		ft_forward(doom);
	if (doom->moves.rotate_left == TRUE)
	{
		doom->cam.angle += ROTATE_SPEED;
		if (doom->cam.angle > PI)
			doom->cam.angle = -PI;
	}
	if (doom->moves.rotate_right == TRUE)
	{
		doom->cam.angle -= ROTATE_SPEED;
		if (doom->cam.angle <= -PI)
			doom->cam.angle = PI;
	}
	if (doom->moves.rotate_up == TRUE)
		ft_rotate_up(doom);
	if (doom->moves.rotate_down == TRUE)
		ft_rotate_down(doom);
}
