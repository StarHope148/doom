/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 01:02:50 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_update_screen(t_env *wolf)
{
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);
	ft_set_sdl_minimap_colors(wolf);
	SDL_RenderPresent(wolf->renderer);
}

void	ft_pixel_access_bmp_images(t_env *wolf)
{
	wolf->pixels_wall_north = wolf->surface_wall_north->pixels;
	wolf->pixels_wall_south = wolf->surface_wall_south->pixels;
	wolf->pixels_wall_west = wolf->surface_wall_west->pixels;
	wolf->pixels_wall_east = wolf->surface_wall_east->pixels;
}

void	draw_text(t_env *wolf, int pos, SDL_Surface *text)
{
	int			i;
	int			j;
	Uint32		*goodpos_screenpix;
	Uint32		*surfpix;

	if (text->h > HEIGHT || text->w > WIDTH)
		return ;
	if (pos + text->h * WIDTH + text->w > WIDTH * HEIGHT)
		return ;
	surfpix = (Uint32 *)text->pixels;
	goodpos_screenpix = wolf->screen_pixels + pos;
	j = -1;
	while (++j < text->h)
	{
		i = -1;
		while (++i < text->w)
			goodpos_screenpix[j * WIDTH + i] = surfpix[j * text->w + i];
	}
}

void	draw_centered_text(t_env *wolf, SDL_Surface *text)
{
	draw_text(wolf, (WIDTH * (1 + HEIGHT - text->h) - text->w) / 2, text);
}

void	ft_draw_fps(t_env *wolf)
{
	wolf->time_tmp = clock();
	wolf->frames++;
	if ((wolf->time_tmp - wolf->time_fps) > CLOCKS_PER_SEC)
	{
		if ((wolf->fps = TTF_RenderText_Blended(wolf->txt.font,
				ft_itoa((int)wolf->frames), wolf->txt.black)) == NULL)
			ft_exit(wolf, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
		wolf->frames = 0;
		wolf->time_fps = clock();
	}
	if (wolf->fps != NULL)
		draw_text(wolf,
			(wolf->minimap.def_y + wolf->block + 1) * WIDTH, wolf->fps);
}

void	ft_print(t_env *wolf)
{
	ft_pixel_access_bmp_images(wolf);
	ft_raycaster(wolf);
	ft_draw_minimap(wolf);
	ft_draw_fps(wolf);
	ft_update_screen(wolf);
	if (clock() - wolf->time0 < 3 * CLOCKS_PER_SEC)
		draw_centered_text(wolf, wolf->txt.surf);
	if ((SDL_UpdateTexture(wolf->texture, NULL,
					wolf->screen_pixels,
					wolf->pitch)) < 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
}
