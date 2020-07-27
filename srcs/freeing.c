/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:36:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/27 23:24:56 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_thread_env(t_shared_data *shared_data)
{
	int	i;

	pthread_mutex_lock(&shared_data->mutex);
	shared_data->stop = 1;
	pthread_cond_broadcast(&shared_data->cond);
	pthread_mutex_unlock(&shared_data->mutex);
	i = -1;
	while (++i < shared_data->max_thread)
		pthread_join(shared_data->tab_thread_env[i].thread, 0);
	pthread_cond_broadcast(&shared_data->cond);
	i = -1;
	while (++i < shared_data->max_thread)
	{
		ft_memdel((void**)&shared_data->tab_thread_env[i].screen_pixels);
		ft_free_map(&shared_data->tab_thread_env[i].map);
	}
	ft_memdel((void**)&shared_data->tab_thread_env);
}

void	free_xpm(t_env *doom)
{
	int	xpm_id;

	xpm_id = 0;
	while (xpm_id < NB_XPM)
	{
		free_one_xpm(&doom->xpm[xpm_id]);
	xpm_id++;
	}
}

void	free_one_xpm(t_xpm *xpm)
{
	int	i_color;

	if (xpm->color)
	{
		i_color = -1;
		while (++i_color < xpm->colormax && xpm->color[i_color])
			ft_memdel((void **)&xpm->color[i_color]);
		ft_memdel((void **)&xpm->color);
	}
	ft_memdel((void **)&xpm->pixels);
}

void	ft_free_door(t_door *list)
{
	if (list == NULL)
		return ;
	if (list->next)
		ft_free_door(list->next);
	ft_memdel((void **)&list);
}

void	ft_destroy_texture_renderer_window(t_env *doom)
{
	if (doom->texture != NULL)
	{
		SDL_DestroyTexture(doom->texture);
		doom->texture = NULL;
	}
	if (doom->renderer != NULL)
	{
		SDL_DestroyRenderer(doom->renderer);
		doom->renderer = NULL;
	}
	if (doom->window != NULL)
	{
		SDL_DestroyWindow(doom->window);
		doom->window = NULL;
	}
}

void	ft_free_map(t_map *m)
{
	ft_memdel((void **)&m->data);
	ft_memdel((void **)&m->bright);
	ft_memdel((void **)&m->alt);
}
