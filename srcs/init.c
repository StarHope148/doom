/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 11:55:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/02 19:06:13 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_env(t_env *wolf)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->texture = NULL;
	wolf->screen_pixels = NULL;
	wolf->mapdata.nbcol = 0;
	wolf->mapdata.nbl = 0;
	wolf->mapdata.cur_line = 0;
	wolf->mapdata.map = NULL;
	wolf->cam.pos_x = 0;
	wolf->cam.pos_y = 0;
	wolf->cam.angle = PI / 2;
	wolf->cam.fov = PI / 3;
	wolf->moves.strafe_left = 0;
	wolf->moves.strafe_right = 0;
	wolf->moves.forward = 0;
	wolf->moves.backward = 0;
	wolf->moves.rotate_left = 0;
	wolf->moves.rotate_right = 0;
	wolf->moves.running = 0;
	wolf->moves.crouching = 0;
	wolf->precision = RAY_LENGHT;
	wolf->switch_textures = NON_TEXTURED;
	wolf->block = HEIGHT * 0.01;
	wolf->pitch = 4 * WIDTH;
	wolf->h = HEIGHT;
	wolf->moves.movespeed = MOVE_SPEED;
	wolf->surface_wall_north = NULL;
	wolf->surface_wall_south = NULL;
	wolf->surface_wall_east = NULL;
	wolf->surface_wall_west = NULL;
	if (!(wolf->screen_pixels = (Uint32 *)ft_memalloc(sizeof(Uint32)
								* HEIGHT * WIDTH)))
		ft_exit(wolf, EXIT_FAILURE,
			"Error mallocing screen_pixels in ft_init_env");
}

void	ft_setspawn(t_env *wolf)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (wolf->mapdata.map[y][x] != EMPTY)
	{
		if (y < wolf->mapdata.nbl)
			y++;
		if ((y == wolf->mapdata.nbl) && (x < wolf->mapdata.nbcol))
		{
			y = 1;
			x++;
		}
		if ((y == wolf->mapdata.nbl) && (x == wolf->mapdata.nbcol))
		{
			ft_putendl_fd("This is no map, just a brick wall", 2);
			exit(EXIT_FAILURE);
		}
	}
	wolf->cam.pos_x = x + .5;
	wolf->cam.pos_y = y + .5;
}

void	ft_initialize(t_env *wolf, char *mapfile)
{
	ft_init_env(wolf);
	ft_init_map(wolf, mapfile);
	ft_setspawn(wolf);
}
