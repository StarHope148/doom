/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:51:13 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/28 05:48:04 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_set_new_ray_angle(t_thread_env *e)
{
	e->rc.ray_angle = (e->cam.angle + e->cam.fov / 2.0) -
							((double)e->rc.x_ / (double)W) *
							e->cam.fov;
	e->rc.distance_towall = 0;
	e->rc.eye_x = sin(e->rc.ray_angle);
	e->rc.eye_y = cos(e->rc.ray_angle);
}

void	ft_apply_brightness(t_thread_env *e)
{
	int		shadowing;

	if (e->map.bright[(int)e->cam.pos_y * e ->map.nbcol + (int)e->cam.pos_x] != 3)
	{
		shadowing = e->map.bright[(int)e->cam.pos_y * e->map.nbcol + (int)e->cam.pos_x];
		while (shadowing++ - 3)
		{
			e->screen_pixels[e->rc.y_ * W + e->rc.x_] >>= 1;
			e->screen_pixels[e->rc.y_ * W + e->rc.x_] &=
								0b01111111011111110111111101111111;
		}
	}
}

void	ft_draw_full_column(t_thread_env *e)
{
	e->rc.y_ = -1;
	while (++e->rc.y_ < H)
	{
		if (e->rc.y_ < e->rc.ceiling)
			ft_draw_ceiling(e);
		else if (e->rc.y_ >= e->rc.ceiling &&
				e->rc.y_ <= e->rc.floor)
			ft_draw_wall(e);
		else
			ft_draw_floor(e);
		ft_apply_brightness(e);
	}
}

void	ft_draw_transparent(t_thread_env *e)
{
	e->rc.y_ = 0;
	e->rc.orientation = GRID_XPM;
	while (e->rc.y_ < H)
	{
		if (e->rc.y_ >= e->rc.ceiling && e->rc.y_ <= e->rc.floor)
			ft_draw_wall(e);
		e->rc.y_++;
	}
}

void	ft_fix_fisheye_distorsion(t_thread_env *e)
{
	e->rc.distance_towall *= cos(e->cam.angle - e->rc.ray_angle);
}

void	ft_draw_transparent_textures(t_thread_env *e)
{
	while (e->transparent_found > 0)
	{
		e->transparent_found = 1;
		ft_calc_next_intersection_transparent(e);
		ft_calc_sampling_x(e);
		ft_fix_fisheye_distorsion(e);
		ft_set_ceiling_floor(e);
		ft_draw_transparent(e);
		e->transparent_found--;
	}
}

void	ft_draw_image(t_thread_env *e)
{
	e->obj.screen.y = H / 2;
	//static int test_printf;
	
	e->obj.pos.y = 0;
	while (e->obj.pos.y < e->xpm[BARREL_XPM].h && e->obj.screen.y < H)
	{
		e->obj.pos.x = 0;
		e->obj.screen.x = W / 2;
		while (e->obj.pos.x < e->xpm[BARREL_XPM].w && e->obj.screen.x < W)
		{
			if (e->xpm[BARREL_XPM].pixels[e->obj.pos.y * e->xpm[BARREL_XPM].w + e->obj.pos.x] != MAGENTA)
				e->screen_pixels[e->obj.screen.y * W + e->obj.screen.x] = e->xpm[BARREL_XPM].pixels[e->obj.pos.y * e->xpm[BARREL_XPM].w + e->obj.pos.x];
			e->obj.pos.x++;
			e->obj.screen.x++;
		}
		e->obj.pos.y++;
		e->obj.screen.y++;
	}

	//printf("TEST %d\n", test_printf++);
}

