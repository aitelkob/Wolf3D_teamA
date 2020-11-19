/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_miniMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:20:51 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/19 05:50:35 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"
 ///////////////////////////////////// ayoube /////////////////////
void		player_inMini(t_wolf_3d *w)
{
	SDL_SetRenderDrawColor(w->sdl.renderer,50,55,55,255);

	w->sdl.player = (SDL_Rect){w->player.pos.y *MAP_SACLER,
		w->player.pos.x  *MAP_SACLER,
		w->player.with   *MAP_SACLER,
		w->player.height *MAP_SACLER};

	printf(" w->player.pos.y= %f w->player.pos.x=%f  \n",w->player.pos.y,w->player.pos.x);
	SDL_RenderFillRect(w->sdl.renderer,&w->sdl.player);
}
void		mini_map(t_wolf_3d *w)
{
	int i = 0;
	int j;
	int x_exp = 0;
	int y_exp = 0;
	int color_map;

	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			x_exp = j * TILE_SIZE;
			y_exp = i * TILE_SIZE;
			color_map = w->player.world_map[i][j] != 0 ? 255 : 0;
			//SDL_SetRenderDrawBlendMode(w->sdl.renderer,SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(w->sdl.renderer,color_map,color_map,color_map,255);
			w->sdl.map = (SDL_Rect){x_exp*MAP_SACLER,
				y_exp *MAP_SACLER,
				TILE_SIZE *MAP_SACLER,
				TILE_SIZE *MAP_SACLER};
			SDL_RenderFillRect(w->sdl.renderer,&w->sdl.map);
			j++;
		}
		i++;
	}
}
