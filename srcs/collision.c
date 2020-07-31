/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:49:23 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 01:09:36 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		wall_on_cam_pos(t_env *doom)
{
	char	map_symbol;

	map_symbol = doom->map.data[(int)doom->cam.pos_y *
		doom->map.nbcol + (int)doom->cam.pos_x];
	if (map_symbol == WALL)
		return (1);
	else if (map_symbol == DOOR)
		return (2);
	else if (map_symbol == TORCH)
		return (3);
	else if (map_symbol == GRID)
		return (3);
	else if (map_symbol == BUTTON_OFF)
		return (3);
	else if (map_symbol == BUTTON_ON)
		return (3);
	else if (map_symbol == BARREL)
		return (3);
	else if (map_symbol == STATUE)
		return (3);
	return (0);
}
