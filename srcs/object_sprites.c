/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:49:51 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/27 02:19:29 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/* void	ft_draw_image(t_env *doom)
{
	doom->obj.screen.y = H / 2;
	//static int test_printf;
	
	doom->obj.cursor.y = 0;
	while (doom->obj.cursor.y < doom->xpm[BARREL_XPM].h && doom->obj.screen.y < H)
	{
		doom->obj.cursor.x = 0;
		doom->obj.screen.x = W / 2;
		while (doom->obj.cursor.x < doom->xpm[BARREL_XPM].w && doom->obj.screen.x < W)
		{
			if (doom->xpm[BARREL_XPM].pixels[doom->obj.cursor.y * doom->xpm[BARREL_XPM].w + doom->obj.cursor.x] != MAGENTA)
				doom->screen_pixels[doom->obj.screen.y * W + doom->obj.screen.x] = doom->xpm[BARREL_XPM].pixels[doom->obj.cursor.y * doom->xpm[BARREL_XPM].w + doom->obj.cursor.x];
			doom->obj.cursor.x++;
			doom->obj.screen.x++;
		}
		doom->obj.cursor.y++;
		doom->obj.screen.y++;
	}

	//printf("TEST %d\n", test_printf++);
}

void	ft_draw_objects(t_env *doom)
{
	//while (doom->obj[i] != )
	{
		// Update Object Physics
		//object.x += object.vx * fElapsedTime;
		//object.y += object.vy * fElapsedTime;

		// Check if object is inside wall - set flag for removal
		//if (map.c_str()[(int)object.x * nMapWidth + (int)object.y] == '#')
		//	object.bRemove = true;
					
		// Can object be seen?
		doom->obj.pos.x = 3;
		doom->obj.pos.y = 5;
		float fVecX = doom->obj.pos.x - doom->cam.pos_x;
		float fVecY = doom->obj.pos.y - doom->cam.pos_y;
		float fDistanceFromPlayer = sqrtf(fVecX*fVecX + fVecY*fVecY);

		float fEyeX = sinf(doom->cam.angle);
		float fEyeY = cosf(doom->cam.angle);

		// Calculate angle between lamp and players feet, and players looking direction
		// to determine if the lamp is in the players field of view
		float fObjectAngle = atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);
		if (fObjectAngle < -3.14159f)
			fObjectAngle += 2.0f * 3.14159f;
		if (fObjectAngle > 3.14159f)
			fObjectAngle -= 2.0f * 3.14159f;

		int bInPlayerFOV ;
		if (fabs(fObjectAngle) < doom->cam.fov / 2.0f)
			bInPlayerFOV = 1;
		else
			bInPlayerFOV = 0;

		printf("InPlayerFOV = %d\tFOV = %f\t distanceFromPlayer = %f\n",bInPlayerFOV, doom->cam.fov, fDistanceFromPlayer);
		if (bInPlayerFOV && fDistanceFromPlayer >= 0.5f)
		{
			float fObjectCeiling = (float)((H / 2.0) - H / ((float)fDistanceFromPlayer)) * 0.5 ;
			float fObjectFloor = H - fObjectCeiling;
			float fObjectHeight = fObjectFloor - fObjectCeiling;
			//printf("doom->xpm[BARREL_XPM].h = %d\n", doom->xpm[BARREL_XPM].h);
			float fObjectAspectRatio = (float)(doom->xpm[BARREL_XPM].h / (float)doom->xpm[BARREL_XPM].w);
			float fObjectWidth = fObjectHeight / fObjectAspectRatio;
			float fMiddleOfObject = (0.5f * (fObjectAngle / (doom->cam.fov / 2.0f)) + 0.5f) * (float)W;
			//printf("objectWidth = %f\tobjectHeight = %f\tapectRatio = %f\n", fObjectWidth, fObjectHeight, fObjectAspectRatio);
			// Draw BARREL_XPM
			for (float lx = 0; lx < fObjectWidth; lx++)
			{
				for (float ly = 0; ly < fObjectHeight; ly++)
				{
					float fSampleX = lx / fObjectWidth;
					float fSampleY = ly / fObjectHeight;
					int text_x = fSampleX * doom->xpm[BARREL_XPM].w;
					int text_y = fSampleY * doom->xpm[BARREL_XPM].h;
					//wchar_t c = object.sprite->SampleGlyph(fSampleX, fSampleY);
					Uint32	color = doom->xpm[BARREL_XPM].pixels[(int)(text_y * doom->xpm[BARREL_XPM].w + text_x)];
					int nObjectColumn = (int)(fMiddleOfObject + lx - (fObjectWidth / 2.0f));
					//printf("nObjectColumn = %d\n", nObjectColumn);
					if (nObjectColumn >= 0 && nObjectColumn < W)
						if (color != MAGENTA)
						{
							//printf("TEST\n");
							//Draw(nObjectColumn, fObjectCeiling + ly, c, object.sprite->SampleColour(fSampleX, fSampleY));
							//fDepthBuffer[nObjectColumn] = fDistanceFromPlayer;
							doom->screen_pixels[(int)((fObjectCeiling + ly) * W + nObjectColumn)] = color;
							//doom->screen_pixels[(int)((fObjectCeiling + ly) * W + nObjectColumn)] = RED;
						}
				}
			}
		}
	}
} */