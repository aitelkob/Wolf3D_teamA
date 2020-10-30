/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:27:40 by ayagoumi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/10/28 04:19:07 by yait-el-         ###   ########.fr       */
=======
/*   Updated: 2020/10/27 17:18:29 by ayagoumi         ###   ########.fr       */
>>>>>>> f2e7d2aa29d7b3dd92feb091dd556bfb418a9fbe
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void draw_map_3d(t_wolf_3d *w)
{
	int x;
	double tmp1;
	double tmp2;

	x = 0;
	while (x < WIDTH)
	{
		w->ray.cameraX = 2 * x / (double)WIDTH - 1;
		w->ray.raydir.x = w->player.dir.x + w->player.plane.x * w->ray.cameraX;
		w->ray.raydir.y = w->player.dir.y + w->player.plane.y * w->ray.cameraX;
		tmp1 = (w->ray.raydir.x == 0) ? 1 : fabs(1 / w->ray.raydir.x);
		tmp2 = (w->ray.raydir.y == 0) ? 1 : fabs(1 / w->ray.raydir.y);
		w->ray.deltadist.x = (w->ray.raydir.y == 0) ? 0 : tmp1;
		w->ray.deltadist.y = (w->ray.raydir.x == 0) ? 0 : tmp2;
		w->ray.hit = 0;
		w->ray.map.x = (int)w->player.pos.x;
		w->ray.map.y = (int)w->player.pos.y;
		step_taken(w);
		dda_algorithm(w);
		detect_start_end(w);
		fill_data_tab(w, x);
		x++;
	}
}

void load_img(t_wolf_3d *w, const char *file)
{
	w->sdl.cur = IMG_Load(file);
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer, w->sdl.cur);
	if (!w->sdl.cur_tex)
		return;
}

/*
**	Time it took to draw this frame
**	Frame per second
** Speed of movement and rotation
**	Square per second
**	Radient per second
*/

void fps_calculation(t_fps *fps)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), (fps->last_frame_time + fps->frame_target)))
		;
	fps->delta_time = (SDL_GetTicks() - fps->last_frame_time) / 1000.0f;
	printf("FPS : %f\n", 1 / fps->delta_time);
	fps->movespeed = 30 * fps->delta_time;
	fps->rotspeed = 2 * fps->delta_time;
}

/*
**	Start the Mouse postion in the middle of the window
*/

void draw_on_win(t_wolf_3d *w, const char *file)
{
	SDL_Rect dst;

	dst.w = 100;
	dst.h = 100;
	dst.x = (WIDTH / 2) - (dst.w / 2);
	dst.y = (HEIGHT / 2) - (dst.h / 2);
	w->fps.last_frame_time = 0;
	SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), (HEIGHT / 2));
	load_img(w, file);
	while (w->game_running == 0)
	{
		SDL_ShowCursor(0);
		// SDL_SetRelativeMouseMode(SDL_TRUE); // trap the mouse inside the window
		fps_calculation(&(w->fps));
		w->fps.last_frame_time = SDL_GetTicks();
		draw_map_3d(w);
		//draw_map(w);
		SDL_UpdateTexture(
			w->sdl.texture, NULL,
			w->data, WIDTH * sizeof(int));
		SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
		SDL_RenderCopy(w->sdl.renderer, w->sdl.cur_tex, NULL, &dst);
		process_input(w, w->player.world_map);
		SDL_RenderPresent(w->sdl.renderer);
	}
}

/*
**	init player position x
**	init player position y
**	init direction vector x
**	init direction vector y
**	the 2d raycaster version of camera plane x
**	the 2d raycaster version of camera plane y
*/

void init_perso(t_wolf_3d *w)
{
	w->player.pos.x = 19.5;
	w->player.pos.y = 19.5;
	w->player.dir.x = -1;
	w->player.dir.y = 0;
	w->player.plane.x = 0;
	w->player.plane.y = 0.57;
	w->fps.fps = 60;
	w->fps.frame_target = 1000 / w->fps.fps;
}

int main(int ac, char **av)
{
	t_wolf_3d *w;
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
		if (w->player.world_map[(int)w->player.pos.x]
							   [(int)w->player.pos.y] == 0)
			draw_on_win(w, "./img/Png.png");
		SDL_FreeSurface(w->sdl.cur);
		SDL_DestroyRenderer(w->sdl.renderer);
		SDL_DestroyWindow(w->sdl.win);
		SDL_Quit();
	}
	else if (ac == 1)
		show_error3();
	return (0);
}
