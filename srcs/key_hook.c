/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/02 19:06:12 by czhang           ###   ########.fr       */
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

void	ft_key_hook(t_env *wolf)
{
	while (1)
	{
		while (SDL_PollEvent(&wolf->event))
		{
			if (wolf->event.type == SDL_KEYDOWN)
				ft_key_pressed(wolf);
			if (wolf->event.type == SDL_KEYUP)
				ft_key_released(wolf);
			if (wolf->event.type == SDL_QUIT)
				ft_exit(wolf, EXIT_SUCCESS, NULL);
		}
		ft_refresh_new_pos(wolf);
		ft_print(wolf);
	}
}
