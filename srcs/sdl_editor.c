/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:27:01 by czhang            #+#    #+#             */
/*   Updated: 2020/07/31 23:58:29 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_init_video(t_env *doom)
{
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

void	sdl_editor(t_env *doom)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_Init()");
	editor_init_video(doom);
	clock_gettime(_POSIX_MONOTONIC_CLOCK, &doom->time0);
	while (1)
	{
		ft_draw_minimap(doom);
		SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
		ft_set_sdl_minimap_colors(doom);
		SDL_RenderPresent(doom->renderer);
		if ((SDL_UpdateTexture(doom->texture, NULL,
					doom->screen_pixels,
					doom->pitch)) < 0)
			ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
		while (SDL_PollEvent(&doom->event))
			ft_key_hook(doom);
		ft_refresh_new_pos(doom);
	}
	ft_exit(doom, EXIT_SUCCESS, NULL);
}

void	editor(char *mapfile)
{
	t_env doom;

	ft_initialize(&doom, mapfile);
	sdl_editor(&doom);
}
