/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 21:29:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 00:16:16 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_points(t_env *wolf)
{
	wolf->minimap.done = 0;
	wolf->minimap.x = wolf->minimap.j * wolf->block;
	wolf->minimap.y = wolf->minimap.i * wolf->block;
	wolf->minimap.def_x = wolf->minimap.x;
	wolf->minimap.def_y = wolf->minimap.y;
}

void	ft_draw_minimap_wall(t_env *wolf)
{
	while (wolf->minimap.done == 0)
	{
		wolf->screen_pixels[wolf->minimap.y * WIDTH + wolf->minimap.x] = LIME;
		wolf->minimap.x++;
		if (wolf->minimap.x > wolf->minimap.def_x + wolf->block)
		{
			wolf->minimap.x = wolf->minimap.j * wolf->block;
			wolf->minimap.y++;
		}
		if (wolf->minimap.y > wolf->minimap.def_y + wolf->block)
			wolf->minimap.done = 1;
	}
}

void	ft_draw_minimap_empty_space(t_env *wolf)
{
	while (wolf->minimap.done == 0)
	{
		wolf->screen_pixels[wolf->minimap.y * WIDTH + wolf->minimap.x] = GRAY;
		wolf->minimap.x++;
		if (wolf->minimap.x > wolf->minimap.def_x + wolf->block)
		{
			wolf->minimap.x = wolf->minimap.j * wolf->block;
			wolf->minimap.y++;
		}
		if (wolf->minimap.y > wolf->minimap.def_y + wolf->block)
			wolf->minimap.done = 1;
	}
}

void	ft_set_sdl_minimap_colors(t_env *wolf)
{
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x * wolf->block,
						wolf->cam.pos_y * wolf->block,
						(wolf->cam.pos_x + sin(wolf->cam.angle)) * wolf->block,
						(wolf->cam.pos_y + cos(wolf->cam.angle)) *
						wolf->block);
	SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(wolf->renderer, wolf->cam.pos_x * wolf->block,
						wolf->cam.pos_y * wolf->block);
}

void	ft_draw_minimap(t_env *wolf)
{
	wolf->minimap.j = 0;
	while (wolf->minimap.j < (int)wolf->map.nbcol)
	{
		wolf->minimap.i = 0;
		while (wolf->minimap.i < (int)wolf->map.nbl)
		{
			ft_set_points(wolf);
			if (wolf->map.data[wolf->minimap.i][wolf->minimap.j] == WALL)
				ft_draw_minimap_wall(wolf);
			else if (wolf->map.data[wolf->minimap.i]
						[wolf->minimap.j] == EMPTY)
				ft_draw_minimap_empty_space(wolf);
			wolf->minimap.i++;
		}
		wolf->minimap.j++;
	}
}
