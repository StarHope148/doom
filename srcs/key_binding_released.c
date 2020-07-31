/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding_released.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 22:21:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 00:20:05 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_jump_crouch_fly_controls_released(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_LSHIFT)
		doom->moves.running = FALSE;
	if (doom->event.key.keysym.sym == SDLK_LCTRL)
		doom->moves.crouching = FALSE;
	if (doom->event.key.keysym.sym == SDLK_e)
		doom->moves.up = FALSE;
	if (doom->event.key.keysym.sym == SDLK_q)
		doom->moves.down = FALSE;
}

void		ft_rotate_controls_released(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_RIGHT)
		doom->moves.rotate_right = FALSE;
	if (doom->event.key.keysym.sym == SDLK_LEFT)
		doom->moves.rotate_left = FALSE;
	if (doom->event.key.keysym.sym == SDLK_UP)
		doom->moves.rotate_up = FALSE;
	if (doom->event.key.keysym.sym == SDLK_DOWN)
		doom->moves.rotate_down = FALSE;
}

void		ft_movement_controls_released(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_w)
		doom->moves.forward = FALSE;
	if (doom->event.key.keysym.sym == SDLK_a)
		doom->moves.strafe_left = FALSE;
	if (doom->event.key.keysym.sym == SDLK_s)
		doom->moves.backward = FALSE;
	if (doom->event.key.keysym.sym == SDLK_d)
		doom->moves.strafe_right = FALSE;
}
