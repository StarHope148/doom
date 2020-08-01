/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 08:42:10 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 17:30:15 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_firing_anim(t_env *doom)
{
	static int	duration = 0;

	if (doom->gun.firing == TRUE)
	{
		duration++;
		if (duration == 5)
		{
			doom->gun.firing = FALSE;
			duration = 0;
		}
	}
}

void		ft_init_gun(t_env *doom)
{
	doom->gun.h_ = 350;
	doom->gun.w_ = 400;
	doom->gun.x_ = W / 2 - doom->gun.w_ * 0.35;
}

int			ft_choose_gun_mode(t_env *doom)
{
	if (doom->gun.firing == FALSE)
		return (GUN_XPM);
	else
		return (GUN_FIRING_XPM);
}

int			ft_init_draw_gun(t_env *doom)
{
	int				id;

	id = ft_choose_gun_mode(doom);
	if (id == GUN_XPM)
	{
		doom->gun.h_ = 350;
		doom->gun.y_ = H - doom->gun.h_;
	}
	else
	{
		doom->gun.h_ = 420;
		doom->gun.y_ = H - doom->gun.h_;
	}
	return (id);
}

void		ft_draw_gun(t_env *doom)
{
	t_point			delta;
	t_point			sample;
	unsigned int	y_;
	unsigned int	x_;
	t_xpm			*x;

	x = &doom->xpm[ft_init_draw_gun(doom)];
	if (!x || !x->pixels || x->w < 1 || x->h < 1)
		return ;
	delta.y = -1;
	while (++delta.y < doom->gun.h_)
	{
		delta.x = -1;
		while (++delta.x < doom->gun.w_)
		{
			sample.y = delta.y * x->h / doom->gun.h_;
			sample.x = delta.x * x->w / doom->gun.w_;
			y_ = doom->gun.y_ + delta.y;
			x_ = doom->gun.x_ + delta.x;
			if (sample.y * x->w + sample.x < x->w * x->h && x->pixels[sample.y
				* x->w + sample.x] != MAGENTA && y_ * W + x_ < W * H && x_ < W)
				doom->screen_pixels[y_ * W + x_] =
										x->pixels[sample.y * x->w + sample.x];
		}
	}
}
