/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:26:24 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 08:07:00 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_dead(t_env *doom)
{
	static int	i = 0;

	(void)doom;
	if (i == 0)
	{
		i++;
		printf("You are DEAD !\n");			//DEBUG
	}
}

void		ft_taking_damage(t_env *doom, int amount)
{
	if (doom->chr.health >= amount)
		doom->chr.health -= amount;
	else if (doom->chr.health <= 0)
	{
		doom->chr.health = 0;
		ft_dead(doom);
	}
}

int			ft_restore_health(t_env *doom, int amount)
{
	if (doom->chr.health == PLAYER_MAX_HP)
		return (FALSE);
	doom->chr.health += amount;
	if (doom->chr.health > PLAYER_MAX_HP)
		doom->chr.health = PLAYER_MAX_HP;
	printf("just restored %d HP\n", amount);			//DEBUG
	return (TRUE);
}