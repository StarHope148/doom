/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:16:41 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/24 14:02:36 by czhang           ###   ########.fr       */
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
		wolf->cam.forward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_a)
		wolf->cam.strafe_left = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_s)
		wolf->cam.backward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_d)
		wolf->cam.strafe_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
		wolf->cam.rotate_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_LEFT)
		wolf->cam.rotate_left = TRUE;
}
