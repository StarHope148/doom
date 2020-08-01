/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 04:43:52 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 19:21:05 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_free_close_fmod(t_env *doom)
{
	if (doom->editor)
		return ;
	if ((FMOD_Sound_Release(doom->sound.jump)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of jump");
	if ((FMOD_Sound_Release(doom->sound.switch_on)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of switch_on");
	if ((FMOD_Sound_Release(doom->sound.switch_off)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of switch_off");
	if ((FMOD_Sound_Release(doom->sound.door_opening)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of door_opening");
	if ((FMOD_Sound_Release(doom->sound.door_closing)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of door_closing");
	if ((FMOD_Sound_Release(doom->sound.laser_shot)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of laser_shot");
	if ((FMOD_Sound_Release(doom->sound.life_down)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of life_down");
	if ((FMOD_Sound_Release(doom->sound.life_up)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of life_up");
	if ((FMOD_Sound_Release(doom->sound.music)) != FMOD_OK)
		perror("Error in FMOD_Sound_Release of music");
	if ((FMOD_System_Close(doom->sound.system)) != FMOD_OK)
		perror("Error in FMOD_System_Close ");
	if ((FMOD_System_Release(doom->sound.system)) != FMOD_OK)
		perror("Error in FMOD_System_Release ");
}

void		ft_free_close_ttf(t_env *doom)
{
	TTF_CloseFont(doom->txt.font);
	SDL_FreeSurface(doom->txt.welcome1);
	SDL_FreeSurface(doom->txt.welcome2);
	SDL_FreeSurface(doom->txt.objectif);
	SDL_FreeSurface(doom->txt.end_level);
	SDL_FreeSurface(doom->txt.dead);
	SDL_FreeSurface(doom->fps.s);
	TTF_Quit();
}

void		ft_exit(t_env *doom, int exit_type, char *message)
{
	free_thread_env(&doom->shared_data);
	ft_destroy_texture_renderer_window(doom);
	ft_memdel((void **)&doom->screen_pixels);
	if (doom->sound.fmod_launched == TRUE)
		ft_free_close_fmod(doom);
	ft_free_close_ttf(doom);
	SDL_Quit();
	ft_free_door(doom->door);
	free_xpm(doom);
	ft_free_map(&doom->map);
	ft_free_obj_list(&doom->obj.next);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	exit(exit_type);
}
