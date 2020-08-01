/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:05 by czhang            #+#    #+#             */
/*   Updated: 2020/08/01 19:34:18 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_cursor(t_env *e, t_point pos)
{
	t_xpm	*x;
	t_point	start;
	t_point	d;
	t_point	sp;
	Uint32	color;

	x = &e->xpm[CURSOR_XPM];
	start.y = pos.y * H / e->map.nbl;
	start.x = pos.x * W / e->map.nbcol;
	d.y = -1;
	while (++d.y < (double)H / e->map.nbl)
	{
		d.x = -1;
		while (++d.x < (double)W / e->map.nbcol)
		{
			sp.y = x->h * d.y * e->map.nbl / (double)H;
			sp.x = x->w * d.x * e->map.nbcol / (double)W;
			color = x->pixels[sp.y * x->w + sp.x];
			if (color != MAGENTA)
				e->screen_pixels[(start.y + d.y) * W + start.x + d.x] = color;
		}
	}
}

void	editor_key2(t_env *doom, t_point *pos, SDL_Keycode key)
{
	if (key == SDLK_y)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = BUTTON_OFF;
	if (key == SDLK_h)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = BUTTON_ON;
	if (key == SDLK_r)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = DOOR_OPENED;
	if (key == SDLK_p)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = HEALTH_POTION;
	if (key == SDLK_k)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = KEY;
	if (key == SDLK_t)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = TORCH;
	if (key == SDLK_s)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = STATUE;
	if (key == SDLK_e)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = END_CASE;
	if (key == SDLK_a)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = SPAWN;
	if (key == SDLK_RETURN)
	{
		ft_putendl("saved in new.map");
		save_in_file(doom);
	}
	if (key == SDLK_ESCAPE)
		ft_exit(doom, EXIT_SUCCESS, NULL);
}

void	editor_key(t_env *doom, t_point *pos)
{
	SDL_Keycode	key;

	key = doom->event.key.keysym.sym;
	if (key == SDLK_UP && pos->y > 1)
		pos->y--;
	if (key == SDLK_LEFT && pos->x > 1)
		pos->x--;
	if (key == SDLK_DOWN && pos->y < doom->map.nbl - 2)
		pos->y++;
	if (key == SDLK_RIGHT && pos->x < doom->map.nbcol - 2)
		pos->x++;
	if (key == SDLK_w)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = WALL;
	if (key == SDLK_SPACE)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = EMPTY;
	if (key == SDLK_d)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = DOOR;
	if (key == SDLK_o)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = OBJECT;
	if (key == SDLK_g)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = GRID;
	if (key == SDLK_b)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = BARREL;
	editor_key2(doom, pos, key);
}

void	editor_map(t_env *doom)
{
	t_point	pix;
	Uint32	color;
	t_point	map_ptr;

	pix.y = -1;
	while (++pix.y < H)
	{
		pix.x = -1;
		while (++pix.x < W)
		{
			map_ptr.y = pix.y * doom->map.nbl / H;
			map_ptr.x = pix.x * doom->map.nbcol / W;
			ft_set_tile_color(doom, map_ptr.y, map_ptr.x, &color);
			doom->screen_pixels[pix.y * W + pix.x] = color;
		}
	}
}
