/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:28:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/07 16:56:39 by ayagoumi         ###   ########.fr       */
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
	else if (w->event.newmouse.y >= HEIGHT - 50)
		SDL_WarpMouseInWindow(w->sdl.win, w->event.oldmouse.x, HEIGHT - 60);
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
	if (w->event.oldmouse.x != w->event.newmouse.x)
		w->event.oldmouse.x = w->event.newmouse.x;
}

void key_down_input(t_wolf_3d *w, const Uint8 *keystates, int **world_map)
{
	if (keystates[SDL_SCANCODE_A])
	{
		if (world_map[(int)(w->player.pos.x - (w->player.dir.y * 8 * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.y * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.x * 8 * w->fps.movespeed))] == 0)
			w->player.pos.y += w->player.dir.x * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_D])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.y * 8 * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.y * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - (w->player.dir.x * 8 * w->fps.movespeed))] == 0)
			w->player.pos.y -= w->player.dir.x * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_UP])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.x * 8 * w->fps.movespeed))][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.x * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.y * 8 * w->fps.movespeed))] == 0)
			w->player.pos.y += w->player.dir.y * w->fps.movespeed;
	}
	if (keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_DOWN])
	{
		if (world_map[(int)(w->player.pos.x - w->player.dir.x * 8 * w->fps.movespeed)][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.x * w->fps.movespeed;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - w->player.dir.y * 8 * w->fps.movespeed)] == 0)
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
		calculate_plane_dir_x(w, 30 * (3.14 * w->fps.rotspeed) / 180.0);
	if (keystates[SDL_SCANCODE_RIGHT])
		calculate_plane_dir_x(w, -30 * (3.14 * w->fps.rotspeed) / 180.0);
}

void wall_light_input(t_wolf_3d *w, int *color)
{
	if (w->event.keystates[SDL_SCANCODE_K])
		w->event.light1 = 0;
	else if (w->event.keystates[SDL_SCANCODE_L])
		w->event.light1 = 1;
	if (w->event.light1)
	{
		darken_wall_color(w, color);
		if (w->event.keystates[SDL_SCANCODE_KP_PLUS])
			w->event.darken_value = 3.5;
		if (w->event.keystates[SDL_SCANCODE_KP_MINUS])
			w->event.darken_value = 0.9;
	}
}

void light_input(t_wolf_3d *w, int *color)
{
	if (w->event.keystates[SDL_SCANCODE_K] && w->sdl.ceiling_tex != 1)
		w->event.light2 = 0;
	else if (w->event.keystates[SDL_SCANCODE_L] && w->sdl.ceiling_tex != 1)
		w->event.light2 = 1;
	if (w->event.light2)
	{
		darken_fall_color(w, color);
		if (w->event.keystates[SDL_SCANCODE_KP_PLUS])
			w->event.darken_value = 3.5;
		if (w->event.keystates[SDL_SCANCODE_KP_MINUS])
			w->event.darken_value = 0.9;
	}
}

void tex_input(t_wolf_3d *w)
{

	if (w->event.keystates[SDL_SCANCODE_KP_1])
	{
		w->sdl.ceiling_tex = 1;
		w->sdl.new_text[0] = (unsigned int *)w->sdl.wall1->pixels;
		w->sdl.new_text[1] = (unsigned int *)w->sdl.wall2->pixels;
		w->sdl.new_text[2] = (unsigned int *)w->sdl.wall3->pixels;
		w->sdl.new_text[3] = (unsigned int *)w->sdl.wall4->pixels;
		w->sdl.wall_data_ceiling = (unsigned int *)w->sdl.roof_texture1->pixels;
		w->sdl.wall_data_floor = (unsigned int *)w->sdl.floor_texture1->pixels;
	}
	if (w->event.keystates[SDL_SCANCODE_KP_2])
	{
		w->sdl.ceiling_tex = 2;
		w->sdl.new_text[0] = (unsigned int *)w->sdl.wall5->pixels;
		w->sdl.new_text[1] = (unsigned int *)w->sdl.wall6->pixels;
		w->sdl.new_text[2] = (unsigned int *)w->sdl.wall7->pixels;
		w->sdl.new_text[3] = (unsigned int *)w->sdl.wall8->pixels;
		w->sdl.wall_data_ceiling = (unsigned int *)w->sdl.roof_texture2->pixels;
		w->sdl.wall_data_floor = (unsigned int *)w->sdl.floor_texture2->pixels;
	}
	if (w->event.keystates[SDL_SCANCODE_KP_3])
	{
		w->sdl.ceiling_tex = 3;
		w->sdl.new_text[0] = (unsigned int *)w->sdl.wall9->pixels;
		w->sdl.new_text[1] = (unsigned int *)w->sdl.wall10->pixels;
		w->sdl.new_text[2] = (unsigned int *)w->sdl.wall11->pixels;
		w->sdl.new_text[3] = (unsigned int *)w->sdl.wall12->pixels;
		w->sdl.wall_data_ceiling = (unsigned int *)w->sdl.roof_texture3->pixels;
		w->sdl.wall_data_floor = (unsigned int *)w->sdl.floor_texture3->pixels;
	}
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
	tex_input(w);
	arrow_move_input(w, w->event.keystates);
	key_down_input(w, w->event.keystates, world_map);
	mouse_motion_input(w, &w->mousestates);
	clear_data_tab(w->data);
}
