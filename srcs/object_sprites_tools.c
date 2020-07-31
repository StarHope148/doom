/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprites_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 02:02:47 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 02:57:52 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_choose_and_init_torch_sprite(t_env *e, t_object *tmp)
{
	static int	id_anim = 0;
	static int	duration = 0;

	init_draw_torch(e, tmp);
	if (duration == 4)
	{
		duration = 0;
		if (id_anim >= 7)
			id_anim = 0;
		id_anim++;
	}
	else
		duration++;
	return (TORCH_1_XPM + id_anim);
}

int			ft_choose_and_init_statue_sprite(t_env *e, t_object *tmp)
{
	double	obj_dir;

	init_draw_statue(e, tmp);
	obj_dir = atan2(e->cam.pos_y - tmp->data.pos.y,
		e->cam.pos_x - tmp->data.pos.x);
	if (obj_dir >= -0.75 && obj_dir <= 0.75)
		return (STATUE_FRONT_XPM);
	else if (obj_dir < -0.75 && obj_dir >= -PI)
		return (STATUE_LEFT_XPM);
	else if (obj_dir > 0.75 && obj_dir <= PI)
		return (STATUE_RIGHT_XPM);
	else
		return (STATUE_FRONT_XPM);
}

int			ft_choose_and_init_sprite(t_env *e, t_object *tmp)
{
	if (tmp->data.type == PROJECTILE)
	{
		init_draw_projectile(e, tmp);
		return (PROJECTILE_XPM);
	}
	else if (tmp->data.type == BARREL)
	{
		init_draw_barrel(e, tmp);
		return (BARREL_XPM);
	}
	else if (tmp->data.type == HEALTH_POTION)
	{
		init_draw_health_potion(e, tmp);
		return (HEALTH_POTION_XPM);
	}
	else if (tmp->data.type == KEY)
	{
		init_draw_key(e, tmp);
		return (KEY_XPM);
	}
	else if (tmp->data.type == TORCH)
		return (ft_choose_and_init_torch_sprite(e, tmp));
	else if (tmp->data.type == STATUE)
		return (ft_choose_and_init_statue_sprite(e, tmp));
	else
		return (BARREL_XPM);
}
