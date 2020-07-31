/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 22:11:50 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 20:44:49 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_pointd	ft_new_t_pointd(double y, double x)
{
	t_pointd	tmp;

	tmp.y = y;
	tmp.x = x;
	return (tmp);
}

void		ft_add_object_projectile(t_env *doom)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->data.type == 0)
	{
		tmp->data.pos.x = doom->cam.pos_x;
		tmp->data.pos.y = doom->cam.pos_y;
		tmp->data.vel.x = sin(doom->cam.angle) * RATIO_PROJECTILE_SPEED;
		tmp->data.vel.y = cos(doom->cam.angle) * RATIO_PROJECTILE_SPEED;
		tmp->data.type = PROJECTILE;
	}
	else
	{
		if ((tmp->next = ft_memalloc(sizeof(t_object))) == NULL)
			ft_exit(doom, EXIT_FAILURE, "Error in ft_memalloc");
		tmp = tmp->next;
		tmp->data.pos.x = doom->cam.pos_x;
		tmp->data.pos.y = doom->cam.pos_y;
		tmp->data.vel.x = sin(doom->cam.angle) * RATIO_PROJECTILE_SPEED;
		tmp->data.vel.y = cos(doom->cam.angle) * RATIO_PROJECTILE_SPEED;
		//printf("vel.y = %f\tvel.x = %f\n", tmp->data.vel.y, tmp->data.vel.x);
		tmp->data.type = PROJECTILE;
	}
}

void		ft_shoot_projectile(t_env *doom)
{
	if (doom->cam.pos_z > DEFAULT_POS_Z)
		return ;
	ft_add_object_projectile(doom);
	if (!doom->gun.firing)
		if ((FMOD_System_PlaySound(doom->sound.system, doom->sound.laser_shot,
				NULL, 0, NULL)) != FMOD_OK)
			perror("Error in FMOD_System_PlaySound for laser_shot ");
	doom->gun.firing = TRUE;
	//debug display object list with type and [y][x]
	//t_object *tmp = &doom->obj;
	//while (tmp != NULL)
	//{
	//	printf("%c at [%f][%f]\n", tmp->data.type, tmp->data.pos.y, tmp->data.pos.x);
	//	tmp = tmp->next;
	//}
	//printf("--------------------------\n");
}