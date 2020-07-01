/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 22:45:07 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_key_released(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_w)
		wolf->cam.forward = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_a)
		wolf->cam.strafe_left = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_s)
		wolf->cam.backward = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_d)
		wolf->cam.strafe_right = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
		wolf->cam.rotate_right = FALSE;
	else if (wolf->event.key.keysym.sym == SDLK_LEFT)
		wolf->cam.rotate_left = FALSE;
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
			if (wolf->event.type == SDL_MOUSEMOTION)
				continue;
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
