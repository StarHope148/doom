/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thparlos <thparlos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:27:01 by czhang            #+#    #+#             */
/*   Updated: 2020/08/01 20:15:51 by thparlos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_init_video(t_env *doom)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_Init()");
	doom->window = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, 0);
	if (doom->window == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateWindow()");
	doom->renderer = SDL_CreateRenderer(doom->window, -1,
										SDL_RENDERER_SOFTWARE);
	if (doom->renderer == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateRenderer()");
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_STREAMING, W, H);
	if (doom->texture == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateTexture()");
}

void	editor_cursor(t_env *e, t_point pos)
{
	t_xpm	*x;
	t_point	start;
	t_point	d;
	t_point	sp;
	Uint32	color;

	x = &e->xpm[CURSOR_XPM];
	start.y = pos.y * H / e->map.nbl;
	start.x = pos.x * W / e->map.nbcol;
	d.y = -1;
	while (++d.y < (double)H / e->map.nbl)
	{
		d.x = -1;
		while (++d.x < (double)W / e->map.nbcol)
		{
			sp.y = x->h * d.y * e->map.nbl / (double)H;
			sp.x = x->w * d.x * e->map.nbcol / (double)W;
			color = x->pixels[sp.y * x->w + sp.x];
			if (color != MAGENTA)
				e->screen_pixels[(start.y + d.y) * W + start.x + d.x] = color;
		}
	}
}

void	editor_key(t_env *doom, t_point *pos)
{
	SDL_KeyCode	key;

	key = doom->event.key.keysym.sym;
	editor_key_norme(doom, pos);
	editor_key_norme2(doom, pos);
	if (key == SDLK_RETURN)
	{
		ft_putendl("saved in new.map");
		save_in_file(doom);
	}
	if (key == SDLK_ESCAPE)
		ft_exit(doom, EXIT_SUCCESS, NULL);
}

void	sdl_editor(t_env *doom)
{
	t_point	pos;

	pos.x = 1;
	pos.y = 1;
	editor_init_video(doom);
	clock_gettime(_POSIX_MONOTONIC_CLOCK, &doom->time0);
	while (1)
	{
		editor_map(doom);
		editor_cursor(doom, pos);
		SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
		SDL_RenderPresent(doom->renderer);
		if (SDL_UpdateTexture(doom->texture, 0, doom->screen_pixels, doom->p))
			ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
		while (SDL_PollEvent(&doom->event))
		{
			if (doom->event.type == SDL_QUIT)
				ft_exit(doom, EXIT_SUCCESS, NULL);
			if (doom->event.type == SDL_KEYDOWN)
				editor_key(doom, &pos);
		}
	}
	ft_exit(doom, EXIT_SUCCESS, NULL);
}

void	editor(char *mapfile)
{
	t_env doom;

	ft_initialize(&doom, mapfile, TRUE);
	if ((get_xpm("textures/cursor.xpm", &doom.xpm[CURSOR_XPM])) != 0)
		ft_exit(&doom, EXIT_FAILURE, "Error in get_xpm() for cursor.xpm");
	sdl_editor(&doom);
}
