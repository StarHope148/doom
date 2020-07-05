/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 20:44:08 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_env *wolf, int exit_type, char *message)
{
	printf("time : %f\n", get_time(wolf));
	ft_free_surface_image(wolf);
	ft_destroy_texture_renderer_window(wolf);
	ft_memdel((void **)&wolf->screen_pixels);
	Mix_FreeMusic(wolf->music);
	TTF_CloseFont(wolf->txt.font);
	SDL_FreeSurface(wolf->txt.welcome1);
	SDL_FreeSurface(wolf->txt.welcome2);
	SDL_FreeSurface(wolf->fps.s);
	TTF_Quit();
	//ft_putendl("next step is SDL_Quit()");
	SDL_Quit();
	//ft_putendl("SDL_Quit accomplished");
	ft_free_map(&wolf->map);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	exit(exit_type);
}

void	ft_load_surface(t_env *wolf, char *image_file, SDL_Surface **dest)
{
	SDL_Surface	*tmp;

	tmp = NULL;
	tmp = SDL_LoadBMP(image_file);
	if (tmp == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_LoadBMP()");
	*dest = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 1);
	SDL_FreeSurface(tmp);
	if (*dest == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_ConvertSurfaceFormat()");
}

void	ft_init_video(t_env *wolf)
{
	wolf->window = SDL_CreateWindow("WOLF3D", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (wolf->window == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateWindow()");
	wolf->renderer = SDL_CreateRenderer(wolf->window, -1,
										SDL_RENDERER_ACCELERATED);
	if (wolf->renderer == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateRenderer()");
	wolf->texture = SDL_CreateTexture(wolf->renderer, SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (wolf->texture == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateTexture()");
	ft_load_surface(wolf, "textures/risitas_wall.bmp",
					&(wolf->surface_wall_north));
	ft_load_surface(wolf, "textures/panda_wall.bmp",
					&(wolf->surface_wall_south));
	ft_load_surface(wolf, "textures/orange_wall.bmp",
					&(wolf->surface_wall_east));
	ft_load_surface(wolf, "textures/green_wall.bmp",
					&(wolf->surface_wall_west));
}

void	ft_init_musicttf(t_env *wolf)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
 		ft_exit(wolf, EXIT_FAILURE, "Error in Mix_OpenAudio");
	if ((wolf->music = Mix_LoadMUS("yaeji-raingurl.mp3")) == NULL)
		ft_exit(wolf, EXIT_FAILURE, (char *)SDL_GetError());
	Mix_PlayMusic(wolf->music, -1);
	if (TTF_Init() < 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in TTF_Init()");
	if ((wolf->txt.font = TTF_OpenFont("arial.ttf", 40)) == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in TTF_OpenFont()");
	if (!(wolf->txt.welcome1 = TTF_RenderText_Blended(wolf->txt.font,
				" Hello stranger ! Welcome to... ", wolf->txt.black)))
		ft_exit(wolf, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
	if (!(wolf->txt.welcome2 = TTF_RenderText_Blended(wolf->txt.font,
				" The funkiest Doom Nukem ! ", wolf->txt.black)))
		ft_exit(wolf, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
}

void	ft_sdl(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_Init()");
	ft_init_video(wolf);
	ft_init_musicttf(wolf);
	while (1)
	{
		ft_print(wolf);
		while (SDL_PollEvent(&wolf->event))
		{
			if (wolf->event.type == SDL_KEYDOWN)
				ft_key_pressed(wolf);
			if (wolf->event.type == SDL_KEYUP)
				ft_key_released(wolf);
			if (wolf->event.type == SDL_QUIT)
				ft_exit(wolf, EXIT_SUCCESS, NULL);
		}
		ft_refresh_new_pos(wolf);
	}
	ft_exit(wolf, EXIT_SUCCESS, NULL);
}
