/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding_pressed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:16:41 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/02 00:11:02 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_other_controls_pressed(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_SPACE ||
			doom->event.key.keysym.sym == SDLK_KP_0)
		ft_shoot_projectile(doom);
	if (doom->event.key.keysym.sym == SDLK_p)
		ft_pause_music(doom);
	if (doom->event.key.keysym.sym == SDLK_RETURN)
	{
		resolve_door(doom);
		ft_switch_button(doom);
	}
}

void		ft_rotate_controls_pressed(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_RIGHT)
		doom->moves.rotate_right = TRUE;
	if (doom->event.key.keysym.sym == SDLK_LEFT)
		doom->moves.rotate_left = TRUE;
	if (doom->event.key.keysym.sym == SDLK_UP)
		doom->moves.rotate_up = TRUE;
	if (doom->event.key.keysym.sym == SDLK_DOWN)
		doom->moves.rotate_down = TRUE;
}

void		ft_jump_crouch_fly_controls_pressed(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_LSHIFT)
		doom->moves.running = TRUE;
	if (doom->event.key.keysym.sym == SDLK_LCTRL)
		doom->moves.crouching = TRUE;
	if (doom->event.key.keysym.sym == SDLK_e)
		doom->moves.up = TRUE;
	if (doom->event.key.keysym.sym == SDLK_q)
		doom->moves.down = TRUE;
	if (doom->event.key.keysym.sym == SDLK_LALT)
	{
		if (doom->moves.jumping == FALSE)
			if ((FMOD_System_PlaySound(doom->sound.system, doom->sound.jump,
					NULL, 0, NULL)) != FMOD_OK)
				perror("Error in FMOD_System_PlaySound for jump ");
		doom->moves.jumping = TRUE;
	}
}

void		ft_movement_controls_pressed(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_w)
		doom->moves.forward = TRUE;
	if (doom->event.key.keysym.sym == SDLK_a)
		doom->moves.strafe_left = TRUE;
	if (doom->event.key.keysym.sym == SDLK_s)
		doom->moves.backward = TRUE;
	if (doom->event.key.keysym.sym == SDLK_d)
		doom->moves.strafe_right = TRUE;
}
