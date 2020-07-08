/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/08 21:31:19 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_exit(t_env *doom, int exit_type, char *message)
{
	printf("time ~ from SDL_Init() : %f\n", get_time(doom));
	ft_free_surface_image(doom);
	ft_destroy_texture_renderer_window(doom);
	ft_memdel((void **)&doom->screen_pixels);
	Mix_FreeMusic(doom->music);
	TTF_CloseFont(doom->txt.font);
	SDL_FreeSurface(doom->txt.welcome1);
	SDL_FreeSurface(doom->txt.welcome2);
	SDL_FreeSurface(doom->fps.s);
	TTF_Quit();
	//ft_putendl("next step is SDL_Quit()");
	SDL_Quit();
	//ft_putendl("SDL_Quit accomplished");
	ft_free_door(doom->door);
	ft_free_map(&doom->map);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	printf("time : %f\n", get_time(doom) + doom->time0 / CLOCKS_PER_SEC);
	exit(exit_type);
}

void	ft_load_surface(t_env *doom, char *image_file, SDL_Surface **dest)
{
	SDL_Surface	*tmp;

	tmp = NULL;
	tmp = SDL_LoadBMP(image_file);
	if (tmp == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_LoadBMP()");
	*dest = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 1);
	SDL_FreeSurface(tmp);
	if (*dest == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_ConvertSurfaceFormat()");
}

void	ft_init_video(t_env *doom)
{
	doom->window = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (doom->window == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateWindow()");
	doom->renderer = SDL_CreateRenderer(doom->window, -1,
										SDL_RENDERER_SOFTWARE);
	if (doom->renderer == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateRenderer()");
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (doom->texture == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_CreateTexture()");
	ft_load_surface(doom, "textures/risitas_wall.bmp",
					&(doom->surface_wall_north));
	ft_load_surface(doom, "textures/panda_wall.bmp",
					&(doom->surface_wall_south));
	ft_load_surface(doom, "textures/orange_wall.bmp",
					&(doom->surface_wall_east));
	ft_load_surface(doom, "textures/green_wall.bmp",
					&(doom->surface_wall_west));
	ft_load_surface(doom, "textures/floor.bmp",
					&(doom->surface_floor));
}

void	ft_init_musicttf(t_env *doom)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
 		ft_exit(doom, EXIT_FAILURE, "Error in Mix_OpenAudio");
	if ((doom->music = Mix_LoadMUS("yaeji-raingurl.mp3")) == NULL)
		ft_exit(doom, EXIT_FAILURE, (char *)SDL_GetError());
	//Mix_PlayMusic(doom->music, -1);
	if (TTF_Init() < 0)
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_Init()");
	if ((doom->txt.font = TTF_OpenFont("arial.ttf", 40)) == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_OpenFont()");
	if (!(doom->txt.welcome1 = TTF_RenderText_Blended(doom->txt.font,
				" Hello stranger ! Welcome to... ", doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
	if (!(doom->txt.welcome2 = TTF_RenderText_Blended(doom->txt.font,
				" The funkiest Doom Nukem ! ", doom->txt.black)))
		ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
}

void	ft_sdl(t_env *doom)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_Init()");
	ft_init_video(doom);
	ft_init_musicttf(doom);
	doom->time0 = clock();
	while (1)
	{
		ft_print(doom);
		while (SDL_PollEvent(&doom->event))
		{
			if (doom->event.type == SDL_KEYDOWN)
				ft_key_pressed(doom);
			if (doom->event.type == SDL_KEYUP)
				ft_key_released(doom);
			if (doom->event.type == SDL_QUIT)
				ft_exit(doom, EXIT_SUCCESS, NULL);
		}
		ft_refresh_new_pos(doom);
	}
	ft_exit(doom, EXIT_SUCCESS, NULL);
}
