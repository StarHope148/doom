/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/23 17:17:01 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_update_screen(t_env *doom)
{
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	ft_set_sdl_minimap_colors(doom);
	SDL_RenderPresent(doom->renderer);
}

void	import_screen_pixels(t_env *doom)
{
	int				thread_id;
	int				x;
	int				y;
	t_shared_data	*shared_data;

	shared_data = (t_shared_data*)&doom->shared_data;
	thread_id = -1;
	while (++thread_id < shared_data->max_thread)
	{
		x = shared_data->tab_thread_env[thread_id].x_start - 1;
		while (++x < shared_data->tab_thread_env[thread_id].x_end)
		{
			y = -1;
			while (++y < H)
				doom->screen_pixels[y * W + x] = shared_data->tab_thread_env[thread_id].screen_pixels[y * W + x];
		}
	}
}

void	threadsetc(t_env *doom)
{
	int	thread_id;

	pthread_mutex_lock(&doom->shared_data.mutex);
	while (!doom->shared_data.all_work_done)
		pthread_cond_wait(&doom->shared_data.cond_main, &doom->shared_data.mutex);
	doom->shared_data.all_work_done = 0;
	import_screen_pixels(doom);
	thread_id = -1;
	while (++thread_id < doom->shared_data.max_thread)
		update_thread_env(&doom->shared_data.tab_thread_env[thread_id]);
	pthread_cond_signal(&doom->shared_data.cond_main);
	pthread_mutex_unlock(&doom->shared_data.mutex);
}

void	ft_print(t_env *doom)
{
	animation_opening_door(doom);
	threadsetc(doom);
	//ft_raycaster(doom);
	ft_draw_minimap(doom);
	ft_draw_fps(doom);
	ft_draw_crosshair(doom);
	if (!doom->no_funky)
		ft_funky_textures(doom);
	ft_update_screen(doom);
	if ((SDL_UpdateTexture(doom->texture, NULL,
					doom->screen_pixels,
					doom->pitch)) < 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
}
