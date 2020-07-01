/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:36:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 16:56:07 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
}

void	ft_free_map(t_env *wolf)
{
	int i;

	i = 0;
	while (i < wolf->mapdata.nbl && wolf->mapdata.map[i] != NULL)
	{
		ft_memdel((void **)&wolf->mapdata.map[i]);
		i++;
	}
	ft_memdel((void **)&wolf->mapdata.map);
}
