/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/08 11:10:27 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	ft_darken_color(unsigned int color, double coeff)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	// FF 00 00 00
	// 00 FF 00 00
	color >>= 8;
	b = (unsigned char)color * coeff;
	color >>= 8;
	g = (unsigned char)color * coeff;
	color >>= 8;
	r = (unsigned char)color * coeff;
	return (ft_rgba_to_uint32(r, g, b, 0));
}

void			ft_fix_fisheye_distorsion(t_env *doom)
{
	doom->raycast.distance_towall *= cos(doom->cam.angle -
											doom->raycast.ray_angle);
}

void			ft_set_ceiling_floor(t_env *doom)
{
	doom->ceiling = (double)(doom->h * 0.5) - (double)doom->h /
					doom->raycast.distance_towall * WALL_SIZE;
	doom->floor = doom->h - doom->ceiling;
	doom->ceiling -= (doom->map.alt[doom->raycast.test_y]
			[doom->raycast.test_x]) / doom->raycast.distance_towall;
	doom->ceiling += doom->cam.angle_z;
	doom->floor += doom->cam.angle_z;
}

void	ft_draw_ceiling(t_env *doom)
{
	doom->screen_pixels[doom->raycast.y_render *
		WIDTH + doom->raycast.x_render] = DODGER_BLUE;
}

void	ft_draw_wall(t_env *doom)
{
	if (doom->map.data
				[(int)doom->raycast.test_y][(int)doom->raycast.test_x] == 'D')
		ft_apply_textured_wall(doom);
	else if (doom->wall == TEXTURED)
		ft_apply_textured_wall(doom);
	else if (doom->wall == COLOR_ORIENTED)
		ft_apply_color_oriented_wall(doom);
	else if (doom->wall == SHADED)
		ft_apply_shaded_wall(doom);
	else
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] = WHITE;
}

void	ft_draw_floor(t_env *doom)
{
	double floorXWall, floorYWall;
	
	// 4 possibili direzioni del muro
	if (doom->ray.side == 0 && doom->raycast.eye_x > 0)
	{
		floorXWall = (int)doom->cam.pos_x;
		floorYWall = (int)doom->cam.pos_y + doom->calc.sample_x;
	}
	else if (doom->ray.side == 0 && doom->raycast.eye_x < 0)
	{
		floorXWall = (int)doom->cam.pos_x + 1.0;
		floorYWall = (int)doom->cam.pos_y + doom->calc.sample_x;
	}
	else if (doom->ray.side == 1 && doom->raycast.eye_y > 0)
	{
		floorXWall = (int)doom->cam.pos_x + doom->calc.sample_x;
		floorYWall = (int)doom->cam.pos_y;
	}
	else
	{
		floorXWall = (int)doom->cam.pos_x + doom->calc.sample_x;
		floorYWall = (int)doom->cam.pos_y + 1.0;
	}
	
	double distWall, distPlayer, currentDist;
	distWall = doom->raycast.distance_towall;
	distPlayer = 0.0;
	
	// disegna pavimento e soffitto
	uint32_t colh = abs((int)(HEIGHT / doom->raycast.distance_towall));
	uint32_t c = (colh + HEIGHT) / 2;
	//if (doom->moves.forward)
	//	printf("%d\n", c);
	
	while (c < HEIGHT) // per ogni pixel al di sotto della colonna muro
	{
		// calcola la distanza
		currentDist = HEIGHT / (2.0 * c - HEIGHT);
		double weight = (currentDist - distPlayer) / (distWall - distPlayer);
	
		// calcola il punto X,Y nel blocco corrente
		double currentFloorX = weight * floorXWall + (1.0 - weight) * doom->cam.pos_x;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * doom->cam.pos_y;
		
		// calcola il punto X,Y nella texture del pavimento
		int floorTexX, floorTexY;
		floorTexX = (int)(currentFloorX * 512) % 512;
		floorTexY = (int)(currentFloorY * 512) % 512;
		
		// pixel di pavimento (relativo alla colonna column)
		Uint32 color = doom->pixels_floor[floorTexX + floorTexY * 512];
		if ((doom->raycast.y_render * WIDTH + doom->raycast.x_render) < WIDTH * HEIGHT)
			doom->screen_pixels[doom->raycast.y_render * WIDTH +
				doom->raycast.x_render] = color;
		doom->raycast.y_render++;
		c++;
	}
}
