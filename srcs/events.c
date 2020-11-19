/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:28:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/05 05:28:52 by yait-el-         ###   ########.fr       */
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

void mouse_motion_input(t_wolf_3d *w, Uint32 *mousestates)
{
	track_mouse(w, mousestates);
	mouse_limitation(w);
	if (w->event.oldmouse.x > w->event.newmouse.x)
		calculate_plane_dir_x(w, 0.1 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * (2 * w->fps.rotspeed)));
	if (w->event.oldmouse.x < w->event.newmouse.x)
		calculate_plane_dir_x(w, -0.1 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * (2 * w->fps.rotspeed)));
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
	if ((w->event.oldmouse.x != w->event.newmouse.x) && (w->event.newmouse.x > 0 || w->event.oldmouse.x > 0))
		w->event.oldmouse.x = w->event.newmouse.x;
}

void key_down_input(t_wolf_3d *w, const Uint8 *keystates, int **world_map)
{
	if (keystates[SDL_SCANCODE_A])
	{
		if (world_map[(int)(w->player.pos.x - (w->player.dir.y * 0.2))][(int)w->player.pos.y] == 0)
			w->player.pos.x -= (w->player.dir.y * 0.02);
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.x * 0.2))] == 0)
			w->player.pos.y += (w->player.dir.x * 0.02);
	}
	if (keystates[SDL_SCANCODE_D])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.y * 0.2))][(int)w->player.pos.y] == 0)
			w->player.pos.x += (w->player.dir.y * 0.02);
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - (w->player.dir.x * 0.2))] == 0)
			w->player.pos.y -= (w->player.dir.x * 0.02);
	}
	if (keystates[SDL_SCANCODE_W])
	{
		if (world_map[(int)(w->player.pos.x + (w->player.dir.x * 0.2))][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.x * 0.02;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y + (w->player.dir.y * 0.2))] == 0)
			w->player.pos.y += w->player.dir.y * 0.02;
	}
	if (keystates[SDL_SCANCODE_S])
	{
		if (world_map[(int)(w->player.pos.x - w->player.dir.x * 0.2)][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.x * 0.02;
		if (world_map[(int)w->player.pos.x][(int)(w->player.pos.y - w->player.dir.y * 0.2)] == 0)
			w->player.pos.y -= w->player.dir.y * 0.02;
	}
	if (keystates[SDL_SCANCODE_R])
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), (HEIGHT / 2));
		init_perso(w);
	}
}

/*
**
**	the arrow keys are still fucked up
**
*/
void arrow_move_input(t_wolf_3d *w, const Uint8 *keystates)
{
	if (keystates[SDL_SCANCODE_SPACE])
	{
		w->player.plane.x = 0 + 1;
		w->player.plane.y = 0.57 + 1;
	}
	if (keystates[SDL_SCANCODE_LEFT])
		calculate_plane_dir_x(w, 20 * 3.14 * w->fps.rotspeed / 180.0);
	if (keystates[SDL_SCANCODE_RIGHT])
		calculate_plane_dir_x(w, -20 * 3.14 * w->fps.rotspeed / 180.0);
	// if (keystates[SDL_SCANCODE_UP])
	// {
	// 	if(w->event.oldmouse.y <= WIDTH)
	// 	{
	// 		w->event.up_mouve += 5 * 3.14 * w->fps.movespeed;
	// 		w->event.down_mouve += 5 * 3.14 * w->fps.movespeed;
	// 		w->event.oldmouse.y += 5 * 3.14 * w->fps.movespeed;
	// 		w->event.newmouse.y += 5 * 3.14 * w->fps.movespeed;
	// 	}
	// }
	// if (keystates[SDL_SCANCODE_DOWN])
	// {
	// 	if(w->event.oldmouse.y >= -(WIDTH / 2) && w->event.oldmouse.y > 0)
	// 	{
	// 		w->event.up_mouve += -5 * 3.14 * w->fps.movespeed;
	// 		w->event.down_mouve += -5 * 3.14 * w->fps.movespeed;
	// 		w->event.oldmouse.y += -5 * 3.14 * w->fps.movespeed;
	// 		w->event.newmouse.y += -5 * 3.14 * w->fps.movespeed;
	// 	}
	// }
}

void process_input(t_wolf_3d *w, int **world_map)
{
	const Uint8 *keystates;
	SDL_ShowCursor(0);
	keystates = SDL_GetKeyboardState(NULL);
	track_mouse(w, &w->mousestates);
	SDL_PollEvent(&w->sdl.event);
	if (w->sdl.event.type == SDL_QUIT)
		w->game_running = 1;
	if (keystates[SDL_SCANCODE_ESCAPE])
		w->game_running = 1;
	arrow_move_input(w, keystates);
	key_down_input(w, keystates, world_map);
	mouse_motion_input(w, &w->mousestates);
	clear_data_tab(w->data);
	//draw_map_3d(w);
}
