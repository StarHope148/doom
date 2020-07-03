/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:16:41 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/03 22:39:32 by jcanteau         ###   ########.fr       */
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
	else if (wolf->event.key.keysym.sym == SDLK_SPACE)
	{
		if (wolf->switch_textures == NON_TEXTURED)
			wolf->switch_textures = SHADED;
		else if (wolf->switch_textures == SHADED)
			wolf->switch_textures = COLOR_ORIENTED;
		else if (wolf->switch_textures == COLOR_ORIENTED)
			wolf->switch_textures = TEXTURED;
		else if (wolf->switch_textures == TEXTURED)
			wolf->switch_textures = NON_TEXTURED;
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
