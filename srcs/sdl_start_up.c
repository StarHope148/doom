/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 17:05:51 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_env *wolf, int exit_type, char *message)
{
	ft_free_surface_image(wolf);
	ft_destroy_texture_renderer_window(wolf);
	SDL_Quit();
	if (wolf->mapdata.map != NULL)
		ft_free_map(wolf);
	if (message != NULL)
		ft_putendl_fd(message, 2);
	exit(exit_type);
}

void	ft_init_window(t_env *wolf)
{
	wolf->window = SDL_CreateWindow("WOLF3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WIDTH,
					HEIGHT,
					0);
	if (wolf->window == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateWindow()");
}

void	ft_init_renderer_texture(t_env *wolf)
{
	wolf->renderer = SDL_CreateRenderer(wolf->window,
										-1,
										SDL_RENDERER_ACCELERATED);
	if (wolf->renderer == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateRenderer()");
	wolf->texture = SDL_CreateTexture(wolf->renderer,
									SDL_PIXELFORMAT_RGBA8888,
									SDL_TEXTUREACCESS_STREAMING,
									WIDTH,
									HEIGHT);
	if (wolf->texture == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateTexture()");
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

void	ft_sdl(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_Init()");
	ft_init_window(wolf);
	ft_init_renderer_texture(wolf);
	ft_load_surface(wolf, "textures/risitas_wall.bmp",
					&(wolf->surface_wall_north));
	ft_load_surface(wolf, "textures/panda_wall.bmp",
					&(wolf->surface_wall_south));
	ft_load_surface(wolf, "textures/orange_wall.bmp",
					&(wolf->surface_wall_east));
	ft_load_surface(wolf, "textures/green_wall.bmp",
					&(wolf->surface_wall_west));
	ft_print(wolf);
	ft_key_hook(wolf);
	ft_exit(wolf, EXIT_SUCCESS, NULL);
}
