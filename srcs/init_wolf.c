/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:13:22 by yait-el-          #+#    #+#             */
/*   Updated: 2020/12/05 01:03:28 by yait-el-         ###   ########.fr       */
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

	w->player.dir.x = -1;
	w->player.dir.y = 0;
	w->player.with = 20;
	w->player.height = 20;
	w->player.plane.x = 0;
	w->player.plane.y = 0.57;
	w->fps.fps = 30;
	w->fps.frame_target = 1000 / w->fps.fps;
	w->fps.last_frame_time = 0;
	w->dst.w = 100;
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
	w->sdl.cur = IMG_Load(PNG);
	w->sdl.wall = IMG_Load(MOSSY);
	w->sdl.wall2 = IMG_Load(WOOD);
	w->sdl.wall3 = IMG_Load(EAGLE);
	w->sdl.wall4 = IMG_Load(MOSSY);
	w->sdl.wall1 = IMG_Load(GRAYSTONE);
	w->sdl.wall5 = IMG_Load(BLUESTONE);
	w->sdl.ceiling_texture = IMG_Load(REDBRICK);
	w->sdl.roof_texture = IMG_Load(PURPLESTONE);
	w->sdl.new_text = malloc(sizeof(unsigned int*) * 6);
	w->sdl.new_text[0] = (unsigned int*)w->sdl.roof_texture->pixels;
	w->sdl.new_text[1] = (unsigned int*)w->sdl.wall1->pixels;
	w->sdl.new_text[2] = (unsigned int*)w->sdl.wall3->pixels;
	w->sdl.new_text[3] = (unsigned int*)w->sdl.wall4->pixels;
	w->sdl.new_text[4] = (unsigned int*)w->sdl.wall5->pixels;
	w->sdl.new_text[5] = (unsigned int*)w->sdl.wall->pixels;

	w->sdl.wall_data_tmp = (unsigned int*)w->sdl.wall3->pixels;

	w->sdl.wall_data_floor = (unsigned int*)w->sdl.wall2->pixels;

	if (!w->sdl.cur_tex)
		return;
}
