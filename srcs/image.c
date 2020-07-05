/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/05 10:31:29 by czhang           ###   ########.fr       */
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

void	draw_text(t_env *wolf, unsigned int pos, SDL_Surface *text)
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
			wolf->screen_pixels[pos + j * WIDTH + i] = surfpix[j * text->w + i];
	}
}

void	draw_centered_text(t_env *wolf, SDL_Surface *text)
/* to be fixed */
{
	double	value;
	static int		lol = 0;
	if (lol == 0)
	{
		ft_putnbr(((double)WIDTH - text->w) / 2 + WIDTH * (double)(HEIGHT - text->h) / 2);
		ft_putendl("");
		ft_putnbr(WIDTH * (HEIGHT - text->h) / 2);
		ft_putendl("");
		ft_putnbr((double)WIDTH * (double)(HEIGHT - text->h) / (double)2);
		ft_putendl("");
		printf("text->h = %d, text->w = %d\n", text->h, text->w);
	}
	//value = (double)WIDTH * ((double)HEIGHT - (double)text->h) / (double)2 + ((double)WIDTH - (double)text->w) / (double)2;
	value = (WIDTH - text->w) / 2 + (HEIGHT * 0.3) * WIDTH;
	draw_text(wolf, (unsigned int)value, text);
	lol++;
}

void	ft_draw_fps(t_env *wolf)
{
	char	*str_frames;

	wolf->fps.time_tmp = clock();
	wolf->fps.frames++;
	if ((wolf->fps.time_tmp - wolf->fps.time_fps) > CLOCKS_PER_SEC)
	{
		if ((str_frames = ft_itoa((int)wolf->fps.frames)) == NULL)
			ft_exit(wolf, EXIT_FAILURE, "Error malloc in itoa (ft_draw_fps)");
		SDL_FreeSurface(wolf->fps.s);
		if ((wolf->fps.s = TTF_RenderText_Blended(wolf->txt.font,
				str_frames, wolf->txt.black)) == NULL)
		{
			ft_memdel((void **)&str_frames);
			ft_exit(wolf, EXIT_FAILURE, "Error in TTF_RenderText_Blended()");
		}
		ft_memdel((void **)&str_frames);
		wolf->fps.frames = 0;
		wolf->fps.time_fps = clock();
	}
	if (wolf->fps.s != NULL)
		draw_text(wolf,
			(wolf->minimap.def_y + wolf->block + 1) * WIDTH, wolf->fps.s);
}

double	get_time(t_env *wolf)
{
	double	time;

	time = (clock() - wolf->time0) / (double)CLOCKS_PER_SEC;
	return (time);
}

void	ft_funky_textures(t_env *wolf)
{
	double	time;

	time = get_time(wolf);
	if (wolf->count_puls * wolf->music_puls + 6.90 < time)
	{
		wolf->wall = wolf->wall == 3 ? 0 : wolf->wall + 1;
		wolf->count_puls++;
		//wolf->count_puls < 25 &&
	}
	else if (time < 4.45)
		draw_centered_text(wolf, wolf->txt.welcome1);
	else if (5.35 < time && time < 8)
		draw_centered_text(wolf, wolf->txt.welcome2);
 	if (0.55 < time && time < 1.35)
		wolf->wall = 0;
	else if (1.525 < time && time < 2.5)
		wolf->wall = 2;
	else if (2.5 < time && time < 3.425)
		wolf->wall = 1;
	else if (3.475 < time && time < 4.45)
		wolf->wall = 0;
	else if (4.45 < time && time < 5.35)
		wolf->wall = 2;
	else if (5.35 < time && time < 6)
		wolf->wall = wolf->wall == 3 ? 0 : wolf->wall + 1;
}

void	ft_print(t_env *wolf)
{
	ft_pixel_access_bmp_images(wolf);
	ft_raycaster(wolf);
	ft_draw_minimap(wolf);
	ft_draw_fps(wolf);
	ft_update_screen(wolf);
	ft_funky_textures(wolf);
	if ((SDL_UpdateTexture(wolf->texture, NULL,
					wolf->screen_pixels,
					wolf->pitch)) < 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_UpdateTexture()");
}
