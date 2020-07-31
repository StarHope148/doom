/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 04:43:52 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 06:36:20 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_exit(t_env *doom, int exit_type, char *message)
{
	printf("next step is free_thread_env()\n");		//DEBUG
	free_thread_env(&doom->shared_data);
	printf("next step is ft_destroy_texture_renderer_window()\n");		//DEBUG
	ft_destroy_texture_renderer_window(doom);
	printf("next step is freeing screen_pixel\n");		//DEBUG
	ft_memdel((void **)&doom->screen_pixels);
	printf("next step is ft_free_fmod()\n");		//DEBUG
	ft_free_fmod(doom);
	printf("next step is TTF_CloseFont()\n");		//DEBUG
	TTF_CloseFont(doom->txt.font);
	printf("next step is freeing welcome1, welcome2 and fps surface\n");		//DEBUG
	SDL_FreeSurface(doom->txt.welcome1);
	SDL_FreeSurface(doom->txt.welcome2);
	SDL_FreeSurface(doom->fps.s);
	printf("next step is TTF_Quit()\n");		//DEBUG
	TTF_Quit();
	printf("next step is SDL_Quit()\n");		//DEBUG
	SDL_Quit();
	printf("next step is ft_free_door()\n");		//DEBUG
	ft_free_door(doom->door);
	printf("next step is free_xpm()\n");		//DEBUG
	free_xpm(doom);
	printf("next step is ft_free_map()\n");		//DEBUG
	ft_free_map(&doom->map);
	printf("next step is ft_free_obj_list()\n");		//DEBUG
	ft_free_obj_list(&doom->obj.next);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	printf("time ~ from SDL_Init() : %f\n", get_time(doom));
	exit(exit_type);
}