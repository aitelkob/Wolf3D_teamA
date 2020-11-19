/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:16:33 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/03 04:42:52 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void init_vari(t_wolf_3d *w)
{
	w->player.pos.x = 19.5;
	w->player.pos.y = 19.5;
	w->player.dir.x = -1;
	w->player.dir.y = 0;
	w->player.plane.x = 0;
	w->player.plane.y = 0.57;
	w->fps.fps = 60;
	w->fps.frame_target = 1000 / w->fps.fps;
	dst.w = 100;
	dst.h = 100;
	dst.x = (WIDTH / 2) - (dst.w / 2);
	dst.y = (HEIGHT / 2) - (dst.h / 2);
	w->fps.last_frame_time = 0;
	SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), (HEIGHT / 2));
	load_img(w, PNG);
}

void		game_start(t_wolf_3d *w)
{
	////// game loop
	while (game)
}

void sdl_quit(t_wolf_3d *w)
{
	SDL_FreeSurface(w->sdl.cur);
	SDL_DestroyRenderer(w->sdl.renderer);
	SDL_DestroyWindow(w->sdl.win);
	SDL_Quit();
}

int 	init_wolf(t_wolf_3d w,int ac,char **av)
{
	int fd;
	if (ac == 2)
	{
		w = malloc(sizeof(t_wolf_3d));
		fd = open(av[1], O_RDONLY);
		if (fd >= 3)
			w->player.world_map = get_map(w->player.world_map, fd, av);
		else
			show_error1();
		init_perso(w);
		w->game_running = sdl_init_win(w);
		w->data = malloc(sizeof(int) * (WIDTH * HEIGHT));
		game_start(w);
	}
	else if (ac == 1)
		show_error3();
	return (1);
}
int main(int ac, char **av)
{

	t_wolf_3d w;

	init_wolf(&w,ac,**av);

	sdl_quit(&w);

	return (0);
}
