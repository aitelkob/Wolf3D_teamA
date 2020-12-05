/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:28:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/05 18:59:48 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void mouse_limitation(t_wolf_3d *w)
{
	if (w->event.newmouse.x > WIDTH - 10)
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), w->event.newmouse.y);
		w->event.newmouse.x = WIDTH / 2;
		w->event.oldmouse.x = WIDTH / 2;
	}
	else if (w->event.newmouse.x < 10)
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), w->event.newmouse.y);
		w->event.newmouse.x = WIDTH / 2;
		w->event.oldmouse.x = WIDTH / 2;
	}
	else if (w->event.newmouse.y >= HEIGHT - 5)
		SDL_WarpMouseInWindow(w->sdl.win, w->event.oldmouse.x, HEIGHT - 6);
}

/*
**	The first time put the mouse in th middle of the screan
**	after that update it on the last new known position
*/

void track_mouse(t_wolf_3d *w, Uint32 *mousestates)
{
	static int i;

	if (i == 0)
	{
		*mousestates = SDL_GetMouseState(&w->event.oldmouse.x, &w->event.oldmouse.y);
		i++;
	}
	*mousestates = SDL_GetMouseState(&w->event.newmouse.x, &w->event.newmouse.y);
}

/*
**	mouse mouvement left
**	mouse mouvement rigth
**	mouse mouvement up
**	mouse mouvement down
**	update the mouvement and stops it
*/

void mouse_motion_input(t_wolf_3d *w, Uint32 *mousestates)
{
	track_mouse(w, mousestates);
	mouse_limitation(w);
	if (w->event.oldmouse.x > w->event.newmouse.x)
		calculate_plane_dir_x(w, 0.05 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * (2 * w->fps.rotspeed)));
	if (w->event.oldmouse.x < w->event.newmouse.x)
		calculate_plane_dir_x(w, -0.05 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * (2 * w->fps.rotspeed)));
	if (w->event.oldmouse.y > w->event.newmouse.y && w->event.newmouse.y < WIDTH && w->event.oldmouse.y < WIDTH)
	{
		w->event.up_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
		w->event.down_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
	}
	if (w->event.oldmouse.y < w->event.newmouse.y && w->event.newmouse.y > 0 && w->event.oldmouse.y > 0)
	{
		w->event.up_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
		w->event.down_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
	}
	if ((w->event.oldmouse.x != w->event.newmouse.x))
		w->event.oldmouse.x = w->event.newmouse.x;
}

void key_down_input(t_wolf_3d *w, const Uint8 *keystates, int **world_map)
{
	if (keystates[SDL_SCANCODE_A])
	{
		if (world_map[(int)(w->player.pos.x - (w->player.dir.y * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.y * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.x * w->fps.movespeed))] == 0)
			w->player.pos.y += w->player.dir.x * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_D])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.y * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.y * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - (w->player.dir.x * w->fps.movespeed))] == 0)
			w->player.pos.y -= w->player.dir.x * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_W])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.x * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.x * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.y * w->fps.movespeed))] == 0)
			w->player.pos.y += w->player.dir.y * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_S])
	{
		if (world_map[(int)(w->player.pos.x - w->player.dir.x * w->fps.movespeed)][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.x * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - w->player.dir.y * w->fps.movespeed)] == 0)
			w->player.pos.y -= w->player.dir.y * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_R])
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), (HEIGHT / 2));
		init_perso(w);
	}
}

void arrow_move_input(t_wolf_3d *w, const Uint8 *keystates)
{
	if (keystates[SDL_SCANCODE_LEFT])
		calculate_plane_dir_x(w, 20 * (3.14 * w->fps.rotspeed) / 180.0);
	if (keystates[SDL_SCANCODE_RIGHT])
		calculate_plane_dir_x(w, -20 * (3.14 * w->fps.rotspeed) / 180.0);
}

int light_input(t_wolf_3d *w, int color)
{
	if (w->event.keystates[SDL_SCANCODE_L])
		w->event.i = 0;
	if (w->event.keystates[SDL_SCANCODE_P])
		w->event.i = 1;
	if (w->event.i)
		color = darken_wall_color(w, color);

	return (color);
}

void process_input(t_wolf_3d *w, int **world_map)
{
	SDL_ShowCursor(0);
	w->event.keystates = SDL_GetKeyboardState(NULL);
	track_mouse(w, &w->mousestates);
	SDL_PollEvent(&w->sdl.event);
	if (w->sdl.event.type == SDL_QUIT)
		w->game_running = 1;
	if (w->event.keystates[SDL_SCANCODE_ESCAPE])
		w->game_running = 1;
	arrow_move_input(w, w->event.keystates);
	key_down_input(w, w->event.keystates, world_map);
	mouse_motion_input(w, &w->mousestates);
	clear_data_tab(w->data);
}
