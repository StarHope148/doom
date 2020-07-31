/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 09:36:40 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	ft_update_screen(t_env *doom)
{
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	ft_set_sdl_minimap_colors(doom);
	SDL_RenderPresent(doom->renderer);
}

static void	import_screen_pixels(t_env *doom)
{
	int				thread_id;
	t_point			pix;
	t_shared_data	*shared_data;

	shared_data = (t_shared_data*)&doom->shared_data;
	thread_id = -1;
	while (++thread_id < shared_data->max_thread)
	{
		pix.x = shared_data->tab_thread_env[thread_id].x_start - 1;
		while (++pix.x < shared_data->tab_thread_env[thread_id].x_end)
		{
			pix.y = -1;
			while (++pix.y < H)
				doom->screen_pixels[pix.y * W + pix.x] = shared_data->
					tab_thread_env[thread_id].screen_pixels[pix.y * W + pix.x];
		}
	}
}

static void	set_raycast_threads(t_env *doom)
{
	int				thread_id;
	t_shared_data	*shared_data;

	shared_data = &doom->shared_data;
	pthread_mutex_lock(&shared_data->mutex);
	while (!shared_data->all_work_done)
		pthread_cond_wait(&shared_data->cond_main, &shared_data->mutex);
	shared_data->all_work_done = 0;
	import_screen_pixels(doom);
	thread_id = -1;
	while (++thread_id < shared_data->max_thread)
		update_thread_env(&shared_data->tab_thread_env[thread_id]);
	pthread_cond_signal(&shared_data->cond_main);
	pthread_mutex_unlock(&shared_data->mutex);
}

static void	draw_welcome_text(t_env *doom)
{
	if (get_time(doom) < 8)
		draw_centered_text(doom, doom->txt.welcome1);
}

void		draw_only_bar(t_env *e)
{
	t_point			delta;
	t_point			sample;
	t_xpm			*x;

	x = &e->xpm[HEALTHBAR_XPM];
	delta.y = -1;
	while (++delta.y < e->hp.size.y)
	{
		delta.x = -1;
		while (++delta.x < e->hp.size.x)
		{
			sample.y = delta.y * x->h / e->hp.size.y;
			sample.x = delta.x * x->w / e->hp.size.x;
			if (x->pixels[sample.y * x->w + sample.x] != MAGENTA)
				e->screen_pixels[(e->hp.y_ + delta.y) * W + delta.x] =
									x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		draw_hp(t_env *e)
{
	t_xpm			*x;
	t_point			delta;

	x = &e->xpm[HEALTHBAR_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1 || e->hp.size.x >= W
			|| e->hp.y_ + e->hp.size.y * W + e->hp.size.x >= W * H)
		return ;
	delta.y = e->hp.start_red.y;
	e->hp.current_red_x = (e->hp.max_red.x - e->hp.start_red.x)
												* e->chr.health / 100;
	while (++delta.y < e->hp.max_red.y)
	{
		delta.x = -1;
		while (++delta.x < e->hp.current_red_x)
			e->screen_pixels[(e->hp.y_ + delta.y) * W
										+ delta.x + e->hp.start_red.x] = RED;
	}
	draw_only_bar(e);
}

void		draw_carried_key(t_env *e)
{
	t_point			delta;
	t_point			sample;
	t_xpm			*x;

	if (!e->chr.carried_key)
		return ;
	x = &e->xpm[KEY_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1 || e->key.size.x >= W
			|| e->key.y_ + e->key.size.y * W + e->key.size.x >= W * H)
		return ;
	delta.y = -1;
	while (++delta.y < e->key.size.y)
	{
		delta.x = -1;
		while (++delta.x < e->key.size.x)
		{
			sample.y = delta.y * x->h / e->key.size.y;
			sample.x = delta.x * x->w / e->key.size.x;
			if (x->pixels[sample.y * x->w + sample.x] != MAGENTA)
				e->screen_pixels[(e->key.y_ + delta.y) * W + delta.x] =
									x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		ft_print(t_env *doom)
{
	animation_opening_door(doom);
	set_raycast_threads(doom);
	ft_draw_objects(doom);
	ft_draw_minimap(doom);
	ft_draw_fps(doom);
	ft_draw_crosshair(doom);
	draw_welcome_text(doom);
	draw_hp(doom);
	draw_carried_key(doom);
	if (!doom->no_funky)
		ft_funky_textures(doom);
	ft_update_screen(doom);
	if ((SDL_UpdateTexture(doom->texture, NULL,
					doom->screen_pixels,
					doom->pitch)) < 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
}
