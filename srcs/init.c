/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 11:55:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/06 21:58:49 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_env(t_env *wolf)
{
	ft_bzero((void *)wolf, sizeof(t_env));
	ft_bzero((void *)&(wolf->map), sizeof(t_map));
	wolf->cam.angle = PI / 2;
	wolf->cam.fov = PI / 3.5;
	wolf->precision = RAY_LENGHT;
	wolf->wall = SHADED;
	wolf->block = HEIGHT * 0.01;
	wolf->pitch = 4 * WIDTH;
	wolf->h = HEIGHT;
	wolf->fps.time_fps = clock();
	wolf->time0 = clock();
	wolf->music_puls = (double)60 / 117;
	wolf->count_puls = 1;
	wolf->moves.movespeed = MOVE_SPEED;
	if (!(wolf->screen_pixels = (Uint32 *)ft_memalloc(sizeof(Uint32)
								* HEIGHT * WIDTH)))
		ft_exit(wolf, EXIT_FAILURE,
			"Error mallocing screen_pixels in ft_init_env");
}

void	ft_setspawn(t_env *wolf)
{
	int x;
	int y;

	y = 0;
	while (++y < wolf->map.nbl - 1)
	{
		x = 0;
		while (++x < wolf->map.nbcol - 1)
			if (wolf->map.data[y][x] == EMPTY)
			{
				wolf->cam.pos_x = x + 0.5;
				wolf->cam.pos_y = y + 0.5;
				return ;
			}
	}
	ft_putendl_fd("This is no map, just a brick wall", 2);
	exit(EXIT_FAILURE);
}

void	ft_initialize(t_env *wolf, char *mapfile)
{
	ft_init_env(wolf);
	ft_init_map(wolf, mapfile);
	ft_setspawn(wolf);
}
