/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:25:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/30 02:16:16 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_add_object(t_env *doom, t_point pos)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->data.type == 0)
	{
		tmp->data.pos.x = pos.x + 0.5;
		tmp->data.pos.y = pos.y + 0.5;
		tmp->data.type = doom->map.data[pos.y * doom->map.nbcol + pos.x];
	}
	else
	{
		if ((tmp->next = ft_memalloc(sizeof(t_object))) == NULL)
			ft_exit(doom, EXIT_FAILURE, "Error in ft_memalloc");
		tmp = tmp->next;
		tmp->data.pos.x = pos.x + 0.5;
		tmp->data.pos.y = pos.y + 0.5;
		tmp->data.type = doom->map.data[pos.y * doom->map.nbcol + pos.x];
	}
}

void			ft_count_objects(t_env *doom)
{
	t_point		pos;

	pos.y = 0;
	while (pos.y < doom->map.nbl)
	{
		pos.x = 0;
		while (pos.x < doom->map.nbcol)
		{
			if (doom->map.data[pos.y * doom->map.nbcol + pos.x] == BARREL ||
					doom->map.data[pos.y * doom->map.nbcol + pos.x] ==
					HEALTH_POTION)
				ft_add_object(doom, pos);
			pos.x++;
		}
		pos.y++;
	}
}