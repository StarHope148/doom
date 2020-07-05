/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 23:37:46 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_key_released(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_w)
		wolf->moves.forward = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_a)
		wolf->moves.strafe_left = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_s)
		wolf->moves.backward = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_d)
		wolf->moves.strafe_right = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
		wolf->moves.rotate_right = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_LEFT)
		wolf->moves.rotate_left = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_UP)
		wolf->moves.rotate_up = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_DOWN)
		wolf->moves.rotate_down = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_LSHIFT)
		wolf->moves.running = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_LCTRL)
	{
		wolf->moves.crouching = FALSE;
		wolf->h = HEIGHT;
	}
}

void	ft_key_pressed(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_ESCAPE)
		ft_exit(wolf, EXIT_SUCCESS, NULL);
	ft_movement(wolf);
	ft_settings(wolf);
}
