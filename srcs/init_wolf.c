/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:13:22 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/06 22:45:22 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
 *check for the fisrt  0 spot
 *
 */
void		player_start(t_wolf_3d *w)
{
	int i,j;

	i = 0;
	while (i < MAP_NUM_COLS)
	{
		j = 0;
		while (j < MAP_NUM_ROWS)
		{
			if (w->player.world_map[i][j] == 0)
			{
				w->player.pos.x = i;
				w->player.pos.y = j;
				return;
			}
			j++;
		}
		i++;
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
	 SDL_ShowCursor(0);
     w->player.dir.x = -1;
     w->player.dir.y = 0;
	 w->player.with = 20;
	 w->player.height = 20;
     w->player.plane.x = 0;
     w->player.plane.y = 0.57;
     w->fps.fps = 60;
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

