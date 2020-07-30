/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprites_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 02:02:47 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/30 02:08:49 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_choose_sprite(t_env *e, t_object *tmp)
{
	if (tmp->data.type == BARREL)
	{
		init_draw_barrel(e, tmp);
		return(BARREL_XPM);
	}
	else if (tmp->data.type == HEALTH_POTION)
	{
		init_draw_health_potion(e, tmp);
		return (HEALTH_POTION_XPM);
	}
	return (0);
}