/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:05 by czhang            #+#    #+#             */
/*   Updated: 2020/08/01 03:22:49 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	editor_map(t_env *doom)
{
	t_point	pix;
	Uint32	color;
	t_point	map_ptr;

	pix.y = -1;
	while (++pix.y < H)
	{
		pix.x = -1;
		while (++pix.x < W)
		{
			map_ptr.y = pix.y * doom->map.nbl / H;
			map_ptr.x = pix.x * doom->map.nbcol / W;
			ft_set_tile_color(doom, map_ptr.y, map_ptr.x, &color);
			doom->screen_pixels[pix.y * W + pix.x] = color;
		}
	}
}
