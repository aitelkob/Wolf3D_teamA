/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:28:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/10/16 09:41:23 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void	mouse_limitation(t_wolf_3d *w)
{
	if (w->event.newmouse.x > WIDTH - 1|| w->event.newmouse.x < 0)
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), w->event.newmouse.y);
		w->event.newmouse.x = WIDTH / 2;
	}
}

void	track_mouse(t_wolf_3d	*w, Uint32 *mousestates)
{
	static int i;

	if (i == 0)
	{
		*mousestates = SDL_GetMouseState(&w->event.oldmouse.x, &w->event.oldmouse.y);
		i++;
	}
	*mousestates = SDL_GetMouseState(&w->event.newmouse.x, &w->event.newmouse.y);
}

void	mouse_motion_input(t_wolf_3d *w, Uint32	*mousestates)
{
	track_mouse(w, mousestates);
	mouse_limitation(w);
	if (w->event.oldmouse.x > w->event.newmouse.x)
		calculate_plane_dir_x(w, 0.05 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * 2 * w->fps.rotspeed));
	if (w->event.oldmouse.x < w->event.newmouse.x)
		calculate_plane_dir_x(w, -0.05 * ((abs(w->event.oldmouse.x - w->event.newmouse.x) % 100) * 2 * w->fps.rotspeed));
	if (w->event.oldmouse.y > w->event.newmouse.y && w->event.newmouse.y > -200 && w->event.oldmouse.y > -200)
	{
		w->event.up_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
		w->event.down_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
	}
	if (w->event.oldmouse.y < w->event.newmouse.y && w->event.newmouse.y < 1300 && w->event.oldmouse.y < 1300)
	{
		w->event.up_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
		w->event.down_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
	}
	if ((w->event.oldmouse.x != w->event.newmouse.x))
		w->event.oldmouse.x = w->event.newmouse.x;
}

void	key_down_input(t_wolf_3d *w, const Uint8 *keystates, int	**world_map)
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
}

// void	arrow_move_input(t_wolf_3d *w, const Uint8 *keystates, t_var	*v)
// {
// 	if (keystates[SDL_SCANCODE_LEFT])
// 		calculate_plane_dir_x(w, 2 * 3.14 * w->rotspeed / 180.0);
// 	if (keystates[SDL_SCANCODE_RIGHT])
// 		calculate_plane_dir_x(w, -2 * 3.14 * w->rotspeed / 180.0);
// 	if (keystates[SDL_SCANCODE_UP])
// 	{
// 		if(v->oldmouse.y < 1300)
// 		{
// 			printf("%d,%d\n", v->oldmouse.x, v->oldmouse.y);
// 			v->up_mouve += 10 * w->movespeed;
// 			v->down_mouve += 10 * w->movespeed;
// 			v->oldmouse.y += 10 * w->movespeed;
// 			v->newmouse.y += 10 * w->movespeed;
// 		}
// 	}
// 	if (keystates[SDL_SCANCODE_DOWN])
// 	{
// 		if(v->oldmouse.y > -200)
// 		{
// 		printf("%d,%d\n", v->oldmouse.x, v->oldmouse.y);
// 			v->up_mouve += -10 * w->movespeed;
// 			v->down_mouve += -10 * w->movespeed;
// 			v->oldmouse.y += -10 * w->movespeed;
// 			v->newmouse.y += -10 * w->movespeed;
// 		}
// 	}
// }

void	process_input(t_wolf_3d *w, int	**world_map)
{
    const Uint8		*keystates;

    keystates = SDL_GetKeyboardState(NULL);
	track_mouse(w, &w->mousestates);
    SDL_PollEvent(&w->sdl.event);
    if(w->sdl.event.type == SDL_QUIT)
		w->game_running = 1;
    if (keystates[SDL_SCANCODE_ESCAPE])
			w->game_running = 1;
	//arrow_move_input(w, keystates, v);
	key_down_input(w, keystates, world_map);
	mouse_motion_input(w, &w->mousestates);
    clear_data_tab(w->data);
	draw_map_3d(w);
}