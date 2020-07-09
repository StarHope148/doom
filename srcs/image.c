/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/09 03:29:26 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_update_screen(t_env *doom)
{
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	ft_set_sdl_minimap_colors(doom);
	SDL_RenderPresent(doom->renderer);
}

void	ft_pixel_access_bmp_images(t_env *doom)
{
	doom->pixels_wall_north = doom->surface_wall_north->pixels;
	doom->pixels_wall_south = doom->surface_wall_south->pixels;
	doom->pixels_wall_west = doom->surface_wall_west->pixels;
	doom->pixels_wall_east = doom->xpm->pixels;
	doom->pixels_floor = doom->surface_floor->pixels;
}

void	draw_text(t_env *doom, unsigned int pos, SDL_Surface *text)
{
	int			i;
	int			j;
	Uint32		*surfpix;

	if (text->h > HEIGHT || text->w > WIDTH)
		return ;
	if (pos + text->h * WIDTH + text->w > WIDTH * HEIGHT)
		return ;
	surfpix = (Uint32 *)text->pixels;
	j = -1;
	while (++j < text->h)
	{
		i = -1;
		while (++i < text->w)
			doom->screen_pixels[pos + j * WIDTH + i] = surfpix[j * text->w + i];
	}
}

void	draw_centered_text(t_env *doom, SDL_Surface *text)
{
	double	value;

	value = (WIDTH - text->w) / 2 + (HEIGHT * 0.3) * WIDTH;
	draw_text(doom, (unsigned int)value, text);
}

void	ft_draw_fps(t_env *doom)
{
	char	*str_frames;

	doom->fps.time_tmp = clock();
	doom->fps.frames++;
	if ((doom->fps.time_tmp - doom->fps.time_fps) > CLOCKS_PER_SEC)
	{
		if ((str_frames = ft_itoa((int)doom->fps.frames)) == NULL)
			ft_exit(doom, EXIT_FAILURE, "Error malloc in itoa (ft_draw_fps)");
		SDL_FreeSurface(doom->fps.s);
		if ((doom->fps.s = TTF_RenderText_Blended(doom->txt.font,
				str_frames, doom->txt.black)) == NULL)
		{
			ft_memdel((void **)&str_frames);
			ft_exit(doom, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
		}
		ft_memdel((void **)&str_frames);
		doom->fps.frames = 0;
		doom->fps.time_fps = clock();
	}
	if (doom->fps.s != NULL)
		draw_text(doom,
			(doom->minimap.def_y + doom->block + 1) * WIDTH, doom->fps.s);
}

double	get_time(t_env *doom)
{
	double	time;

	time = (clock() - doom->time0) / (double)CLOCKS_PER_SEC;
	return (time);
}

void	ft_funky_textures(t_env *doom)
{
	double	time;

	time = get_time(doom);
	if (time < 4.45)
		draw_centered_text(doom, doom->txt.welcome1);
	else if (5.35 < time && time < 8)
		draw_centered_text(doom, doom->txt.welcome2);
	if (doom->count_puls < MAX_PULS_FUNKY_TEXTURES &&
		doom->count_puls * doom->music_puls + 6.45 < time)
	{
		doom->wall = doom->wall == 3 ? 0 : doom->wall + 1;
		doom->count_puls++;
		if (doom->count_puls == 25)
			doom->wall = 3;
	}
 	else if (0.35 < time && time < 1.25)
		doom->wall = 0;
	else if (1.425 < time && time < 2.4)
		doom->wall = 2;
	else if (2.4 < time && time < 3.375)
		doom->wall = 1;
	else if (3.375 < time && time < 4.35)
		doom->wall = 0;
	else if (4.35 < time && time < 5.25)
		doom->wall = 2;
	else if (5.25 < time && time < 5.9)
		doom->wall = doom->wall == 3 ? 0 : doom->wall + 1;
}

void	ft_print(t_env *doom)
{
	ft_pixel_access_bmp_images(doom);
	animation_opening_door(doom);
	ft_raycaster(doom);
	ft_draw_minimap(doom);
	ft_draw_fps(doom);
	if (!doom->no_funky)
		ft_funky_textures(doom);
	ft_update_screen(doom);
	if ((SDL_UpdateTexture(doom->texture, NULL,
					doom->screen_pixels,
					doom->pitch)) < 0)
		ft_exit(doom, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
}
