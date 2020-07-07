/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:36:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 04:56:19 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free_door(t_door *list)
{
	if (list == NULL)
		return ;
	if (list->next != NULL)
		ft_free_door(list->next);
	ft_memdel((void **)&list);
}

void	ft_destroy_texture_renderer_window(t_env *wolf)
{
	if (wolf->texture != NULL)
	{
		SDL_DestroyTexture(wolf->texture);
		wolf->texture = NULL;
	}
	if (wolf->renderer != NULL)
	{
		SDL_DestroyRenderer(wolf->renderer);
		wolf->renderer = NULL;
	}
	if (wolf->window != NULL)
	{
		SDL_DestroyWindow(wolf->window);
		wolf->window = NULL;
	}
}

void	ft_free_surface_image(t_env *wolf)
{
	if (wolf->surface_wall_north != NULL)
	{
		SDL_FreeSurface(wolf->surface_wall_north);
		wolf->surface_wall_north = NULL;
	}
	if (wolf->surface_wall_south != NULL)
	{
		SDL_FreeSurface(wolf->surface_wall_south);
		wolf->surface_wall_south = NULL;
	}
	if (wolf->surface_wall_east != NULL)
	{
		SDL_FreeSurface(wolf->surface_wall_east);
		wolf->surface_wall_east = NULL;
	}
	if (wolf->surface_wall_west != NULL)
	{
		SDL_FreeSurface(wolf->surface_wall_west);
		wolf->surface_wall_west = NULL;
	}
	if (wolf->surface_floor != NULL)
	{
		SDL_FreeSurface(wolf->surface_floor);
		wolf->surface_floor = NULL;
	}
}

void	ft_free_map(t_map *m)
{
	int i;

	i = 0;
	if (m->data)
		while (i < m->nbl && m->data[i])
			ft_memdel((void **)&m->data[i++]);
	i = 0;
	if (m->bright)
		while (i < m->nbl && m->bright[i])
			ft_memdel((void **)&m->bright[i++]);
	i = 0;
	if (m->alt)
		while (i < m->nbl && m->alt[i])
			ft_memdel((void **)&m->alt[i++]);
	ft_memdel((void **)&m->data);
	ft_memdel((void **)&m->bright);
	ft_memdel((void **)&m->alt);
}
