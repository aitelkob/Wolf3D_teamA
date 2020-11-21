/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_miniMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:20:51 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/21 14:28:20 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"



///////////////////////////////////// ayoub /////////////////////

void		player_inMini(t_wolf_3d *w)
{
	SDL_SetRenderDrawColor(w->sdl.renderer,255,0,0,255);

	w->sdl.player = (SDL_Rect){
		w->player.pos.y * MAP_SACLER * TILE_SIZE,
		w->player.pos.x * MAP_SACLER * TILE_SIZE,
		w->player.with * MAP_SACLER,
		w->player.height * MAP_SACLER
		};

	//printf(" w->player.pos.y= %f w->player.pos.x=%f  \n",w->player.pos.y,w->player.pos.x);
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
			w->sdl.map = (SDL_Rect){
				x_exp * MAP_SACLER,
				y_exp * MAP_SACLER,
				TILE_SIZE * MAP_SACLER,
				TILE_SIZE * MAP_SACLER
			};
			SDL_RenderFillRect(w->sdl.renderer,&w->sdl.map);
			if (i == (int)w->player.pos.x && j == (int)w->player.pos.y)
			{
				//printf("i was here i = %d, pos.x = %d, j = %d, pos.y = %d\n", i, (int)w->player.pos.x, j, (int)w->player.pos.y);
				player_inMini(w);
			}
			j++;
		}
		i++;
	}
}

void		drawCube(t_wolf_3d *w, int x_begin, int y_begin, double scaler, int color)
{
	int i;
	int j;

	j = x_begin;
	while (j < x_begin + CUBESIZE)
	{
		i = y_begin;
		while (i < y_begin + CUBESIZE)
		{
			if (j != x_begin + (CUBESIZE * scaler) && i != y_begin + (CUBESIZE * scaler))
				w->data[i + (j * WIDTH)] = color;
			i++;
		}
		j++;
	}
}

/*void		drawMap(t_wolf_3d *w)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAP_NUM_ROWS * CUBESIZE * MAP_SACLER)
	{
		j = 0;
		while (j < MAP_NUM_COLS * CUBESIZE * MAP_SACLER)
		{
			if (w->player.world_map[i / (int)(CUBESIZE * MAP_SACLER)][j / (int)(CUBESIZE * MAP_SACLER)] != 0)
				drawCube(w, i, j, 0xC0C0C0);
			else if ((int)(i / (int)(CUBESIZE * MAP_SACLER)) == (int)w->player.pos.x && (int)(j / (int)(CUBESIZE * MAP_SACLER)) == (int)w->player.pos.y)
				drawCube(w, i, j, 0xff0000);
			else if (w->player.world_map[(int)(i / (int)(CUBESIZE * MAP_SACLER))][(int)(j / (int)(CUBESIZE * MAP_SACLER))] == 0)
				drawCube(w, i, j, 0);
			j += (CUBESIZE * MAP_SACLER);
		}
		i += (CUBESIZE * MAP_SACLER);
	}
}*/

void	drawMap(t_wolf_3d *w)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_NUM_COLS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (w->player.world_map[i][j] != 0)
				drawCube(w, i * CUBESIZE, j * CUBESIZE, 1, 0xC0C0C0);
			else if (i == (int)w->player.pos.x && j == (int)w->player.pos.y)
				drawCube(w, i * CUBESIZE, j * CUBESIZE, 1/2, 0xff0000);
			j++;
		}
		i++;
	}
}