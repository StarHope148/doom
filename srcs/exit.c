/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 04:43:52 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 02:52:13 by jcanteau         ###   ########.fr       */
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
	SDL_FreeSurface(doom->txt.end_level);
	SDL_FreeSurface(doom->txt.dead);
	SDL_FreeSurface(doom->fps.s);
	TTF_Quit();
	SDL_Quit();
	ft_free_door(doom->door);
	free_xpm(doom);
	ft_free_map(&doom->map);
	ft_free_obj_list(&doom->obj.next);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	printf("time ~ from SDL_Init() : %f\n", get_time(doom));
	exit(exit_type);
}
