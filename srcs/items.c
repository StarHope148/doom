/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:15:12 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 06:40:29 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_pick_up_items(t_env *doom)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp != NULL)
	{
		if (tmp->data.type == HEALTH_POTION && tmp->data.dist <= 0.5)
		{
			if (ft_restore_health(doom, HEALTH_POTION_AMOUNT) == TRUE)
			{
				tmp->data.to_remove = TRUE;
				doom->map.data[(int)tmp->data.pos.y *
					doom->map.nbcol + (int)tmp->data.pos.x] = EMPTY;
			}
		}
		tmp = tmp->next;
	}
}