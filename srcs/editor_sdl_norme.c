/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sdl_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thparlos <thparlos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:25:20 by thparlos          #+#    #+#             */
/*   Updated: 2020/08/01 20:17:37 by thparlos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		editor_key_norme(t_env *doom, t_point *pos)
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
}

void		editor_key_norme2(t_env *doom, t_point *pos)
{
	SDL_Keycode	key;

	key = doom->event.key.keysym.sym;
	if (key == SDLK_g)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = GRID;
	if (key == SDLK_b)
		doom->map.data[pos->y * doom->map.nbcol + pos->x] = BARREL;
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
}
