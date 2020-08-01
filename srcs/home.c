/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 05:16:18 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 07:11:19 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_home_event(t_env *doom)
{
	if (doom->event.type == SDL_QUIT)
		ft_exit(doom, EXIT_SUCCESS, NULL);
	if (doom->event.key.keysym.sym == SDLK_ESCAPE)
		ft_exit(doom, EXIT_SUCCESS, NULL);
	if (doom->event.key.keysym.sym == SDLK_RETURN)
		doom->home.in_menu = FALSE;
}

void		ft_init_home_screen(t_env *doom)
{
	doom->home.in_menu = TRUE;
	doom->home.h_ = H;
	doom->home.w_ = W;
	doom->home.y_ = 0;
	doom->home.x_ = 0;
	doom->enter.h_ = 150;
	doom->enter.w_ = 500;
	doom->enter.y_ = H * 0.8;
	doom->enter.x_ = W / 2 - doom->enter.w_ / 2;
}

void		ft_draw_press_enter(t_env *doom)
{
	t_point			delta;
	t_point			sample;
	unsigned int	y_;
	unsigned int	x_;
	t_xpm			*x;

	x = &doom->xpm[PRESS_ENTER_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1)
		return ;
	delta.y = -1;
	while (++delta.y < doom->enter.h_)
	{
		delta.x = -1;
		while (++delta.x < doom->enter.w_)
		{
			sample.y = delta.y * x->h / doom->enter.h_;
			sample.x = delta.x * x->w / doom->enter.w_;
			y_ = doom->enter.y_ + delta.y;
			x_ = doom->enter.x_ + delta.x;
			if (sample.y * x->w + sample.x < x->w * x->h && x->pixels[sample.y
				* x->w + sample.x] != MAGENTA && y_ * W + x_ < W * H && x_ < W)
				doom->screen_pixels[y_ * W + x_] =
										x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		ft_draw_home(t_env *doom)
{
	t_point			delta;
	t_point			sample;
	unsigned int	y_;
	unsigned int	x_;
	t_xpm			*x;

	x = &doom->xpm[HOME_XPM];
	if (!x || !x->pixels || x->w < 1 || x->h < 1)
		return ;
	delta.y = -1;
	while (++delta.y < doom->home.h_)
	{
		delta.x = -1;
		while (++delta.x < doom->home.w_)
		{
			sample.y = delta.y * x->h / doom->home.h_;
			sample.x = delta.x * x->w / doom->home.w_;
			y_ = doom->home.y_ + delta.y;
			x_ = doom->home.x_ + delta.x;
			if (sample.y * x->w + sample.x < x->w * x->h && y_ * W + x_ < W *
					H && x_ < W)
				doom->screen_pixels[y_ * W + x_] =
										x->pixels[sample.y * x->w + sample.x];
		}
	}
}

void		ft_home_screen(t_env *doom)
{
	static int		duration;

	while (doom->home.in_menu == TRUE)
	{
		ft_draw_home(doom);
		if (duration <= 50)
			ft_draw_press_enter(doom);
		if (duration >= 100)
			duration = 0;
		while (SDL_PollEvent(&doom->event))
			ft_home_event(doom);
		ft_update_screen(doom);
		if ((SDL_UpdateTexture(doom->texture, NULL,
					doom->screen_pixels,
					doom->p)) < 0)
			ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
		duration++;
	}
}
