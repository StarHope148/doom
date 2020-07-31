/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 00:19:14 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_key_released(t_env *doom)
{
	ft_movement_controls_released(doom);
	ft_rotate_controls_released(doom);
	ft_jump_crouch_fly_controls_released(doom);
}

void		ft_key_pressed(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_ESCAPE)
		ft_exit(doom, EXIT_SUCCESS, NULL);
	ft_movement_controls_pressed(doom);
	ft_other_controls_pressed(doom);
	ft_rotate_controls_pressed(doom);
	ft_jump_crouch_fly_controls_pressed(doom);
	ft_settings_controls(doom);
}

void		ft_key_hook(t_env *doom)
{
	if (doom->event.type == SDL_KEYDOWN)
		ft_key_pressed(doom);
	if (doom->event.type == SDL_KEYUP)
		ft_key_released(doom);
	if (doom->event.type == SDL_QUIT)
		ft_exit(doom, EXIT_SUCCESS, NULL);
}
