/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:26:24 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 10:38:35 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_dead(t_env *doom)
{
	static int	i = 0;

	(void)doom;
	if (i == 0)
	{
		i++;
		printf("You are DEAD !\n"); //DEBUG
	}
}

void			ft_taking_damage(t_env *doom, int amount)
{
	if (doom->chr.health >= amount)
	{
		if ((FMOD_System_PlaySound(doom->sound.system, doom->sound.life_down,
                                        NULL, 0, NULL)) != FMOD_OK)
                                perror("Error in FMOD_System_PlaySound for life_down ");

		doom->chr.health -= amount;
	}
	else if (doom->chr.health <= 0)
	{
		doom->chr.health = 0;
		ft_dead(doom);
	}
}

int				ft_restore_health(t_env *doom, int amount)
{
	if (doom->chr.health == PLAYER_MAX_HP)
		return (FALSE);
	doom->chr.health += amount;
	if (doom->chr.health > PLAYER_MAX_HP)
		doom->chr.health = PLAYER_MAX_HP;
	printf("just restored %d HP\n", amount); //DEBUG
	return (TRUE);
}

static int		is_on_fire(t_env *e)
{
	t_object	*obj;

	obj = &e->obj;
	while (obj)
	{
		if (obj->data.type == TORCH && obj->data.dist < 0.6)
			return (1);
		obj = obj->next;
	}
	return (0);
}

void			resolve_on_fire(t_env *e)
{
	if (!e->chr.on_fire)
		e->chr.on_fire = is_on_fire(e);
	if (!e->chr.on_fire)
		return ;
	if (is_on_fire(e) == 0)
	{
		e->chr.on_fire = 0;
		e->chr.fire_time = 0;
	}
	else
	{
		if (!e->chr.fire_time)
			e->chr.fire_time = get_time(e);
		else
		{
			if (get_time(e) - e->chr.fire_time > e->chr.on_fire)
			{
				ft_taking_damage(e, FIRE_AIE);
				e->chr.on_fire++;
			}
		}
	}
}
