/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 17:56:04 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_init_video(t_env *doom)
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
	ft_load_textures(doom);
	init_pthread(doom);
}

void	ft_init_musicttf(t_env *doom)
{
	ft_fmod(doom);
	if (TTF_Init() < 0)
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_Init()");
	if ((doom->txt.font = TTF_OpenFont("arial.ttf", 40)) == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_OpenFont()");
	if (!(doom->txt.welcome1 = TTF_RenderText_Blended(doom->txt.font,
			" Welcome to Doom Nukem ! ", doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
	if (!(doom->txt.objectif = TTF_RenderText_Blended(doom->txt.font,
			" Reach MAGENTA tile to win this level !",
			doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
	if (!(doom->txt.end_level = TTF_RenderText_Blended(doom->txt.font,
			" Congratulation, you finished the game ! ", doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE,
			"Error in TTF_RenderText_Blended() for end_level");
	if (!(doom->txt.dead = TTF_RenderText_Blended(doom->txt.font,
			" You should be dead, but we made you immortal ! ",
			doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
}

void	init_bar(t_env *e)
{
	t_xpm			*x;

	x = &e->xpm[HEALTHBAR_XPM];
	e->hp.size.x = e->map.nbcol * e->block * 0.9;
	e->hp.size.y = x->h * e->hp.size.x / x->w;
	e->hp.y_ = (e->map.nbl + 1) * e->block;
	e->hp.max_red.y = e->hp.size.y * 7 / 8;
	e->hp.max_red.x = e->hp.size.x * 89 / 90;
	e->hp.start_red.y = e->hp.size.y / 8;
	e->hp.start_red.x = e->hp.size.x * 8 / 45;
}

void	init_carried_key(t_env *e)
{
	t_xpm	*x;

	x = &e->xpm[KEY_XPM];
	e->key.size.x = e->hp.size.x * 4 / 5;
	e->key.size.y = x->h * e->key.size.x / x->w;
	e->key.y_ = e->hp.y_ + e->hp.size.y;
}

void	ft_sdl(t_env *doom)
{
	ft_init_video(doom);
	ft_init_musicttf(doom);
	init_bar(doom);
	init_carried_key(doom);
	ft_home_screen(doom);
	if ((FMOD_System_PlaySound(doom->sound.system, doom->sound.music, NULL, 0,
			&doom->sound.channel_music)) != FMOD_OK)
		perror("Error in FMOD_System_PlaySound for music ");
	clock_gettime(_POSIX_MONOTONIC_CLOCK, &doom->time0);
	while (1)
	{
		ft_print(doom);
		while (SDL_PollEvent(&doom->event))
			ft_key_hook(doom);
		ft_refresh_new_pos(doom);
	}
	ft_exit(doom, EXIT_SUCCESS, NULL);
}