void	ft_draw_objects(t_thread_env *e)
{
	while (e->object_found > 0)
	{
		e->object_found = 1;

		//e->rc.eye_x = sin(e->cam.angle);
		//e->rc.eye_y = cos(e->cam.angle);
		double fVecX = e->obj.pos.x - e->cam.pos_x;
		double fVecY = e->obj.pos.y - e->cam.pos_y;
		double fDistanceFromPlayer = sqrt(fVecX*fVecX + fVecY*fVecY);
		//fDistanceFromPlayer = sqrt(pow(e->obj.pos_x - e->cam.pos_x, 2) + pow(e->obj.pos_y - e->cam.pos_y, 2));
		if (fDistanceFromPlayer <= 2)
		{
			printf("distance too low\n");
			return ;
		}

		// Calculate angle between lamp and players feet, and players looking direction
		// to determine if the lamp is in the players field of view
		double fObjectAngle = atan2(e->rc.eye_y, e->rc.eye_x) - atan2(fVecY, fVecX);
		if (fObjectAngle < -PI)
				fObjectAngle += 2 * PI;
		if (fObjectAngle > PI)
			fObjectAngle -= 2 * PI;

		//printf("obj angle = %f\tcam angle = %f\n", e->obj.angle, e->cam.angle);
		//fObjectAngle = e->obj.angle;			//DEBUG
		double fObjectCeiling = (double)(H / 2) - H / (fDistanceFromPlayer);
		double fObjectFloor = H - fObjectCeiling;
		double fObjectHeight = fObjectFloor - fObjectCeiling;
		double fObjectAspectRatio = (double)e->xpm[BARREL_XPM].h / (double)e->xpm[BARREL_XPM].w;
		double fObjectWidth = fObjectHeight / fObjectAspectRatio;
		double fMiddleOfObject = (0.5 * (fObjectAngle / (e->cam.fov / 2)) + 0.5) * W;
		//fMiddleOfObject = 500;   //DEBUG
		printf("MiddleOfObject = %f\tObjectAngle = %f\tvecX = %f\tvecY = %f\tdistancefromplayer = %f\teye_y = %f\teye_x = %f\n", fMiddleOfObject, fObjectAngle, fVecX, fVecY, fDistanceFromPlayer, e->rc.eye_y, e->rc.eye_x);
		Uint32 color;
		// Draw BARREL
		for (double lx = 0; lx < fObjectWidth; lx++)
		{
			for (double ly = 0; ly < fObjectHeight; ly++)
			{
				double fSampleX = lx / fObjectWidth;
				double fSampleY = ly / fObjectHeight;
				fSampleX = fSampleX * e->xpm[BARREL_XPM].w;
				fSampleY = fSampleY * e->xpm[BARREL_XPM].h;
				int	tmpx = (int)fSampleX;
				int tmpy = (int)fSampleY;
				//if (tmpy * e->xpm[BARREL_XPM].w + tmpx < e->xpm[BARREL_XPM].w * e->xpm[BARREL_XPM].h)
				color = e->xpm[BARREL_XPM].pixels[(int)(tmpy * e->xpm[BARREL_XPM].w + tmpx)];
				int nObjectColumn = (int)(fMiddleOfObject + lx - (fObjectWidth / 2));
				if (nObjectColumn >= 0 && nObjectColumn < W && (((fObjectCeiling + ly) * W + nObjectColumn) < W * H))
					if (color != MAGENTA)
					{
						//Draw(nObjectColumn, fObjectCeiling + ly, color, object.sprite->SampleColour(fSampleX, fSampleY));
						e->screen_pixels[(int)((fObjectCeiling + ly) * W + nObjectColumn)] = color;
						//DepthBuffer[nObjectColumn] = fDistanceFromPlayer;
					}
			}
		}
		//ft_draw_image(e);
		e->obj.type = 0;
		e->object_found--;
		//printf("TEST\n");
	}
}

void	ft_raycaster(t_thread_env *e)
{
	e->rc.x_ = e->x_start - 1;
	while (++e->rc.x_ < e->x_end)
	{
		ft_set_new_ray_angle(e);
		ft_calc_next_intersection(e);
		ft_calc_sampling_x(e);
		ft_fix_fisheye_distorsion(e);
		ft_set_ceiling_floor(e);
		ft_draw_full_column(e);
		ft_draw_transparent_textures(e);
	}
	//ft_draw_objects(e);
	//printf("object found = %d\n", e->object_found);
	//printf("eye_y = %f\teye_x = %f\tpos_y = %f\tpos_x = %f\n", e->rc.eye_y, e->rc.eye_x, e->cam.pos_y, e->cam.pos_x);
}
