/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:11:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 01:11:40 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void	ft_move(t_env *doom)
{
	if (doom->moves.strafe_right == TRUE)
		ft_strafe_right(doom);
	if (doom->moves.strafe_left == TRUE)
		ft_strafe_left(doom);
	if (doom->moves.backward == TRUE)
		ft_backward(doom);
	if (doom->moves.forward == TRUE)
		ft_forward(doom);
}
