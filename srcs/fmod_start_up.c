/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmod_start_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 06:51:22 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 16:26:22 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_pause_music(t_env *doom)
{
	if ((FMOD_Channel_GetPaused(doom->sound.channel_music,
			&doom->sound.state)) != FMOD_OK)
		perror("Error in FMOD_Channel_GetPaused for music ");
	if (doom->sound.state == FALSE)
	{
		if ((FMOD_Channel_SetPaused(doom->sound.channel_music, TRUE)) !=
				FMOD_OK)
			perror("Error in FMOD_Channel_SetPaused for music ");
	}
	else
	{
		if ((FMOD_Channel_SetPaused(doom->sound.channel_music, FALSE)) !=
				FMOD_OK)
			perror("Error in FMOD_Channel_SetPaused for music ");
	}
}

static void	ft_fmod2(t_env *doom)
{
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/laser_shot.mp3", FMOD_CREATESTREAM, 0,
				&doom->sound.laser_shot)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for laser_shot ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/life_down.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.life_down)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for life_down ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/door_opening.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.door_opening)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for door_opening ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/door_closing.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.door_closing)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for door_closing ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/life_up.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.life_up)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for life_up ");
	if ((FMOD_Sound_SetLoopCount(doom->sound.music, -1)) != FMOD_OK)
		perror("Error in FMOD_Sound_SetLoopCount for music ");
}

void		ft_fmod(t_env *doom)
{
	doom->sound.fmod_launched = TRUE;
	if ((FMOD_System_Create(&doom->sound.system)) != FMOD_OK)
		perror("Error in FMOD_System_Create ");
	if ((FMOD_System_Init(doom->sound.system, 32, FMOD_INIT_NORMAL, NULL)) !=
			FMOD_OK)
		perror("Error in FMOD_System_Init ");
	if ((FMOD_System_CreateSound(doom->sound.system, "sounds/mario_jump.mp3",
			FMOD_CREATESAMPLE, 0, &doom->sound.jump)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for jump ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/music/doom_music.mp3", FMOD_LOOP_NORMAL, 0,
				&doom->sound.music)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for music ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/switch_on.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.switch_on)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for switch_on ");
	if ((FMOD_System_CreateSound(doom->sound.system,
			"sounds/switch_off.wav", FMOD_CREATESTREAM, 0,
				&doom->sound.switch_off)) != FMOD_OK)
		perror("Error in FMOD_System_CreateSound for switch_off ");
	ft_fmod2(doom);
}
