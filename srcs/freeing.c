/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:36:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/09 05:28:22 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_free_xpm(t_xpm *xpm)
{
	int	i;

	if (xpm->color)
	{
		i = -1;
		while (++i < xpm->colormax && xpm->color[i])
			ft_memdel((void **)&xpm->color[i]);
		ft_memdel((void **)&xpm->color);
	}
	ft_memdel((void **)&xpm->filename);
	ft_memdel((void **)&xpm->pixels);
	ft_memdel((void **)&xpm);
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

void	ft_free_surface_image(t_env *doom)
{
	if (doom->surface_wall_north != NULL)
	{
		SDL_FreeSurface(doom->surface_wall_north);
		doom->surface_wall_north = NULL;
	}
	if (doom->surface_wall_south != NULL)
	{
		SDL_FreeSurface(doom->surface_wall_south);
		doom->surface_wall_south = NULL;
	}
	if (doom->surface_wall_east != NULL)
	{
		SDL_FreeSurface(doom->surface_wall_east);
		doom->surface_wall_east = NULL;
	}
	if (doom->surface_wall_west != NULL)
	{
		SDL_FreeSurface(doom->surface_wall_west);
		doom->surface_wall_west = NULL;
	}
	if (doom->surface_floor != NULL)
	{
		SDL_FreeSurface(doom->surface_floor);
		doom->surface_floor = NULL;
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
