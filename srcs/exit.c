/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 04:43:52 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 05:05:19 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_exit(t_env *doom, int exit_type, char *message)
{
	free_thread_env(&doom->shared_data);
	ft_destroy_texture_renderer_window(doom);
	ft_memdel((void **)&doom->screen_pixels);
	ft_free_fmod(doom);
	TTF_CloseFont(doom->txt.font);
	SDL_FreeSurface(doom->txt.welcome1);
	SDL_FreeSurface(doom->txt.welcome2);
	SDL_FreeSurface(doom->fps.s);
	TTF_Quit();
	ft_putendl("next step is SDL_Quit()");		//DEBUG
	SDL_Quit();
	ft_putendl("next step is ft_free_door()");		//DEBUG
	ft_free_door(doom->door);
	ft_putendl("next step is free_xpm()");		//DEBUG
	free_xpm(doom);
	ft_putendl("next step is ft_free_map()");		//DEBUG
	ft_free_map(&doom->map);
	ft_putendl("next step is ft_free_obj_list()");		//DEBUG
	ft_free_obj_list(&doom->obj.next);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	printf("time ~ from SDL_Init() : %f\n", get_time(doom));
	exit(exit_type);
}