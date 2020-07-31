/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 22:54:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 00:21:36 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_reset_view(t_env *doom)
{
	doom->cam.fov_ratio = FOV_RATIO;
	doom->cam.fov = PI / doom->cam.fov_ratio;
	doom->cam.proj_dist = PROJ_DIST;
	doom->cam.angle_z = H / 2;
}

void		ft_change_fov_horizontal(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_KP_PLUS)
	{
		if (doom->cam.fov_ratio - FOV_RATIO_STEP >= 2)
			doom->cam.fov_ratio -= FOV_RATIO_STEP;
		doom->cam.fov = PI / doom->cam.fov_ratio;
	}
	else if (doom->event.key.keysym.sym == SDLK_KP_MINUS)
	{
		if (doom->cam.fov_ratio + FOV_RATIO_STEP <= 6)
			doom->cam.fov_ratio += FOV_RATIO_STEP;
		doom->cam.fov = PI / doom->cam.fov_ratio;
	}
}

void		ft_change_fov_vertical(t_env *doom)
{
	if (doom->event.key.keysym.sym == SDLK_KP_9)
	{
		if (doom->cam.proj_dist / PROJ_DIST_STEP <= MAX_PROJ_DIST)
			doom->cam.proj_dist /= PROJ_DIST_STEP;
	}
	else if (doom->event.key.keysym.sym == SDLK_KP_6)
	{
		if (doom->cam.proj_dist * PROJ_DIST_STEP >= MIN_PROJ_DIST)
			doom->cam.proj_dist *= PROJ_DIST_STEP;
	}
}

void		ft_settings_controls(t_env *doom)
{
	ft_change_fov_horizontal(doom);
	ft_change_fov_vertical(doom);
	if (doom->event.key.keysym.sym == SDLK_KP_5)
		ft_reset_view(doom);
	else if (doom->event.key.keysym.sym == SDLK_t)
		doom->wall = doom->wall == TEXTURED ? NON_TEXTURED : doom->wall + 1;
	else if (doom->event.key.keysym.sym == SDLK_RSHIFT)
	{
		doom->no_funky = 1;
		doom->wall = TEXTURED;
	}
}
