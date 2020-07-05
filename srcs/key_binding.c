/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:16:41 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 21:11:30 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_settings(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_KP_PLUS)
	{
		if (wolf->precision - RAY_LENGHT_STEP > 0)
			wolf->precision -= RAY_LENGHT_STEP;
	}
	else if (wolf->event.key.keysym.sym == SDLK_KP_MINUS)
		wolf->precision += RAY_LENGHT_STEP;
	else if ((wolf->count_puls > 25 || wolf->no_funky) && wolf->event.key.keysym.sym == SDLK_SPACE)
		wolf->wall = wolf->wall == 3 ? 0 : wolf->wall + 1;
	else if (wolf->event.key.keysym.sym == SDLK_RSHIFT)
	{
		wolf->no_funky = 1;
		wolf->wall = 3;
	}
}

void		ft_movement(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_w)
		wolf->moves.forward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_a)
		wolf->moves.strafe_left = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_s)
		wolf->moves.backward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_d)
		wolf->moves.strafe_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
		wolf->moves.rotate_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_LEFT)
		wolf->moves.rotate_left = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_UP)
		wolf->moves.rotate_up = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_DOWN)
		wolf->moves.rotate_down = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_LSHIFT)
		wolf->moves.running = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_LCTRL)
		wolf->moves.crouching = TRUE;
}
