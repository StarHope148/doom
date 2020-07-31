/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:36:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 10:14:59 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_thread_env(t_shared_data *shared_data)
{
	int	i;

	pthread_mutex_lock(&shared_data->mutex);
	shared_data->stop = 1;
	pthread_cond_broadcast(&shared_data->cond);
	pthread_cond_broadcast(&shared_data->cond_main);
	pthread_mutex_unlock(&shared_data->mutex);
	i = -1;
	while (++i < shared_data->max_thread)
		if (pthread_join(shared_data->tab_thread_env[i].thread, 0))
			ft_putendl_fd("Error pthread_join in free_thread_env()", 2);
	i = -1;
	while (++i < shared_data->max_thread)
	{
		ft_memdel((void**)&shared_data->tab_thread_env[i].screen_pixels);
		ft_free_map(&shared_data->tab_thread_env[i].map);
	}
	ft_memdel((void**)&shared_data->tab_thread_env);
	if (pthread_mutex_destroy(&shared_data->mutex))
		ft_putendl_fd("Error mutex_destroy\n", 2);
	if (pthread_cond_destroy(&shared_data->cond))
		ft_putendl_fd("Error cond_destroy\n", 2);
	if (pthread_cond_destroy(&shared_data->cond_main))
		ft_putendl_fd("Error cond_destroy\n", 2);
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

void	ft_free_obj_list(t_object **obj)
{
	t_object	*current;
	t_object	*next;

	current = *obj;
	while (current != NULL)
	{
		next = current->next;
		ft_memdel((void **)&(current));
		current = next;
	}
	*obj = NULL;
}
