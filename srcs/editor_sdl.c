/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thparlos <thparlos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:27:01 by czhang            #+#    #+#             */
/*   Updated: 2020/08/01 20:31:43 by thparlos         ###   ########.fr       */
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

int		ft_new_map(t_point size, t_map *m)
{
	int	x;
	int	y;

	m->nbl = size.y;
	m->nbcol = size.x;
	if (ft_malloc_tab(m) == -1)
		return (-1);
	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
		{
			if (y == 0 || y == size.y - 1 || x == 0 || x == size.x - 1)
				m->data[y * size.x + x] = WALL;
			else
				m->data[y * size.x + x] = EMPTY;
			m->bright[y * size.x + x] = 1;
			m->alt[y * size.x + x] = 3;
		}
	}
	return (0);
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

void	editor(char *av1, char *av2)
{
	t_env	doom;
	t_point	size;

	ft_init_env(&doom);
	doom.editor++;
	size.y = ft_atoi(av1);
	size.x = ft_atoi(av2);
	if (size.x == 0)
		ft_init_map(&doom, av1);
	else if (size.x < 3 || size.y < 3)
		ft_exit(&doom, EXIT_FAILURE, "Please use av[1] >= 3 && av[2] >= 3");
	else if (ft_new_map(size, &doom.map))
		ft_exit(&doom, EXIT_FAILURE, "Error in new_map()");
	if ((get_xpm("textures/cursor.xpm", &doom.xpm[CURSOR_XPM])) != 0)
		ft_exit(&doom, EXIT_FAILURE, "Error in get_xpm() for cursor.xpm");
	sdl_editor(&doom);
}
