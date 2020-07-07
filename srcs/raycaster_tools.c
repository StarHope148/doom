/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 19:52:22 by jcanteau         ###   ########.fr       */
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
	//doom->screen_pixels[doom->raycast.y_render * WIDTH +
	//	doom->raycast.x_render] = ft_rgba_to_uint32(0,
	//											255 *
	//											((doom->raycast.y_render -
	//											doom->h * 0.5) /
	//											doom->h),
	//											0,
	//											0);
	doom->screen_pixels[doom->raycast.y_render * WIDTH +
		doom->raycast.x_render] = OLIVE;
	
	/* 
	// positions X et Y du texel du sol au bas du mur
	int floorXWall;
	int floorYWall;
	
	double weight;// coefficient de pondération
	double currentFloorX;// position du pixel sur X
	double currentFloorY;// position du pixel sur Y
	int floorTexX;// position du texel sur X
	int floorTexY;// position du texel sur Y
	double distWall = doom->raycast.distance_towall;// distance du mur
	double distPlayer = 0;// distance de la caméra
	double currentDist = 0;// point de départ de la texture
	
	//Le mur peut être orienté de 4 manières
	if (doom->ray.side == 0 && doom->raycast.eye_x > 0) {
		// nord
		floorXWall = (int)doom->cam.pos_x;
		floorYWall = (int)doom->cam.pos_y + doom->raycast.x_render;
	} else if (doom->ray.side == 0 && doom->raycast.eye_x < 0) {
		// sud
		floorXWall = (int)doom->cam.pos_x + 1.0;
		floorYWall = (int)doom->cam.pos_y + doom->raycast.x_render;
	} else if (doom->ray.side == 1 && doom->raycast.eye_y > 0) {
		// est
		floorXWall = (int)doom->cam.pos_x + doom->raycast.x_render;
		floorYWall = (int)doom->cam.pos_y;
	} else {
		// ouest
		floorXWall = (int)doom->cam.pos_x + doom->raycast.x_render;
		floorYWall = (int)doom->cam.pos_y + 1.0;
	}
	
	//trace le sol de drawEnd au bas de l'écran
	while (doom->raycast.y_render < HEIGHT) {
	
		int divise = 2 * doom->raycast.y_render - HEIGHT;
		if (divise == 0)
			divise = 1;
		currentDist = HEIGHT / divise;// distance
		//currentDist = 1;
		weight = (currentDist - distPlayer) / (distWall - distPlayer);// coef
		currentFloorX = weight * floorXWall + (1.0 - weight) * doom->cam.pos_x;// position sur X
		currentFloorY = weight * floorYWall + (1.0 - weight) * doom->cam.pos_y;// position sur Y
		floorTexX = (int)(currentFloorX * doom->surface_floor->w) % doom->surface_floor->w;// position texel sur X
		floorTexY = (int)(currentFloorY * doom->surface_floor->h) % doom->surface_floor->h;// position texel sur Y

		//floorTexX = 10;
		//floorTexY = 10;
		doom->screen_pixels[doom->raycast.y_render *
			WIDTH + doom->raycast.x_render] =
				doom->pixels_floor[floorTexY * doom->surface_floor->w + floorTexX];// trace le sol 
		//screen.setPixel(x,h-y-1,textures[2][floorTexX][floorTexY]);// trace le plafond
		doom->raycast.y_render++;
	}
	 */
}
