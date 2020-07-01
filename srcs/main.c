/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:53:23 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 16:56:53 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_usage(void)
{
	ft_putendl_fd("usage: ./wolf3d [file.map]", 2);
	return (EXIT_FAILURE);
}

int		ft_random(void)
{
	ft_putendl_fd("/dev/random cannot be used", 2);
	return (EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (ft_usage());
	if (ft_strcmp("/dev/random", av[1]) == 0)
		return (ft_random());
	ft_wolf3d(av[1]);
	return (0);
}

/*
**  int		main(int ac, char **av)
**  {
**  	SDL_Window		*test_window;
**  	SDL_Renderer	*test_renderer;
**  	SDL_Texture		*test_texture;
**
**  	(void)ac;
**  	(void)av;
**  	SDL_Init(SDL_INIT_VIDEO);
**  	test_window = SDL_CreateWindow("WOLF3D",
**  					SDL_WINDOWPOS_CENTERED,
**  					SDL_WINDOWPOS_CENTERED,
**  					WIDTH,
**  					HEIGHT,
**  					0);
**  	if (test_window == NULL)
**  		exit(EXIT_FAILURE);
**  	test_renderer = SDL_CreateRenderer(test_window,
**  										-1,
**  										SDL_RENDERER_ACCELERATED);
**  	if (test_renderer == NULL)
**  		exit(EXIT_FAILURE);
**  	test_texture = SDL_CreateTexture(test_renderer,
**  									SDL_PIXELFORMAT_RGBA8888,
**  									SDL_TEXTUREACCESS_STREAMING,
**  									WIDTH,
**  									HEIGHT);
**  	if (test_texture == NULL)
**  		exit(EXIT_FAILURE);
** 	SDL_RenderCopy(test_renderer, test_texture, NULL, NULL);
**  	if (test_texture != NULL)
**  	{
**  		SDL_DestroyTexture(test_texture);
**  		test_texture = NULL;
**  	}
**  	if (test_renderer != NULL)
**  	{
**  		SDL_DestroyRenderer(test_renderer);
**  		test_renderer = NULL;
**  	}
**  	if (test_window != NULL)
**  	{
**  		SDL_DestroyWindow(test_window);
**  		test_window = NULL;
**  	}
**  	SDL_Quit();
**  	return (0);
**  }
*/
