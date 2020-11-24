/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_miniMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:20:51 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/24 18:01:20 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
**	hadi ba9i fiha tkhawr bzaaaf 
*/

void player_inMini(t_wolf_3d *w)
{
	double x;
	double y;

	x = (w->player.pos.y - (w->player.pos.x * 0.03));
	y = (w->player.pos.x - (w->player.pos.y * 0.03));
	SDL_SetRenderDrawColor(w->sdl.renderer, 255, 0, 0, 255);

	w->sdl.player = (SDL_Rect){
		x * MAP_SACLER * TILE_SIZE,
		y * MAP_SACLER * TILE_SIZE,
		w->player.with * MAP_SACLER,
		w->player.height * MAP_SACLER};
	SDL_RenderFillRect(w->sdl.renderer, &w->sdl.player);
}

void mini_map(t_wolf_3d *w)
{
	int i;
	int j;
	int color_map;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			color_map = w->player.world_map[i][j] != 0 ? 255 : 0;
			// SDL_SetRenderDrawBlendMode(w->sdl.renderer,SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(w->sdl.renderer, color_map, color_map, color_map, 255);
			w->sdl.map = (SDL_Rect){
				j * TILE_SIZE * MAP_SACLER,
				i * TILE_SIZE * MAP_SACLER,
				TILE_SIZE * MAP_SACLER,
				TILE_SIZE * MAP_SACLER};
			SDL_RenderFillRect(w->sdl.renderer, &w->sdl.map);
			j++;
		}
		i++;
	}
}

void mini_player(t_wolf_3d *w)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (i == (int)w->player.pos.x && j == (int)w->player.pos.y)
			{
				printf("x = %f, y = %f\n", w->player.pos.x, w->player.pos.y);
				player_inMini(w);
			}
			j++;
		}
		i++;
	}
}