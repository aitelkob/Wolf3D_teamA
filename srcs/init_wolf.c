/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:13:22 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/26 19:07:53 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
 *check for the fisrt  0 spot
 *
 */
 
void player_start(t_wolf_3d *w)
{
	int i, j;

	i = MAP_NUM_COLS - 1;
	while (i >= 0)
	{
		j = MAP_NUM_ROWS - 1;
		while (j >= 0)
		{
			if (w->player.world_map[i][j] == 0)
			{
				w->player.pos.x = i + 0.35;
				w->player.pos.y = j + 0.35;
				return;
			}
			j--;
		}
		i--;
	}
}
/*
**  init player position x
**  init player position y
**  init direction vector x
**  init direction vector y
**  the 2d raycaster version of camera plane x
**  the 2d raycaster version of camera plane y
*/

void init_perso(t_wolf_3d *w)
{
	player_start(w);
	load_img(w, PNG);
	// nsiti hadi dakchi 3lash makhdmch lik texture
	texture_img(w);
	
	// SDL_ShowCursor(0);
	w->player.dir.x = -1;
	w->player.dir.y = 0;
	w->player.with = 20;
	w->player.height = 20;
	w->player.plane.x = 0;
	w->player.plane.y = 0.57;
	w->fps.fps = 30;
	w->fps.frame_target = 1000 / w->fps.fps;
	w->dst.w = 100;
	w->fps.last_frame_time = 0;
	w->dst.h = 100;
	SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), (HEIGHT / 2));
	w->dst.x = (WIDTH / 2) - (w->dst.w / 2);
	w->dst.y = (HEIGHT / 2) - (w->dst.h / 2);
	w->data = malloc(sizeof(int) * (WIDTH * HEIGHT));
}

void load_img(t_wolf_3d *w, const char *file)
{
	w->sdl.cur = IMG_Load(file);
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer,
												  w->sdl.cur);
	if (!w->sdl.cur_tex)
		return;
}
