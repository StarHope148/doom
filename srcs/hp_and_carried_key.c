/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_and_carried_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 10:21:21 by czhang            #+#    #+#             */
/*   Updated: 2020/07/31 10:23:00 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_only_bar(t_env *e)
{
	t_point			delta;
	t_point			sample;
	t_xpm			*x;

	x = &e->xpm[HEALTHBAR_XPM];
	delta.y = -1;
	while (++delta.y < e->hp.size.y)
	{
		delta.x = -1;
		while (++delta.x < e->hp.size.x)
		{
			sample.y = delta.y * x->h / e->hp.size.y;
			sample.x = delta.x * x->w / e->hp.size.x;
			if (x->pixels[sample.y * x->w + sample.x] != MAGENTA)
				e->screen_pixels[(e->hp.y_ + delta.y) * W + delta.x] =
									x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		draw_hp(t_env *e)
{
	t_xpm			*x;
	t_point			delta;

	x = &e->xpm[HEALTHBAR_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1 || e->hp.size.x >= W
			|| e->hp.y_ + e->hp.size.y * W + e->hp.size.x >= W * H)
		return ;
	delta.y = e->hp.start_red.y;
	e->hp.current_red_x = (e->hp.max_red.x - e->hp.start_red.x)
												* e->chr.health / 100;
	while (++delta.y < e->hp.max_red.y)
	{
		delta.x = -1;
		while (++delta.x < e->hp.current_red_x)
			e->screen_pixels[(e->hp.y_ + delta.y) * W
										+ delta.x + e->hp.start_red.x] = RED;
	}
	draw_only_bar(e);
}

void		draw_carried_key(t_env *e)
{
	t_point			delta;
	t_point			sample;
	t_xpm			*x;

	if (!e->chr.carried_key)
		return ;
	x = &e->xpm[KEY_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1 || e->key.size.x >= W
			|| e->key.y_ + e->key.size.y * W + e->key.size.x >= W * H)
		return ;
	delta.y = -1;
	while (++delta.y < e->key.size.y)
	{
		delta.x = -1;
		while (++delta.x < e->key.size.x)
		{
			sample.y = delta.y * x->h / e->key.size.y;
			sample.x = delta.x * x->w / e->key.size.x;
			if (x->pixels[sample.y * x->w + sample.x] != MAGENTA)
				e->screen_pixels[(e->key.y_ + delta.y) * W + delta.x] =
									x->pixels[sample.y * x->w + sample.x];
		}
	}
}
