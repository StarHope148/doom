/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 11:55:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 17:00:20 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_init_env(t_env *doom)
{
	ft_bzero((void *)doom, sizeof(t_env));
	ft_bzero((void *)&(doom->map), sizeof(t_map));
	doom->cam.proj_dist = PROJ_DIST;
	doom->cam.angle = PI / 2;
	doom->cam.pos_z = DEFAULT_POS_Z;
	doom->cam.angle_z = H / 2;
	doom->cam.fov_ratio = FOV_RATIO;
	doom->cam.fov = PI / doom->cam.fov_ratio;
	doom->no_funky = 1;
	doom->wall = TEXTURED;
	doom->block = H * 0.01;
	doom->p = 4 * W;
	doom->music_puls = (double)60 / 116;
	doom->count_puls = 1;
	doom->moves.movespeed = MOVE_SPEED;
	doom->chr.health = PLAYER_MAX_HP;
	ft_init_home_screen(doom);
	ft_init_gun(doom);
	pthread_mutex_init(&doom->shared_data.mutex, 0);
	pthread_cond_init(&doom->shared_data.cond, 0);
	pthread_cond_init(&doom->shared_data.cond_main, 0);
	if (!(doom->screen_pixels = (Uint32 *)ft_memalloc(sizeof(Uint32) * H * W)))
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
			if (doom->map.data[y * doom->map.nbcol + x] == SPAWN)
			{
				if (doom->cam.pos_x != 0 || doom->cam.pos_y != 0)
					ft_exit(doom, EXIT_FAILURE,
						"Please set only 1 SPAWN in map");
				doom->cam.pos_x = x + 0.5;
				doom->cam.pos_y = y + 0.5;
			}
	}
	if (doom->cam.pos_x == 0 || doom->cam.pos_y == 0)
		ft_exit(doom, EXIT_FAILURE, "Please add a SPAWN in map");
}

void	ft_initialize(t_env *doom, char *mapfile, unsigned char editor)
{
	ft_init_env(doom);
	ft_init_map(doom, mapfile);
	if (editor == FALSE)
		ft_setspawn(doom);
	ft_count_objects(doom);
}
