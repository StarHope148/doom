/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 21:29:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 15:49:55 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_set_tile_color_2(t_env *doom, int y, int x, Uint32 *color)
{
	char	symb;

	symb = doom->map.data[y * doom->map.nbcol + x];
	if (symb == HEALTH_POTION)
		*color = RED;
	else if (symb == KEY)
		*color = YELLOW;
	else if (symb == TORCH)
		*color = BURLYWOOD;
	else if (symb == STATUE)
		*color = BLACK;
	else if (symb == END_CASE)
		*color = MAGENTA;
	else if (symb == SPAWN)
		*color = CYAN;
	else
		*color = BLACK;
}

void	ft_set_tile_color(t_env *doom, int y, int x, Uint32 *color)
{
	char	symb;

	symb = doom->map.data[y * doom->map.nbcol + x];
	if (symb == WALL)
		*color = LIME;
	else if (symb == EMPTY)
		*color = GRAY;
	else if (symb == DOOR || symb == DOOR_OPENED)
		*color = BLUE;
	else if (symb == GRID)
		*color = ORANGE;
	else if (symb == BUTTON_OFF || symb == BUTTON_ON)
		*color = WHITE;
	else if (symb == BARREL)
		*color = BROWN;
	else
		ft_set_tile_color_2(doom, y, x, color);
}

void	ft_set_sdl_minimap_colors(t_env *doom)
{
	if (SDL_SetRenderDrawColor(doom->renderer, 255, 0, 0, 255) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_SetRenderDrawColor()");
	if (SDL_RenderDrawLine(doom->renderer, doom->cam.pos_x * doom->block,
						doom->cam.pos_y * doom->block,
						(doom->cam.pos_x + sin(doom->cam.angle)) * doom->block,
						(doom->cam.pos_y + cos(doom->cam.angle)) *
						doom->block) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_RenderDrawLine()");
	if (SDL_SetRenderDrawColor(doom->renderer, 255, 255, 255, 255) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_SetRenderDrawColor()");
	if (SDL_RenderDrawPoint(doom->renderer, doom->cam.pos_x * doom->block,
						doom->cam.pos_y * doom->block) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_RenderDrawPoint()");
}

void	ft_draw_minimap(t_env *doom)
{
	t_point	pix;
	Uint32	color;
	t_point	map_ptr;

	pix.y = -1;
	while (++pix.y < doom->map.nbl * doom->block)
	{
		pix.x = -1;
		while (++pix.x < doom->map.nbcol * doom->block)
		{
			map_ptr.y = pix.y / doom->block;
			map_ptr.x = pix.x / doom->block;
			ft_set_tile_color(doom, map_ptr.y, map_ptr.x, &color);
			doom->screen_pixels[pix.y * W + pix.x] = color;
		}
	}
}
