/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:57:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/07 02:15:09 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_wolf3d(char *mapfile)
{
	t_env	wolf;

	ft_initialize(&wolf, mapfile);
	save_in_file(&wolf.map);
	ft_sdl(&wolf);
}
