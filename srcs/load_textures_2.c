/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 04:58:38 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 05:52:24 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_load_hud_textures(t_env *doom)
{
	if ((get_xpm("textures/gun.xpm", &doom->xpm[GUN_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for gun.xpm");
	if ((get_xpm("textures/gun_firing.xpm", &doom->xpm[GUN_FIRING_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for gun_firing.xpm");
	if ((get_xpm("textures/crosshair.xpm", &doom->xpm[CROSSHAIR])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for crosshair.xpm");
	if ((get_xpm("textures/healthbar.xpm", &doom->xpm[HEALTHBAR_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for healthbar.xpm");
}

void		ft_load_other_object_textures(t_env *doom)
{
	if (get_xpm("textures/health_potion.xpm", &doom->xpm[HEALTH_POTION_XPM]))
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for health_potion.xpm");
	if ((get_xpm("textures/key.xpm", &doom->xpm[KEY_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for key.xpm");
	if ((get_xpm("textures/barrel.xpm", &doom->xpm[BARREL_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for barrel.xpm");
	if ((get_xpm("textures/projectile.xpm", &doom->xpm[PROJECTILE_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for projectile.xpm");
}

void		ft_load_other_textures(t_env *doom)
{
	if ((get_xpm("textures/chain.xpm", &doom->xpm[GRID_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for chain.xpm");
	if ((get_xpm("textures/button_off.xpm", &doom->xpm[BUTTON_OFF_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for button_off.xpm");
	if ((get_xpm("textures/button_on.xpm", &doom->xpm[BUTTON_ON_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for button_on.xpm");
	if ((get_xpm("textures/door_metal.xpm", &doom->xpm[DOOR_METAL_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for door_metal.xpm");
}

void		ft_load_home_screen_textures(t_env *doom)
{
	if ((get_xpm("textures/home.xpm", &doom->xpm[HOME_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for home.xpm");
	if ((get_xpm("textures/press_enter.xpm", &doom->xpm[PRESS_ENTER_XPM])) != 0)
		ft_exit(doom, EXIT_FAILURE, "Error in get_xpm() for press_enter.xpm");
}

void		ft_load_textures_2(t_env *doom)
{
	ft_load_hud_textures(doom);
	ft_load_other_object_textures(doom);
	ft_load_other_textures(doom);
	ft_load_home_screen_textures(doom);
}
