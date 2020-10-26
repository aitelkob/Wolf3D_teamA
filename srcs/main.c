/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:27:40 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/10/26 19:06:34 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
**	Creating a render (The act of drawing the modelled object on screen)
**	then
**	Creating a texture image the draw the map on
*/

void calculate_plane_dir_x(t_wolf_3d *w, double rotation_speed)
{
	float cos_calc;
	float sin_calc;

	cos_calc = cos(rotation_speed);
	sin_calc = sin(rotation_speed);
	w->oldDirX = w->player.dir.x;
	w->player.dir.x = w->player.dir.x * cos_calc - w->player.dir.y * sin_calc;
	w->player.dir.y = w->oldDirX * sin_calc + w->player.dir.y * cos_calc;
	w->oldplaneX = w->player.plane.x;
	w->player.plane.x = w->player.plane.x * cos_calc - w->player.plane.y * sin_calc;
	w->player.plane.y = w->oldplaneX * sin_calc + w->player.plane.y * cos_calc;
}

void step_taken(t_wolf_3d *w)
{
	if (w->ray.raydir.x < 0)
	{
		w->ray.step.x = -1;
		w->ray.sidedist.x = (w->player.pos.x - w->ray.map.x) * w->ray.deltadist.x;
	}
	else
	{
		w->ray.step.x = 1;
		w->ray.sidedist.x = (w->ray.map.x + 1.0 - w->player.pos.x) * w->ray.deltadist.x;
	}
	if (w->ray.raydir.y < 0)
	{
		w->ray.step.y = -1;
		w->ray.sidedist.y = (w->player.pos.y - w->ray.map.y) * w->ray.deltadist.y;
	}
	else
	{
		w->ray.step.y = 1;
		w->ray.sidedist.y = (w->ray.map.y + 1.0 - w->player.pos.y) * w->ray.deltadist.y;
	}
}

/*
**	Jump to next map square, OR in x-direction, OR in y-direction
**	Check if ray has hit a wall
*/

void dda_algorithm(t_wolf_3d *w)
{
	while (w->ray.hit == 0)
	{
		if (w->ray.sidedist.x < w->ray.sidedist.y)
		{
			w->ray.sidedist.x += w->ray.deltadist.x;
			w->ray.map.x += w->ray.step.x;
			w->ray.side = 0;
		}
		else
		{
			w->ray.sidedist.y += w->ray.deltadist.y;
			w->ray.map.y += w->ray.step.y;
			w->ray.side = 1;
		}
		if (w->player.world_map[w->ray.map.x][w->ray.map.y] > 0)
			w->ray.hit = 1;
	}
	if (w->ray.side == 0)
		w->ray.perpWallDist = (w->ray.map.x - w->player.pos.x +
							   (1 - w->ray.step.x) / 2) /
							  w->ray.raydir.x;
	else
		w->ray.perpWallDist = (w->ray.map.y - w->player.pos.y +
							   (1 - w->ray.step.y) / 2) /
							  w->ray.raydir.y;
}

/*
**	Draw sky
**	Draw flor
**	Draw a vertical line from drawStart to drawEnd
*/

void fill_data_tab(t_wolf_3d *w, int x)
{
	int i;

	i = 0;
	while (i < w->ray.draw.start)
	{
		w->data[x + (i * WIDTH)] = 0x99cfe0;
		i++;
	}
	i = w->ray.draw.end;
	while (i < HEIGHT)
	{
		w->data[x + (i * WIDTH)] = 0x654321;
		i++;
	}
	while (w->ray.draw.start <= w->ray.draw.end)
	{
		w->ray.color = 0;
		if (w->ray.side == 1)
			w->ray.color = 0xffffff;
		else
			w->ray.color = 0x808080;
		w->data[x + (w->ray.draw.start * WIDTH)] = w->ray.color;
		w->ray.draw.start++;
	}
}

/*
**	Calculate height of line to draw on screen
**	calculate lowest pixel to fill in current stripe
**	Calculate highest pixel to fill in current stripe
*/

void detect_start_end(t_wolf_3d *w)
{
	w->ray.lineHeight = (int)(HEIGHT / w->ray.perpWallDist) * 0.5;
	if (w->ray.perpWallDist <= 0)
		w->ray.lineHeight = WIDTH;
	w->ray.draw.start = (int)((-w->ray.lineHeight / 2) + (HEIGHT / 2)) + w->event.up_mouve;
	if (w->ray.draw.start < 0)
		w->ray.draw.start = 0;
	w->ray.draw.end = (int)((w->ray.lineHeight / 2) + (HEIGHT / 2)) + w->event.down_mouve;
	if (w->ray.draw.end >= HEIGHT)
		w->ray.draw.end = HEIGHT - 1;
}

/*
**	calculate ray position and direction
**	length of ray from one x or y-side to next x or y-side
**	was there a wall hit?
**	coord of the square ( which box of the map we're in )
**	calculate step and initial sideDist
**	Perform DDA
**	Calculate distance projected on camera direction
*/

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

void fps_calculation(t_fps *fps)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), (fps->last_frame_time + fps->frame_target)))
		;
	fps->delta_time = (SDL_GetTicks() - fps->last_frame_time) / 1000.0f;
	fps->movespeed = 30 * fps->delta_time;
	fps->rotspeed = 2 * fps->delta_time;
}

/*
//
// trap the mouse inside the window
//
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
	w->player.initial_pos.x = 19.5;
	w->player.initial_pos.y = 19.5;
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

	if (ac > 1)
	{
		w = malloc(sizeof(t_wolf_3d));
		fd = open(av[1], O_RDONLY);
		w->player.world_map = get_map(w->player.world_map, fd, av);
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
	return (0);
}
