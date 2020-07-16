/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 11:55:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/14 03:23:08 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_init_env(t_env *doom)
{
	ft_bzero((void *)doom, sizeof(t_env));
	ft_bzero((void *)&(doom->map), sizeof(t_map));
	doom->cam.angle = PI / 2;
	doom->cam.pos_z = 1;
	doom->cam.fov_ratio = 4;
	doom->cam.fov = PI / doom->cam.fov_ratio;
	doom->wall = SHADED;
	doom->block = HEIGHT * 0.01;
	doom->pitch = 4 * WIDTH;
	doom->h = HEIGHT;
	doom->fps.time_fps = clock();
	doom->music_puls = (double)60 / 116;
	doom->count_puls = 1;
	doom->moves.movespeed = MOVE_SPEED;
	if (!(doom->screen_pixels = (Uint32 *)ft_memalloc(sizeof(Uint32)
								* HEIGHT * WIDTH)))
		ft_exit(doom, EXIT_FAILURE,
			"Error mallocing screen_pixels in ft_init_env");
}

void	ft_setspawn(t_env *doom)
{
	int x;
	int y;

	y = 0;
	while (++y < doom->map.nbl - 1)
	{
		x = 0;
		while (++x < doom->map.nbcol - 1)
			if (doom->map.data[y][x] == EMPTY)
			{
				doom->cam.pos_x = x + 0.5;
				doom->cam.pos_y = y + 0.5;
				return ;
			}
	}
	ft_putendl_fd("This is no map, just a brick wall", 2);
	exit(EXIT_FAILURE);
}

void	ft_initialize(t_env *doom, char *mapfile)
{
	ft_init_env(doom);
	ft_init_map(doom, mapfile);
	ft_setspawn(doom);
}
